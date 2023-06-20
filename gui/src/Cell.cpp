/*
** EPITECH PROJECT, 2023
** gui
** File description:
** Cell
*/

#include "Cell.hpp"
#include <iostream>

GUI::Cell::Cell(GUI::Vector2i pos, std::vector<int> objects) : _pos(pos)
{
    for (int i = 0; i < GUI::Object::OBJ_LAST_ELEMENT; i++) {
        _objects[(GUI::Object)i] = objects[i];
    }
}

GUI::Cell::~Cell()
{
}

GUI::Vector2i GUI::Cell::getPos() const
{
    return _pos;
}

std::unordered_map<GUI::Object, int> GUI::Cell::getObjects() const
{
    return _objects;
}

void GUI::Cell::addObject(GUI::Object object)
{
    _objects[object] += 1;
}
