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
        Player() {};
        Player(const Player &player) = default;
        Player(int id, std::string teamName = "", int orientation = 1,
               int level = 1) {
            this->id = id;
            this->teamName = std::move(teamName);
            this->orientation = static_cast<GUI::Direction>(orientation);
            this->level = level;
        }

        ~Player() final = default;

        std::string teamName;
        int id = 0;
        GUI::Vector2i pos = {0, 0};
        GUI::Vector2i nextPos = {0, 0};
        Direction orientation = Direction::NORTH;
        int level = 1;
        bool isAlive = true;
        bool inIncantation = false;
        bool isLayingEgg = false;
        bool isMoving = false;
        bool isEjecting = false;
        GUI::Vector3f _offset = {0, 0, 0};
        int _currentFrame = 0;
        GUI::AnimationType _currentAnim = GUI::AnimationType::ANIM_IDLE;

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

        Vector2i getPos() const final;

        void setPos(Vector2i pos) final;

        GUI::Vector2i &getNextPos() final;

        void setNextPos(GUI::Vector2i &pos) final;

        GUI::Direction getOrientation() const final;

        void setOrientation(GUI::Direction orientation) final;

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

        GUI::Vector3f getOffset() const final;
        void setOffset(const GUI::Vector3f &offset) final;
        int getCurrentFrame() const final;
        void setCurrentFrame(int currentFrame) final;
        GUI::AnimationType getAnimation() const final;
        void setAnimation(GUI::AnimationType animationType) final;
        float getRotationAngle() const final;
    };
} // GUI
