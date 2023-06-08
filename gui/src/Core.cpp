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

    GUI::Vector3f groundSize = _module->getModelSize(ModelEntity::GRASS_BLOCK);
    _scene->getCamera()->setTarget(Vector3f(_map->getSize().x * groundSize.x / 2, 0, _map->getSize().y * groundSize.z / 2));
    _scene->getCamera()->setPosition(Vector3f(_map->getSize().x * groundSize.x / 2, 20, -20));
}

void GUI::Core::handleUserInput()
{
    _module->handleEvents();
    if (_module->isKeyPressed(GUI::Key::LEFT)) {
        _scene->getCamera()->rotateX(1);
    }
    if (_module->isKeyPressed(GUI::Key::RIGHT)) {
        _scene->getCamera()->rotateX(-1);
    }
    if (_module->isKeyPressed(GUI::Key::UP)) {
        _scene->getCamera()->rotateY(1);
    }
    if (_module->isKeyPressed(GUI::Key::DOWN)) {
        _scene->getCamera()->rotateY(-1);
    }
    if (_module->isKeyPressed(GUI::Key::ESCAPE)) {
        _running = false;
    }
    if (_module->isKeyPressed(GUI::Key::Z)) {
        _scene->getCamera()->zoom(0.1);
    }
    if (_module->isKeyPressed(GUI::Key::S)) {
        _scene->getCamera()->zoom(-0.1);
    }
}

void GUI::Core::run()
{
    while (_running) {
        handleUserInput();
        this->draw();
    }
    _module->close();
}

void GUI::Core::draw()
{
    _module->preDraw(_scene->getCamera());
    _module->drawModel(ModelEntity::GOLEM, Vector3f(0, 0, 0), 1, Vector3f(0, 0, 0));
    GUI::Vector3f grassSize = _module->getModelSize(ModelEntity::GRASS_BLOCK);
    for (int y = 0; y < _map->getSize().y; y++) {
        for (int x = 0; x < _map->getSize().x; x++) {
            _module->drawModel(ModelEntity::GRASS_BLOCK, Vector3f(x * grassSize.x, 0, y * grassSize.z), 1, Vector3f(0, 0, 0));
        }
    }
    _module->postDraw();
}
