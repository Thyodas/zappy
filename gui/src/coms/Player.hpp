/*
** EPITECH PROJECT, 2023
** zappy_gui
** File description:
** Player.hpp
*/

#pragma once

#include <utility>
#include <string>
#include <map>
#include "IPlayer.hpp"

namespace GUI {

    class Player final : public IPlayer {
    public:
        Player() = default;

        ~Player() final = default;

        std::string teamName;
        int id = 0;
        std::pair<int, int> pos = {0, 0};
        int orientation = 1;
        int level = 0;
        bool isAlive = true;
        bool inIncantation = false;
        std::map<int, int> inventory = {{0, 0}, // food
                                        {1, 0}, // linemate
                                        {2, 0}, // deraumere
                                        {3, 0}, // sibur
                                        {4, 0}, // mendiane
                                        {5, 0}, // phiras
                                        {6, 0}}; // thystame

        const std::map<int, int> &getInventory() const final;

        void setInventory(const std::map<int, int> &inventory) final;

        const std::string &getTeamName() const final;

        void setTeamName(const std::string &teamName) final;

        int getId() const final;

        void setId(int id) final;

        const std::pair<int, int> &getPos() const final;

        void setPos(const std::pair<int, int> &pos) final;

        int getOrientation() const final;

        void setOrientation(int orientation) final;

        int getLevel() const final;

        void setLevel(int level) final;

        bool isInIncantation() const final;

        void setInIncantation(bool inIncantation) final;

        void setInventoryAtIndex(int index, int value) final;

        bool getIsAlive() const final;

        void setIsAlive(bool value) final;
    };
} // GUI
