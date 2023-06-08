/*
** EPITECH PROJECT, 2023
** B-YEP-400-STG-4-1-zappy-remi.mergen
** File description:
** Main
*/

#include "Core.hpp"
#include <memory>

int main(int argc, char **argv)
{
    std::unique_ptr<GUI::ICore> core = std::make_unique<GUI::Core>();
    core->init(GUI::GraphicalLib::RAYLIB, {800, 600});
    core->run();
    return 0;
}
