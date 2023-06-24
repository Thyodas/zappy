/*
** EPITECH PROJECT, 2023
** zappy_gui
** File description:
** IPlayer.hpp
*/

#pragma once

#include <map>
#include <string>
#include "Vector3f.hpp"
#include "AnimationType.hpp"
#include "Vector2i.hpp"
#include "ICell.hpp"
#include <unordered_map>

class IPlayer {
public:
    virtual ~IPlayer() = default;

    virtual const std::string &getTeamName() const = 0;

    virtual std::unordered_map<GUI::Object, int> getInventory() = 0;
    virtual void setInventory(const std::unordered_map<GUI::Object, int> &inventory) = 0;


    virtual int getInventoryObject(GUI::Object object) = 0;
    virtual void setInventoryObject(GUI::Object object, int value) = 0;

    virtual bool getIsMoving() const = 0;

    virtual void setIsMoving(bool isMoving) = 0;

    virtual bool getIsEjecting() const = 0;

    virtual void setIsEjecting(bool isEjecting) = 0;

    virtual void setTeamName(const std::string &value) = 0;

    virtual int getId() const = 0;

    virtual void setId(int value) = 0;

    virtual GUI::Vector2i getPos() const = 0;

    virtual void setPos(GUI::Vector2i value) = 0;

    virtual GUI::Vector2i &getNextPos() = 0;

    virtual void setNextPos(GUI::Vector2i &pos) = 0;

    virtual GUI::Direction getOrientation() const = 0;

    virtual void setOrientation(GUI::Direction value) = 0;

    virtual int getLevel() const = 0;

    virtual void setLevel(int value) = 0;

    virtual bool isInIncantation() const = 0;

    virtual void setInIncantation(bool value) = 0;

    virtual bool getIsAlive() const = 0;

    virtual void setIsAlive(bool isAlive) = 0;

    //
    virtual GUI::Vector3f getOffset() const = 0;
    virtual void setOffset(const GUI::Vector3f &offset) = 0;
    virtual int getCurrentFrame() const = 0;
    virtual void setCurrentFrame(int currentFrame) = 0;
    virtual void setAnimation(GUI::AnimationType type) = 0;
    virtual GUI::AnimationType getAnimation() const = 0;
    virtual float getRotationAngle() const = 0;
    //
};
