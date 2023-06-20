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
        Player(const Player &player) = default;
        Player(int id, std::string teamName = "", int orientation = 1,
               int level = 1) {
            this->id = id;
            this->teamName = std::move(teamName);
            this->orientation = orientation;
            this->level = level;
        }

        ~Player() final = default;

        std::string teamName;
        int id = 0;
        std::pair<int, int> pos = {0, 0};
        std::pair<int, int> nextPos = {0, 0};
        int orientation = 1;
        int level = 1;
        bool isAlive = true;
        bool inIncantation = false;
        bool isLayingEgg = false;
        bool isMoving = false;
        bool isEjecting = false;

        std::map<int, int> inventory = {{0, 0}, // food
                                        {1, 0}, // linemate
                                        {2, 0}, // deraumere
                                        {3, 0}, // sibur
                                        {4, 0}, // mendiane
                                        {5, 0}, // phiras
                                        {6, 0}}; // thystame

        const std::map<int, int> &getInventory() const final;

        void setInventory(const std::map<int, int> &inventory) final;

        bool getIsMoving() const final;

        void setIsMoving(bool isMoving) final;

        bool getIsEjecting() const final;

        void setIsEjecting(bool isEjecting) final;

        const std::string &getTeamName() const final;

        void setTeamName(const std::string &teamName) final;

        int getId() const final;

        void setId(int id) final;

        const std::pair<int, int> &getPos() const final;

        void setPos(const std::pair<int, int> &pos) final;

        const std::pair<int, int> &getNextPos() const final;

        void setNextPos(const std::pair<int, int> &pos) final;

        int getOrientation() const final;

        void setOrientation(int orientation) final;

        int getLevel() const final;

        void setLevel(int level) final;

        bool isInIncantation() const final;

        void setInIncantation(bool inIncantation) final;

        void setInventoryAtIndex(int index, int value) final;

        void opOnInventoryAtIndex(int index, int value) final;

        bool getIsAlive() const final;

        void setIsAlive(bool value) final;

        bool getIsLayingEgg() const final;

        void setIsLayingEgg(bool value) final;
    };
} // GUI
