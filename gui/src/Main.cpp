/*
** EPITECH PROJECT, 2023
** B-YEP-400-STG-4-1-zappy-remi.mergen
** File description:
** Main
*/

#include <iostream>
#include "Core.hpp"
#include <memory>
#include <iostream>
#include "Message.h"
#include "ArgsParser.hpp"

int main([[maybe_unused]] int argc, char **argv)
{
    if (argc == 2 && std::string(argv[1]).compare("-help") == 0) {
        std::cout << HELP_MESSAGE << std::endl;
        return 0;
    }
    try {
        GUI::Args args = GUI::ArgsParser::parseArgs(argc, argv);
        std::unique_ptr<GUI::ICore> core = std::make_unique<GUI::Core>();
        core->init(GUI::GraphicalLib::RAYLIB, {800, 600});
        core->run();
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }
    catch (...) {
        std::cerr << "Unknown error" << std::endl;
        return 84;
    }
    return 0;
}
