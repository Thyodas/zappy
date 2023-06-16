/*
** EPITECH PROJECT, 2023
** gui
** File description:
** Map
*/

#include "Map.hpp"
#include <iostream>

GUI::Map::Map(int ssize) : _size(ssize), _selectionMode(false), _selectionBlock((GUI::Vector2i){0, 0})
{
    int count = 0;
    _map.reserve(_size);
    for (int i = 0; i < _size; i++) {
        _map[i].reserve(_size);
        for (int j = 0; j < _size; j++) {
            count++;
            _map[i][j] = std::make_shared<GUI::Cell>((GUI::Vector2i){j, i});
        }
    }

    _objectsDensity = {
        {GUI::Object::OBJ_FOOD, 0.5},
        {GUI::Object::OBJ_LINEMATE, 0.3},
        {GUI::Object::OBJ_DERAUMERE, 0.15},
        {GUI::Object::OBJ_SIBUR, 0.1},
        {GUI::Object::OBJ_MENDIANE, 0.1},
        {GUI::Object::OBJ_PHIRAS, 0.08},
        {GUI::Object::OBJ_THYSTAME, 0.05}
    };
}

GUI::Map::~Map()
{
}

int GUI::Map::getSize() const
{
    return _size;
}

std::shared_ptr<GUI::ICell>& GUI::Map::getCell(GUI::Vector2i pos)
{
    return _map[pos.y][pos.x];
}

bool GUI::Map::selectionMode() const
{
    return _selectionMode;
}

void GUI::Map::setSelectionMode(bool selectionMode)
{
    _selectionMode = selectionMode;
}

GUI::Vector2i GUI::Map::getSelectionBlock() const
{
    return _selectionBlock;
}

void GUI::Map::setSelectionBlock(GUI::Vector2i selectionBlock)
{
    _selectionBlock = selectionBlock;
}
