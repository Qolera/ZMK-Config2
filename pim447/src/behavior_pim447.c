/*
 * Copyright (c) 2024 The ZMK Contributors
 *
 * SPDX-License-Identifier: MIT
 */

#define DT_DRV_COMPAT zmk_behavior_pim447

#include <zephyr/device.h>
#include <drivers/behavior.h>
#include <zephyr/logging/log.h>
#include <zmk/behavior.h>

LOG_MODULE_DECLARE(zmk, CONFIG_ZMK_LOG_LEVEL);

struct behavior_pim447_config {
    // Add your config properties here
};

struct behavior_pim447_data {
    // Add your data properties here
};

static int behavior_pim447_init(const struct device *dev) {
    return 0;
}

static int on_keymap_binding_pressed(struct zmk_behavior_binding *binding,
                                   struct zmk_behavior_binding_event event) {
    const struct device *dev = zmk_behavior_get_binding_device(binding);
    // param1 = binding->param1, param2 = binding->param2
    
    LOG_DBG("PIM447 behavior pressed: param1=%d, param2=%d", 
            binding->param1, binding->param2);
    
    // Add your behavior logic here
    
    return ZMK_BEHAVIOR_OPAQUE;
}

static int on_keymap_binding_released(struct zmk_behavior_binding *binding,
                                    struct zmk_behavior_binding_event event) {
    const struct device *dev = zmk_behavior_get_binding_device(binding);
    
    LOG_DBG("PIM447 behavior released: param1=%d, param2=%d", 
            binding->param1, binding->param2);
    
    // Add your release logic here
    
    return ZMK_BEHAVIOR_OPAQUE;
}

static const struct behavior_driver_api behavior_pim447_driver_api = {
    .binding_pressed = on_keymap_binding_pressed,
    .binding_released = on_keymap_binding_released,
};

static const struct behavior_pim447_config behavior_pim447_config_0 = {};
static struct behavior_pim447_data behavior_pim447_data_0 = {};

BEHAVIOR_DT_INST_DEFINE(0, behavior_pim447_init, NULL, &behavior_pim447_data_0,
                       &behavior_pim447_config_0, POST_KERNEL,
                       CONFIG_KERNEL_INIT_PRIORITY_DEFAULT, &behavior_pim447_driver_api);

// Auto-instantiation for all compatible nodes
#if DT_HAS_COMPAT_STATUS_OKAY(DT_DRV_COMPAT)
DT_INST_FOREACH_STATUS_OKAY(BEHAVIOR_DT_INST_DEFINE)
#endif