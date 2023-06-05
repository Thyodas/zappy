/*
** EPITECH PROJECT, 2023
** B-YEP-400-STG-4-1-zappy-remi.mergen
** File description:
** Main
*/

#include "Core.hpp"

int main(int argc, char **argv)
{
    Core core;
    core.init(GUI::GraphicalLib::RAYLIB, {1920, 1080});
    core.run();
    return 0;
}
