cmake_minimum_required(VERSION 3.22)

project(vector)

set(CMAKE_C_FLAGS "-Wall -Wextra")

add_library(${PROJECT_NAME}
            element.c
            init.c
            save.c
            )
