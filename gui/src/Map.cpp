/*
** EPITECH PROJECT, 2023
** gui
** File description:
** Map
*/

#include "Map.hpp"
#include <iostream>

GUI::Map::Map(GUI::Vector2i ssize, std::map<GUI::Vector2i, std::vector<int>> mapContent) : _size(ssize), _selectionMode(false), _selectionBlock((GUI::Vector2i){0, 0})
{
    int count = 0;
    _map.resize(_size.y);
    for (int i = 0; i < _size.y; i++) {
        _map[i].resize(_size.x);
        for (int j = 0; j < _size.x; j++) {
            count++;
            _map[i][j] = std::make_shared<GUI::Cell>((GUI::Vector2i){j, i}, mapContent[(GUI::Vector2i){j, i}]);
        }
    }
}

GUI::Map::~Map()
{
}

GUI::Vector2i GUI::Map::getSize() const
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
