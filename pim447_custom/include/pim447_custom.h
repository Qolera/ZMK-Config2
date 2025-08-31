#ifndef PIM447_CUSTOM_H
#define PIM447_CUSTOM_H

#include <zephyr/device.h>
#include <zephyr/drivers/i2c.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/input/input.h>

#define PIM447_I2C_ADDR 0x0A

struct pim447_custom_config {
	struct i2c_dt_spec i2c;
	struct gpio_dt_spec int_gpio;
};

struct pim447_custom_data {
	struct gpio_callback int_cb_data;
	struct k_work work;
};

#endif /* PIM447_CUSTOM_H */