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
            Egg(int id, bool alive, const GUI::Vector2i &pos) : id(id), alive(alive), pos(pos) {};
            Egg() : id(0), alive(false), pos(GUI::Vector2i(0, 0)) {};
            ~Egg() = default;
            int id;
            bool alive;
            GUI::Vector2i pos;
    };
};
