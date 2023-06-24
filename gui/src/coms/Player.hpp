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
        Player(int id, std::string teamName, int orientation,
               int level);

        ~Player() final = default;

        std::string teamName;
        int id = 0;
        GUI::Vector2i pos = {0, 0};
        GUI::Vector2i nextPos = {0, 0};
        Direction orientation = Direction::NORTH;
        int level = 1;
        bool isAlive = true;
        bool inIncantation = false;
        bool isMoving = false;
        bool isEjecting = false;
        GUI::Vector3f _offset = {0, 0, 0};
        int _currentFrame = 0;
        GUI::AnimationType _currentAnim = GUI::AnimationType::ANIM_IDLE;
        std::unordered_map<GUI::Object, int> _inventory;

        std::unordered_map<GUI::Object, int> getInventory() final;
        void setInventory(const std::unordered_map<GUI::Object, int> &inventory) final;
        int getInventoryObject(GUI::Object object) final;
        void setInventoryObject(GUI::Object object, int value) final;

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

        bool getIsAlive() const final;

        void setIsAlive(bool value) final;

        GUI::Vector3f getOffset() const final;
        void setOffset(const GUI::Vector3f &offset) final;
        int getCurrentFrame() const final;
        void setCurrentFrame(int currentFrame) final;
        GUI::AnimationType getAnimation() const final;
        void setAnimation(GUI::AnimationType animationType) final;
        float getRotationAngle() const final;
    };
} // GUI
