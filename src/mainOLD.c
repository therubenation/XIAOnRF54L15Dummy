#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>
#include <zephyr/bluetooth/bluetooth.h>
#include <zephyr/bluetooth/conn.h>
#include <zephyr/bluetooth/gatt.h>
#include <zephyr/bluetooth/uuid.h>
#include <string.h>
#include <stdio.h>

#define DEVICE_NAME CONFIG_BT_DEVICE_NAME
#define DEVICE_NAME_LEN (sizeof(DEVICE_NAME) - 1)

#define COMMAND_BUFFER_SIZE 128
#define TRACE_BUFFER_SIZE 128

static struct bt_conn *current_conn;
static bool trace_notifications_enabled;

static char last_command[COMMAND_BUFFER_SIZE] = "NO_COMMAND";
static char trace_value[TRACE_BUFFER_SIZE] = "-12,-10,-9,-4,3,12,30,18,5,-1";

static struct bt_uuid_128 hormone_service_uuid = BT_UUID_INIT_128(
		BT_UUID_128_ENCODE(0x12345678, 0x1234, 0x5678, 0x1234, 0x56789abcdef0));

static struct bt_uuid_128 command_char_uuid = BT_UUID_INIT_128(
		BT_UUID_128_ENCODE(0x12345678, 0x1234, 0x5678, 0x1234, 0x56789abcdef1));

static struct bt_uuid_128 trace_char_uuid = BT_UUID_INIT_128(
		BT_UUID_128_ENCODE(0x12345678, 0x1234, 0x5678, 0x1234, 0x56789abcdef2));

static ssize_t write_command(struct bt_conn *conn,
														 const struct bt_gatt_attr *attr,
														 const void *buf,
														 uint16_t len,
														 uint16_t offset,
														 uint8_t flags);

static ssize_t read_trace(struct bt_conn *conn,
													const struct bt_gatt_attr *attr,
													void *buf,
													uint16_t len,
													uint16_t offset)
{
	const char *value = attr->user_data;

	return bt_gatt_attr_read(conn, attr, buf, len, offset, value, strlen(value));
}

static void trace_ccc_changed(const struct bt_gatt_attr *attr, uint16_t value)
{
	trace_notifications_enabled = (value == BT_GATT_CCC_NOTIFY);

	printk("Trace notifications %s\n",
				 trace_notifications_enabled ? "enabled" : "disabled");
}

BT_GATT_SERVICE_DEFINE(hormone_service,
											 BT_GATT_PRIMARY_SERVICE(&hormone_service_uuid),

											 BT_GATT_CHARACTERISTIC(&command_char_uuid.uuid,
																							BT_GATT_CHRC_WRITE | BT_GATT_CHRC_WRITE_WITHOUT_RESP,
																							BT_GATT_PERM_WRITE,
																							NULL,
																							write_command,
																							NULL),

											 BT_GATT_CHARACTERISTIC(&trace_char_uuid.uuid,
																							BT_GATT_CHRC_READ | BT_GATT_CHRC_NOTIFY,
																							BT_GATT_PERM_READ,
																							read_trace,
																							NULL,
																							trace_value),

											 BT_GATT_CCC(trace_ccc_changed,
																	 BT_GATT_PERM_READ | BT_GATT_PERM_WRITE));

static void generate_fake_trace(const char *command)
{
	if (strstr(command, "FREQ=100") != NULL)
	{
		snprintf(trace_value, sizeof(trace_value),
						 "-12,-10,-9,-4,3,12,30,18,5,-1");
	}
	else if (strstr(command, "FREQ=200") != NULL)
	{
		snprintf(trace_value, sizeof(trace_value),
						 "-8,-6,-3,4,14,31,48,33,15,2,-4");
	}
	else
	{
		snprintf(trace_value, sizeof(trace_value),
						 "-5,-3,0,8,21,35,22,9,1,-2");
	}
}

static ssize_t write_command(struct bt_conn *conn,
														 const struct bt_gatt_attr *attr,
														 const void *buf,
														 uint16_t len,
														 uint16_t offset,
														 uint8_t flags)
{
	if (offset != 0)
	{
		return BT_GATT_ERR(BT_ATT_ERR_INVALID_OFFSET);
	}

	if (len >= COMMAND_BUFFER_SIZE)
	{
		return BT_GATT_ERR(BT_ATT_ERR_INVALID_ATTRIBUTE_LEN);
	}

	memcpy(last_command, buf, len);
	last_command[len] = '\0';

	printk("Received command: %s\n", last_command);

	generate_fake_trace(last_command);

	if (trace_notifications_enabled)
	{
		int err = bt_gatt_notify(
				conn,
				&hormone_service.attrs[4],
				trace_value,
				strlen(trace_value));

		if (err)
		{
			printk("Notify failed: %d\n", err);
		}
		else
		{
			printk("Trace notified: %s\n", trace_value);
		}
	}
	else
	{
		printk("Trace generated but notifications are not enabled.\n");
	}

	return len;
}

static const struct bt_data advertising_data[] = {
		BT_DATA_BYTES(BT_DATA_FLAGS, (BT_LE_AD_GENERAL | BT_LE_AD_NO_BREDR)),
		BT_DATA(BT_DATA_NAME_COMPLETE, DEVICE_NAME, DEVICE_NAME_LEN),
};

static void connected(struct bt_conn *conn, uint8_t err)
{
	if (err)
	{
		printk("Connection failed: %u\n", err);
		return;
	}

	current_conn = bt_conn_ref(conn);
	printk("Connected\n");
}

static void disconnected(struct bt_conn *conn, uint8_t reason)
{
	printk("Disconnected: %u\n", reason);

	if (current_conn != NULL)
	{
		bt_conn_unref(current_conn);
		current_conn = NULL;
	}

	trace_notifications_enabled = false;
}

BT_CONN_CB_DEFINE(conn_callbacks) = {
		.connected = connected,
		.disconnected = disconnected,
};

int main(void)
{
	int err;

	printk("Starting Hormone Dummy BLE firmware\n");

	err = bt_enable(NULL);
	if (err)
	{
		printk("Bluetooth init failed: %d\n", err);
		return 0;
	}

	printk("Bluetooth initialized\n");

	err = bt_le_adv_start(BT_LE_ADV_CONN_FAST_1,
												advertising_data,
												ARRAY_SIZE(advertising_data),
												NULL,
												0);

	if (err)
	{
		printk("Advertising failed to start: %d\n", err);
		return 0;
	}

	printk("Advertising as %s\n", DEVICE_NAME);

	while (1)
	{
		k_sleep(K_SECONDS(1));
	}

	return 0;
}