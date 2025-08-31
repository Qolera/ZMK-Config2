/*
 * Copyright (c) 2024 The ZMK Contributors
 *
 * SPDX-License-Identifier: MIT
 */

#include <zephyr/kernel.h>
#include <zmk/keymap.h>

// Provide missing function for PIM447 driver
void activate_automouse_layer(void) {
    // Activate layer 4 - adjust as needed for your keymap
    zmk_keymap_layer_activate(4);
}

void deactivate_automouse_layer(void) {
    zmk_keymap_layer_deactivate(4);
}

// Board init to ensure this gets linked
static int nice_nano_board_init(void) {
    return 0;
}

SYS_INIT(nice_nano_board_init, POST_KERNEL, CONFIG_KERNEL_INIT_PRIORITY_DEFAULT);