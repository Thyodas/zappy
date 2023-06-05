cmake_minimum_required(VERSION 3.22)

project(zappy_server)

add_subdirectory(lib)

set(CMAKE_C_FLAGS "-Wall -Wextra")

include_directories(
        include/
        lib/
)

file(GLOB_RECURSE SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "src/*.c")

add_executable(${PROJECT_NAME} ${SOURCES} ${INCLUDE})

target_link_libraries(${PROJECT_NAME} PRIVATE vector)
