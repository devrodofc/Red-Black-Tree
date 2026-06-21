cmake_minimum_required(VERSION 3.20)

project(red_black_tree C)

set(CMAKE_C_STANDARD 11)

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    add_compile_options(
            -O3
            -march=native
    )
endif()

add_executable(
        red_black_tree

        src/main.c
        src/rbtree.c
        src/benchmark.c
        src/csv.c
)