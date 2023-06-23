/*
** EPITECH PROJECT, 2023
** zappy_gui
** File description:
** Egg.hpp
*/

#pragma once

#include <utility>
#include "Vector2i.hpp"

namespace GUI {

    class Egg {
    public:
        Egg() = default;

        ~Egg() = default;
        GUI::Vector2i pos = {0, 0};
        int id = 1;
        bool isAlive = true;
    };

} // GUI
