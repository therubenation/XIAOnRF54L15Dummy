#include <zephyr/kernel.h>
#include <zephyr/bluetooth/bluetooth.h>
#include <zephyr/bluetooth/gatt.h>
#include <zephyr/bluetooth/uuid.h>
#include <zephyr/drivers/gpio.h>
#include <string.h>
#include <stdio.h>

static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(DT_ALIAS(led0), gpios);

static void error_blink(void)
{
    /* Fast blink: BLE init failed */
    while (1) {
        gpio_pin_toggle_dt(&led);
        k_sleep(K_MSEC(100));
    }
}

#define DEVICE_NAME CONFIG_BT_DEVICE_NAME
#define DEVICE_NAME_LEN (sizeof(DEVICE_NAME) - 1)

#define COMMAND_BUFFER_SIZE 128
#define RESPONSE_BUFFER_SIZE 128

static char read_value[] = "HELLO";
static char last_command[COMMAND_BUFFER_SIZE] = "NONE";
static char response_value[RESPONSE_BUFFER_SIZE] = "READY";

static struct bt_uuid_128 service_uuid = BT_UUID_INIT_128(
    BT_UUID_128_ENCODE(0x12345678, 0x1234, 0x5678, 0x1234, 0x56789abcdef0));

static struct bt_uuid_128 read_uuid = BT_UUID_INIT_128(
    BT_UUID_128_ENCODE(0x12345678, 0x1234, 0x5678, 0x1234, 0x56789abcdef1));

static struct bt_uuid_128 command_uuid = BT_UUID_INIT_128(
    BT_UUID_128_ENCODE(0x12345678, 0x1234, 0x5678, 0x1234, 0x56789abcdef2));

static struct bt_uuid_128 response_uuid = BT_UUID_INIT_128(
    BT_UUID_128_ENCODE(0x12345678, 0x1234, 0x5678, 0x1234, 0x56789abcdef3));

/* Advertising */
static const struct bt_data ad[] = {
    BT_DATA_BYTES(BT_DATA_FLAGS, (BT_LE_AD_GENERAL | BT_LE_AD_NO_BREDR)),
    BT_DATA(BT_DATA_NAME_COMPLETE, DEVICE_NAME, DEVICE_NAME_LEN),
};

static const struct bt_data sd[] = {
    BT_DATA_BYTES(BT_DATA_UUID128_ALL,
        BT_UUID_128_ENCODE(0x12345678, 0x1234, 0x5678, 0x1234, 0x56789abcdef0)),
};

/* READS */

static ssize_t read_dummy(struct bt_conn *conn,
                          const struct bt_gatt_attr *attr,
                          void *buf,
                          uint16_t len,
                          uint16_t offset)
{
    return bt_gatt_attr_read(conn, attr, buf, len, offset,
                             read_value, strlen(read_value));
}

static ssize_t read_command(struct bt_conn *conn,
                            const struct bt_gatt_attr *attr,
                            void *buf,
                            uint16_t len,
                            uint16_t offset)
{
    return bt_gatt_attr_read(conn, attr, buf, len, offset,
                             last_command, strlen(last_command));
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

/* LOGIC */

static void build_response(const char *cmd)
{
    if (strstr(cmd, "FREQ=100")) {
        snprintf(response_value, sizeof(response_value),
                 "TRACE:-12,-10,-9,-4,3,12");
    } else {
        snprintf(response_value, sizeof(response_value),
                 "ACK:%s", cmd);
    }
}

/* WRITE */

static ssize_t write_command(struct bt_conn *conn,
                             const struct bt_gatt_attr *attr,
                             const void *buf,
                             uint16_t len,
                             uint16_t offset,
                             uint8_t flags)
{
    if (offset + len >= COMMAND_BUFFER_SIZE) {
        return BT_GATT_ERR(BT_ATT_ERR_INVALID_ATTRIBUTE_LEN);
    }

    /* During Prepare Write phase: validate only, don't commit */
    if (flags & BT_GATT_WRITE_FLAG_PREPARE) {
        return len;
    }

    /* Clear buffer on first (or only) chunk */
    if (offset == 0) {
        memset(last_command, 0, sizeof(last_command));
    }

    memcpy(last_command + offset, buf, len);
    last_command[offset + len] = '\0';

    build_response(last_command);

    return len;
}

/* GATT */

BT_GATT_SERVICE_DEFINE(hormone_service,
    BT_GATT_PRIMARY_SERVICE(&service_uuid),

    BT_GATT_CHARACTERISTIC(&read_uuid.uuid,
        BT_GATT_CHRC_READ,
        BT_GATT_PERM_READ,
        read_dummy, NULL, NULL),

    BT_GATT_CHARACTERISTIC(&command_uuid.uuid,
        BT_GATT_CHRC_READ | BT_GATT_CHRC_WRITE,   // NO write without response
        BT_GATT_PERM_READ | BT_GATT_PERM_WRITE,
        read_command, write_command, NULL),

    BT_GATT_CHARACTERISTIC(&response_uuid.uuid,
        BT_GATT_CHRC_READ,
        BT_GATT_PERM_READ,
        read_response, NULL, NULL),
);

/* MAIN */

int main(void)
{
    int err;

    gpio_pin_configure_dt(&led, GPIO_OUTPUT_INACTIVE);

    err = bt_enable(NULL);
    if (err) {
        error_blink();
    }

    err = bt_le_adv_start(BT_LE_ADV_CONN_FAST_1,
                          ad, ARRAY_SIZE(ad),
                          sd, ARRAY_SIZE(sd));

    if (err) {
        error_blink();
    }

    /* Slow heartbeat: advertising OK */
    while (1) {
        gpio_pin_toggle_dt(&led);
        k_sleep(K_MSEC(500));
    }
}