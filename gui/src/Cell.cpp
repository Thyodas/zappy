/*
** EPITECH PROJECT, 2023
** gui
** File description:
** Cell
*/

#include "Cell.hpp"

GUI::Cell::Cell(GUI::Vector2i pos) : _pos(pos)
{
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
