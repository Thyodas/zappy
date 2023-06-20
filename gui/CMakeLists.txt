cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 20)

project(zappy_gui VERSION 1.0.0 LANGUAGES CXX)

include_directories(include include/interface include/libs)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(SOURCE
        Main.cpp
        Core.cpp
        GraphicalFactory.cpp
        Parser.cpp
        Map.cpp
        Cell.cpp
        ArgsParser.cpp
        libs/RayLib.cpp
        coms/Network.cpp
        coms/Network.hpp
        utils/CFunctionWrapper.cpp
        utils/CFunctionWrapper.hpp
        coms/Coms.cpp
        coms/Coms.hpp
        coms/Player.cpp
        coms/Player.hpp
        coms/Egg.cpp
        coms/Egg.hpp
        coms/Config.hpp
        )

list(TRANSFORM SOURCE PREPEND "src/")

add_compile_options(-Wall -Wextra -std=c++2a)

add_executable(${PROJECT_NAME} ${SOURCE})

set_target_properties(${PROJECT_NAME} PROPERTIES
    LINKER_LANGUAGE CXX
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
)

target_include_directories(${PROJECT_NAME} PUBLIC ./include/)
target_include_directories(${PROJECT_NAME} PUBLIC ./include/interface)
target_include_directories(${PROJECT_NAME} PUBLIC ./include/libs)
target_include_directories(${PROJECT_NAME} PUBLIC ./src/coms)

target_link_libraries(${PROJECT_NAME} raylib)
target_link_libraries(${PROJECT_NAME} pthread)
target_link_libraries(${PROJECT_NAME} dl)
target_link_libraries(${PROJECT_NAME} config++)
