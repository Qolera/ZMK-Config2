/*
 * Copyright (c) 2024 The ZMK Contributors
 *
 * SPDX-License-Identifier: MIT
 */

#include <zephyr/kernel.h>
#include <zmk/keymap.h>

// Stub implementation for PIM447 driver
void activate_automouse_layer(void) {
    // Activate layer 4 - adjust as needed for your keymap
    zmk_keymap_layer_activate(4);
}

void deactivate_automouse_layer(void) {
    zmk_keymap_layer_deactivate(4);
}

// Force this to be linked
static int stub_init(void) {
    return 0;
}

SYS_INIT(stub_init, APPLICATION, CONFIG_APPLICATION_INIT_PRIORITY);