/*
** EPITECH PROJECT, 2023
** B-YEP-400-STG-4-1-zappy-remi.mergen
** File description:
** Core
*/

#include "Parser.hpp"
#include "Map.hpp"
#include "Core.hpp"

GUI::Core::Core() : _running(true), _scene(std::make_shared<Scene>()), _map(std::make_shared<Map>(GUI::Vector2i{10, 10}))
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

void GUI::Core::handleUserInput()
{
    _module->handleEvents();
    if (_module->isKeyPressed(GUI::Key::LEFT)) {
        _scene->getCamera()->rotateX(0.03);
    }
    if (_module->isKeyPressed(GUI::Key::RIGHT)) {
        _scene->getCamera()->rotateX(-0.03);
    }
    if (_module->isKeyPressed(GUI::Key::UP)) {
        _scene->getCamera()->rotateY(0.03);
    }
    if (_module->isKeyPressed(GUI::Key::DOWN)) {
        _scene->getCamera()->rotateY(-0.03);
    }
    if (_module->isKeyPressed(GUI::Key::ESCAPE)) {
        _running = false;
    }
    if (_module->isKeyPressed(GUI::Key::Z)) {
        _scene->getCamera()->zoom(0.2);
    }
    if (_module->isKeyPressed(GUI::Key::S)) {
        _scene->getCamera()->zoom(-0.2);
    }
}

void GUI::Core::run()
{
    while (_running) {
        handleUserInput();
        _module->preDraw(_scene->getCamera());
        _module->drawModel(ModelEntity::GOLEM, Vector3f(0, 0, 0), 1, Vector3f(0, 0, 0));
        _module->postDraw();
    }
    _module->close();
}
