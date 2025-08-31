# Copyright (c) 2023-2025 The ZMK Contributors
# SPDX-License-Identifier: MIT

# Always include the header directory regardless of CONFIG flag
# This ensures dt-bindings are available during preprocessing
zephyr_include_directories(include)

# Include the driver and behavior subdirectories if their respective Kconfig options are enabled
# Note: zephyr_library_subdirectory is not available in this Zephyr version
# The subdirectories handle their own CMake configuration