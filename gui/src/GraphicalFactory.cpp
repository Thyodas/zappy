/*
** EPITECH PROJECT, 2023
** B-YEP-400-STG-4-1-zappy-remi.mergen
** File description:
** GraphicalFactory
*/

#include "GraphicalFactory.hpp"

GUI::GraphicalFactory::GraphicalFactory()
{
}

GUI::GraphicalFactory::~GraphicalFactory()
{
}

std::shared_ptr<GUI::IGraphicalModule> GUI::GraphicalFactory::createModule(GraphicalLib lib)
{
    if (lib == GUI::GraphicalLib::RAYLIB)
        return std::make_shared<GUI::RayLib>();
    throw std::runtime_error("Unrecognized graphical library");
}
