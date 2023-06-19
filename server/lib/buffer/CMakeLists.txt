cmake_minimum_required(VERSION 3.18)

project(buffer)

set(CMAKE_C_FLAGS "-Wall -Wextra")

add_library(${PROJECT_NAME}
            buffer.c
            memory.c
            )
