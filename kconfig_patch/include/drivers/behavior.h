/*
 * Copyright (c) 2020 The ZMK Contributors
 *
 * SPDX-License-Identifier: MIT
 *
 * Patched version of behavior.h to use short device names
 */

#pragma once

#include_next <drivers/behavior.h>

#ifdef CONFIG_ZMK_SHORT_DEVICE_NAMES
/* Redefine BEHAVIOR_DT_INST_DEFINE to use short synthetic names.
 * This avoids Zephyr's 48-character device name limit by using
 * simple numeric names like "behavior_0", "behavior_1", etc.
 * Safe for behaviors as they are not real hardware devices.
 */
#undef BEHAVIOR_DT_INST_DEFINE
#define BEHAVIOR_DT_INST_DEFINE(inst, ...) \
    DEVICE_DEFINE(behavior_##inst, __VA_ARGS__)
#endif /* CONFIG_ZMK_SHORT_DEVICE_NAMES */