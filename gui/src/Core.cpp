/*
** EPITECH PROJECT, 2023
** B-YEP-400-STG-4-1-zappy-remi.mergen
** File description:
** Core
*/

#include "Parser.hpp"
#include "Core.hpp"

GUI::Core::Core() : _running(true), _scene(std::make_shared<Scene>())
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
    _module = GUI::GraphicalFactory::createModule(lib);
    _windowSize = windowSize;
    _module->init(_windowSize);
    _module->loadModels(_config.models);
}

void GUI::Core::run()
{
    while (_running) {
        _module->preDraw(_scene->getCamera());
        _module->drawModel(ModelEntity::GOLEM, Vector3f(0, 0, 0), 1, Vector3f(0, 0, 0));
        _module->postDraw();
    }
}
