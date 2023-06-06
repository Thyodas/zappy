/*
** EPITECH PROJECT, 2023
** B-YEP-400-STG-4-1-zappy-remi.mergen
** File description:
** Core
*/

#include "Parser.hpp"
#include "Core.hpp"

GUI::Core::Core() : _running(true)
{
    IParser *parser = new Parser("config.cfg");
    _config = parser->parseConfig();
    delete parser;

}

GUI::Core::~Core()
{
}

void GUI::Core::init(GUI::GraphicalLib lib, GUI::Vector2i windowSize)
{
    _windowSize = windowSize;
    _module->init(windowSize);
    _module->loadModels(_config.models);
}

void GUI::Core::run()
{
    while (_running) {
    }
}
