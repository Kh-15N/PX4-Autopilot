
px4_add_module(
    MODULE modules__my_module
    MAIN my_module
    COMPILE_FLAGS
        -Wno-cast-align
    SRCS
        my_module.cpp
    )