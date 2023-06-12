cmake_minimum_required(VERSION 3.22)

project(buffer)

set(CMAKE_C_FLAGS "-Wall -Wextra")

add_library(${PROJECT_NAME}
            buffer.c
            memory.c
            )
