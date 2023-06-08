/*
** EPITECH PROJECT, 2023
** gui
** File description:
** Map
*/

#include "Map.hpp"
#include <iostream>

GUI::Map::Map(GUI::Vector2i ssize) : _size(ssize)
{
    int count = 0;
    _map.reserve(ssize.y);
    for (int i = 0; i < ssize.y; i++) {
        _map[i].reserve(ssize.x);
        for (int j = 0; j < ssize.x; j++) {
            count++;
            _map[i][j] = std::make_shared<GUI::Cell>((GUI::Vector2i){j, i});
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
