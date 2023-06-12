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

target_link_libraries(${PROJECT_NAME} PRIVATE vector buffer)

# Add the criterion library
find_library(CRITERION_LIB criterion)

# Enable testing
enable_testing()


# Add the unit_tests rule

file(GLOB_RECURSE TEST_SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "lib/*.c" "tests/*.c")
add_executable(unit_tests ${TEST_SOURCES})
target_link_libraries(unit_tests PRIVATE ${CRITERION_LIB} gcov)
set_target_properties(unit_tests PROPERTIES COMPILE_FLAGS "-g -Wall -Wextra --coverage -fprofile-arcs -ftest-coverage")
add_test(NAME unit_tests COMMAND unit_tests)
