target_sources_ifdef(CONFIG_ZMK_POINTING app PRIVATE 
    src/automouse_layer.c
)
target_include_directories(app PRIVATE include)