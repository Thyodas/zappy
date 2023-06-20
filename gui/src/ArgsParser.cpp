/*
** EPITECH PROJECT, 2023
** gui
** File description:
** ArgsParser
*/

#include "ArgsParser.hpp"
#include "Message.h"
#include <stdexcept>

GUI::ArgsParser::ArgsParser()
{
}

GUI::ArgsParser::~ArgsParser()
{
}

GUI::Args GUI::ArgsParser::parseArgs(int argc, char **argv)
{
    if (argc != 5)
        throw std::runtime_error("Invalid number of arguments");
    Args args = {0, ""};

    for (int i = 1; i < argc; i++) {
        if (std::string(argv[i]) == "-p" && i + 1 < argc)
            args.port = std::stoi(argv[i + 1]);
        if (std::string(argv[i]) == "-h" && i + 1 < argc)
            args.machine = argv[i + 1];
    }
    if (args.port == 0 || args.machine == "")
        throw std::runtime_error("Invalid arguments");
    return args;
}
