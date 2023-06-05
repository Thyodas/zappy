cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 20)

set(TARGET zappy_gui)

project(${TARGET})

set(SOURCE
    Main.cpp
    Core.cpp
)

list(TRANSFORM SOURCE PREPEND "src/")

add_compile_options(-Wall -Wextra -std=c++2a)

add_executable(${TARGET} ${SOURCE})

set_target_properties(${TARGET} PROPERTIES
    LINKER_LANGUAGE CXX
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
)

target_include_directories(${TARGET} PUBLIC ./include/)

target_link_libraries(${TARGET} raylib)
target_link_libraries(${TARGET} pthread)
target_link_libraries(${TARGET} dl)
