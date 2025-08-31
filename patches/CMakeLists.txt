target_sources(app PRIVATE 
    src/automouse_layer.c
    src/zmk_automouse.c
)
target_include_directories(app PRIVATE include)