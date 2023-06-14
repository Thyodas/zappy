/*
** EPITECH PROJECT, 2023
** gui
** File description:
** Cell
*/

#include "Cell.hpp"

GUI::Cell::Cell(GUI::Vector2i pos) : _pos(pos)
{
    // TEST
    for (int i = 0; i <= 6; i++)
        _objects[static_cast<GUI::Object>(i)] = 1;
    // END OF TEST
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
