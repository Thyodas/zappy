/*
** EPITECH PROJECT, 2023
** gui
** File description:
** Map
*/

#include "Map.hpp"

GUI::Map::Map(GUI::Vector2i ssize) : _size(ssize)
{
    _map.reserve(ssize.y * ssize.x);
    for (int i = 0; i < ssize.y; i++) {
        _map[i].reserve(ssize.x);
        for (int j = 0; j < ssize.x; j++) {
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
