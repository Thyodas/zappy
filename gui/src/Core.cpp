/*
** EPITECH PROJECT, 2023
** B-YEP-400-STG-4-1-zappy-remi.mergen
** File description:
** Core
*/

#include "Parser.hpp"
#include "Map.hpp"
#include "Core.hpp"

GUI::Core::Core() : _running(true), _scene(std::make_shared<Scene>()), _map(std::make_shared<Map>(10))
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
    _scene->getCamera()->setPosition(Vector3f(_map->getSize() * groundSize.x / 2, 20, 20));
}

void GUI::Core::handleZoom()
{
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
}

void GUI::Core::handleSelection()
{
    GUI::Vector2i currentSelection = _map->getSelectionBlock();
    int mapSize = _map->getSize();

    if (_module->isKeyReleased(GUI::Key::LEFT)) {
        currentSelection.x = (currentSelection.x - 1 + mapSize) % mapSize;
    }
    if (_module->isKeyReleased(GUI::Key::RIGHT)) {
        currentSelection.x = (currentSelection.x + 1) % mapSize;
    }
    if (_module->isKeyReleased(GUI::Key::UP)) {
        currentSelection.y = (currentSelection.y - 1 + mapSize) % mapSize;
    }
    if (_module->isKeyReleased(GUI::Key::DOWN)) {
        currentSelection.y = (currentSelection.y + 1) % mapSize;
    }

    _map->setSelectionBlock(currentSelection);
}


void GUI::Core::handleUserInput()
{
    _module->handleEvents();
    if (_module->isKeyReleased(GUI::Key::R)) {
        _map->setSelectionMode(!_map->selectionMode());
    }
    if (_map->selectionMode())
        handleSelection();
    else
        handleZoom();
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

void GUI::Core::drawGround()
{
    GUI::Vector3f grassSize = _module->getModelSize(ModelEntity::GRASS_BLOCK);
    for (int y = -(_map->getSize() * grassSize.x / 2 - (grassSize.x / 2)), yy = 0; y <= (_map->getSize() * grassSize.x / 2 - (grassSize.x / 2)); y += 2, yy++) {
        for (int x = -(_map->getSize() * grassSize.z / 2 - (grassSize.z / 2)), xx = 0; x <= (_map->getSize() * grassSize.z / 2 - (grassSize.z / 2)); x += 2, xx++) {
            if (_map->selectionMode() && _map->getSelectionBlock() == (GUI::Vector2i){xx, yy})
                continue;
            else
                _module->drawModel(ModelEntity::GRASS_BLOCK, Vector3f(x, -grassSize.y, y), 1, Vector3f(0, 0, 0));
        }
    }
}

void GUI::Core::draw()
{
    _module->preDraw(_scene->getCamera());
    this->drawGround();
    _module->drawGrid(_map->getSize(), _module->getModelSize(ModelEntity::GRASS_BLOCK).x);
    _module->postDraw();
}
