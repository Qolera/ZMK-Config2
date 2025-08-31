/*
 * Copyright (c) 2024 The ZMK Contributors
 *
 * SPDX-License-Identifier: MIT
 */

#include <zephyr/kernel.h>
#include <zmk/keymap.h>
#include <automouse.h>

// Define the automouse layer index - adjust this to match your keymap
#ifndef LAYER_AUTOMOUSE
#define LAYER_AUTOMOUSE 4   // Assuming automouse is layer 4, adjust as needed
#endif

// Provide the missing activate_automouse_layer function
void activate_automouse_layer(void) {
    zmk_keymap_layer_activate(LAYER_AUTOMOUSE);
}

// Optional: also provide deactivate function in case it's needed
void deactivate_automouse_layer(void) {
    zmk_keymap_layer_deactivate(LAYER_AUTOMOUSE);
}

// Force linking by having an init function
static int automouse_init(void) {
    // This forces the object file to be linked
    return 0;
}

SYS_INIT(automouse_init, APPLICATION, CONFIG_APPLICATION_INIT_PRIORITY);