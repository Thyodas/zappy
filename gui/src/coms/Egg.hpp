/*
** EPITECH PROJECT, 2023
** zappy_gui
** File description:
** Egg.hpp
*/

#pragma once

#include <utility>

namespace GUI {

    class Egg {
    public:
        Egg() = default;

        ~Egg() = default;
        std::pair <int, int> pos = {0, 0};
        int id = 1;
        bool isAlive = true;
    };

} // GUI
