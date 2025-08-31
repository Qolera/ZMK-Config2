/*
 * Copyright (c) 2024 The ZMK Contributors
 *
 * SPDX-License-Identifier: MIT
 */

#define DT_DRV_COMPAT pimoroni_pim447_custom

#include <zephyr/device.h>
#include <zephyr/drivers/i2c.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/input/input.h>
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>

LOG_MODULE_REGISTER(pim447_custom, CONFIG_INPUT_LOG_LEVEL);

/* PIM447 I2C registers (based on Pimoroni documentation) */
#define PIM447_REG_LED_RED     0x00
#define PIM447_REG_LED_GRN     0x01  
#define PIM447_REG_LED_BLU     0x02
#define PIM447_REG_LED_WHT     0x03
#define PIM447_REG_LEFT        0x04
#define PIM447_REG_RIGHT       0x05
#define PIM447_REG_UP          0x06
#define PIM447_REG_DOWN        0x07
#define PIM447_REG_SWITCH      0x08
#define PIM447_REG_USER_FLASH  0xD0
#define PIM447_REG_FLASH_PAGE  0xF0
#define PIM447_REG_INT         0xF9
#define PIM447_REG_CHIP_ID_L   0xFA
#define PIM447_REG_CHIP_ID_H   0xFB
#define PIM447_REG_VERSION     0xFC
#define PIM447_REG_I2C_ADDR    0xFD
#define PIM447_REG_CTRL        0xFE

#define PIM447_CHIP_ID         0x0BA11
#define PIM447_MSK_SWITCH_STATE 0x80

struct pim447_config {
    struct i2c_dt_spec i2c;
    struct gpio_dt_spec int_gpio;
};

struct pim447_data {
    struct k_work work;
    const struct device *dev;
    struct gpio_callback int_cb;
};

static int pim447_read_reg(const struct device *dev, uint8_t reg, uint8_t *val)
{
    const struct pim447_config *config = dev->config;
    
    return i2c_reg_read_byte_dt(&config->i2c, reg, val);
}

static int pim447_write_reg(const struct device *dev, uint8_t reg, uint8_t val)
{
    const struct pim447_config *config = dev->config;
    
    return i2c_reg_write_byte_dt(&config->i2c, reg, val);
}

static void pim447_work_handler(struct k_work *work)
{
    struct pim447_data *data = CONTAINER_OF(work, struct pim447_data, work);
    const struct device *dev = data->dev;
    
    uint8_t left, right, up, down, switch_val;
    int8_t delta_x = 0, delta_y = 0;
    
    /* Read movement deltas */
    if (pim447_read_reg(dev, PIM447_REG_LEFT, &left) == 0) {
        delta_x -= (int8_t)left;
    }
    if (pim447_read_reg(dev, PIM447_REG_RIGHT, &right) == 0) {
        delta_x += (int8_t)right;
    }
    if (pim447_read_reg(dev, PIM447_REG_UP, &up) == 0) {
        delta_y -= (int8_t)up;  
    }
    if (pim447_read_reg(dev, PIM447_REG_DOWN, &down) == 0) {
        delta_y += (int8_t)down;
    }
    
    /* Send movement events if there's movement */
    if (delta_x != 0) {
        input_report_rel(dev, INPUT_REL_X, delta_x);
    }
    if (delta_y != 0) {
        input_report_rel(dev, INPUT_REL_Y, delta_y);
    }
    
    /* Read switch state */
    if (pim447_read_reg(dev, PIM447_REG_SWITCH, &switch_val) == 0) {
        bool pressed = (switch_val & PIM447_MSK_SWITCH_STATE) != 0;
        input_report_key(dev, INPUT_BTN_TOUCH, pressed ? 1 : 0);
    }
    
    /* Clear interrupt */
    pim447_write_reg(dev, PIM447_REG_INT, 0x00);
}

static void pim447_int_callback(const struct device *dev, struct gpio_callback *cb, uint32_t pins)
{
    struct pim447_data *data = CONTAINER_OF(cb, struct pim447_data, int_cb);
    
    k_work_submit(&data->work);
}

static int pim447_init(const struct device *dev)
{
    const struct pim447_config *config = dev->config;
    struct pim447_data *data = dev->data;
    uint8_t chip_id_l, chip_id_h;
    uint16_t chip_id;
    int ret;
    
    data->dev = dev;
    
    /* Check I2C connectivity */
    if (!i2c_is_ready_dt(&config->i2c)) {
        LOG_ERR("I2C device not ready");
        return -ENODEV;
    }
    
    /* Read and verify chip ID */
    ret = pim447_read_reg(dev, PIM447_REG_CHIP_ID_L, &chip_id_l);
    if (ret != 0) {
        LOG_ERR("Failed to read chip ID low byte: %d", ret);
        return ret;
    }
    
    ret = pim447_read_reg(dev, PIM447_REG_CHIP_ID_H, &chip_id_h);
    if (ret != 0) {
        LOG_ERR("Failed to read chip ID high byte: %d", ret);
        return ret;
    }
    
    chip_id = (chip_id_h << 8) | chip_id_l;
    if (chip_id != PIM447_CHIP_ID) {
        LOG_ERR("Invalid chip ID: 0x%04x (expected 0x%04x)", chip_id, PIM447_CHIP_ID);
        return -ENODEV;
    }
    
    LOG_INF("PIM447 trackball detected, chip ID: 0x%04x", chip_id);
    
    /* Initialize work queue */
    k_work_init(&data->work, pim447_work_handler);
    
    /* Configure interrupt GPIO if available */
    if (config->int_gpio.port != NULL) {
        if (!gpio_is_ready_dt(&config->int_gpio)) {
            LOG_ERR("Interrupt GPIO device not ready");
            return -ENODEV;
        }
        
        ret = gpio_pin_configure_dt(&config->int_gpio, GPIO_INPUT);
        if (ret != 0) {
            LOG_ERR("Failed to configure interrupt GPIO: %d", ret);
            return ret;
        }
        
        gpio_init_callback(&data->int_cb, pim447_int_callback, BIT(config->int_gpio.pin));
        
        ret = gpio_add_callback(config->int_gpio.port, &data->int_cb);
        if (ret != 0) {
            LOG_ERR("Failed to add GPIO callback: %d", ret);
            return ret;
        }
        
        ret = gpio_pin_interrupt_configure_dt(&config->int_gpio, GPIO_INT_EDGE_TO_ACTIVE);
        if (ret != 0) {
            LOG_ERR("Failed to configure GPIO interrupt: %d", ret);
            return ret;
        }
    }
    
    /* Initialize trackball - clear any pending interrupts */
    pim447_write_reg(dev, PIM447_REG_INT, 0x00);
    
    return 0;
}

#define PIM447_DEFINE(inst)                                                    \
    static const struct pim447_config pim447_config_##inst = {                \
        .i2c = I2C_DT_SPEC_INST_GET(inst),                                    \
        .int_gpio = GPIO_DT_SPEC_INST_GET_OR(inst, int_gpios, {0}),          \
    };                                                                         \
    static struct pim447_data pim447_data_##inst;                            \
    DEVICE_DT_INST_DEFINE(inst, pim447_init, NULL, &pim447_data_##inst,      \
                          &pim447_config_##inst, POST_KERNEL,                 \
                          CONFIG_INPUT_INIT_PRIORITY, NULL);

DT_INST_FOREACH_STATUS_OKAY(PIM447_DEFINE)