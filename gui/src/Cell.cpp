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

std::vector<GUI::Object> GUI::Cell::getObjects() const
{
    return _objects;
}
