/*
 * Copyright (c) 2024 The ZMK Contributors
 *
 * SPDX-License-Identifier: MIT
 */

#include <zmk/keymap.h>

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