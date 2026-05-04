#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>
#include <zephyr/bluetooth/bluetooth.h>
#include <zephyr/bluetooth/gatt.h>
#include <zephyr/bluetooth/uuid.h>
#include <string.h>
#include <stdio.h>

#define DEVICE_NAME CONFIG_BT_DEVICE_NAME
#define DEVICE_NAME_LEN (sizeof(DEVICE_NAME) - 1)

#define COMMAND_BUFFER_SIZE 64
#define RESPONSE_BUFFER_SIZE 128

static char read_value[] = "HELLO";
static char response_value[RESPONSE_BUFFER_SIZE] = "READY";

static struct bt_uuid_128 hormone_service_uuid = BT_UUID_INIT_128(
	BT_UUID_128_ENCODE(0x12345678, 0x1234, 0x5678, 0x1234, 0x56789abcdef0)
);

static struct bt_uuid_128 read_char_uuid = BT_UUID_INIT_128(
	BT_UUID_128_ENCODE(0x12345678, 0x1234, 0x5678, 0x1234, 0x56789abcdef1)
);

static struct bt_uuid_128 command_char_uuid = BT_UUID_INIT_128(
	BT_UUID_128_ENCODE(0x12345678, 0x1234, 0x5678, 0x1234, 0x56789abcdef2)
);

static struct bt_uuid_128 response_char_uuid = BT_UUID_INIT_128(
	BT_UUID_128_ENCODE(0x12345678, 0x1234, 0x5678, 0x1234, 0x56789abcdef3)
);

static const struct bt_data ad[] = {
	BT_DATA_BYTES(BT_DATA_FLAGS, (BT_LE_AD_GENERAL | BT_LE_AD_NO_BREDR)),
	BT_DATA(BT_DATA_NAME_COMPLETE, DEVICE_NAME, DEVICE_NAME_LEN),
};

static const struct bt_data sd[] = {
	BT_DATA_BYTES(BT_DATA_UUID128_ALL,
		BT_UUID_128_ENCODE(0x12345678, 0x1234, 0x5678, 0x1234, 0x56789abcdef0)),
};

static ssize_t read_dummy(struct bt_conn *conn,
			  const struct bt_gatt_attr *attr,
			  void *buf,
			  uint16_t len,
			  uint16_t offset)
{
	return bt_gatt_attr_read(conn, attr, buf, len, offset,
				 read_value, strlen(read_value));
}

static ssize_t read_response(struct bt_conn *conn,
			     const struct bt_gatt_attr *attr,
			     void *buf,
			     uint16_t len,
			     uint16_t offset)
{
	return bt_gatt_attr_read(conn, attr, buf, len, offset,
				 response_value, strlen(response_value));
}

static void build_response_from_command(const char *command)
{
	if (strstr(command, "FREQ=100") != NULL) {
		snprintf(response_value, sizeof(response_value),
			 "-12,-10,-9,-4,3,12,30,18,5,-1");
	} else if (strstr(command, "FREQ=200") != NULL) {
		snprintf(response_value, sizeof(response_value),
			 "-8,-6,-3,4,14,31,48,33,15,2,-4");
	} else {
		snprintf(response_value, sizeof(response_value),
			 "ACK:%s", command);
	}
}

static ssize_t write_command(struct bt_conn *conn,
			     const struct bt_gatt_attr *attr,
			     const void *buf,
			     uint16_t len,
			     uint16_t offset,
			     uint8_t flags)
{
	char command[COMMAND_BUFFER_SIZE];

	if (offset != 0) {
		return BT_GATT_ERR(BT_ATT_ERR_INVALID_OFFSET);
	}

	if (len >= sizeof(command)) {
		len = sizeof(command) - 1;
	}

	memcpy(command, buf, len);
	command[len] = '\0';

	build_response_from_command(command);

	return len;
}

BT_GATT_SERVICE_DEFINE(hormone_service,
	BT_GATT_PRIMARY_SERVICE(&hormone_service_uuid),

	BT_GATT_CHARACTERISTIC(&read_char_uuid.uuid,
			       BT_GATT_CHRC_READ,
			       BT_GATT_PERM_READ,
			       read_dummy,
			       NULL,
			       NULL),

	BT_GATT_CHARACTERISTIC(&command_char_uuid.uuid,
			       BT_GATT_CHRC_WRITE | BT_GATT_CHRC_WRITE_WITHOUT_RESP,
			       BT_GATT_PERM_WRITE,
			       NULL,
			       write_command,
			       NULL),

	BT_GATT_CHARACTERISTIC(&response_char_uuid.uuid,
			       BT_GATT_CHRC_READ,
			       BT_GATT_PERM_READ,
			       read_response,
			       NULL,
			       NULL)
);

int main(void)
{
	int err;

	printk("Starting BLE dummy with response state update\n");

	err = bt_enable(NULL);
	if (err) {
		printk("Bluetooth init failed: %d\n", err);
		return 0;
	}

	err = bt_le_adv_start(BT_LE_ADV_CONN_FAST_1,
			      ad, ARRAY_SIZE(ad),
			      sd, ARRAY_SIZE(sd));

	if (err) {
		printk("Advertising failed: %d\n", err);
		return 0;
	}

	while (1) {
		k_sleep(K_SECONDS(1));
	}

	return 0;
}