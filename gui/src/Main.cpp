/*
** EPITECH PROJECT, 2023
** B-YEP-400-STG-4-1-zappy-remi.mergen
** File description:
** Main
*/

#include "Core.hpp"
#include <memory>
#include <iostream>

int main(int argc, char **argv)
{
    try {
        std::unique_ptr<GUI::ICore> core = std::make_unique<GUI::Core>();
        core->init(GUI::GraphicalLib::RAYLIB, {800, 600});
        core->run();
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }
    catch (...) {
        std::cerr << "Unknown error" << std::endl;
        return 84;
    }
    return 0;
}
