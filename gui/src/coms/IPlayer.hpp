/*
** EPITECH PROJECT, 2023
** zappy_gui
** File description:
** IPlayer.hpp
*/

#pragma once


class IPlayer {
public:
    virtual ~IPlayer() = default;

    virtual const std::string &getTeamName() const = 0;

    virtual const std::map<int, int> &getInventory() const = 0;

    virtual void setInventory(const std::map<int, int> &value) = 0;

    virtual void setInventoryAtIndex(int index, int value) = 0;

    virtual void setTeamName(const std::string &value) = 0;

    virtual int getId() const = 0;

    virtual void setId(int value) = 0;

    virtual const std::pair<int, int> &getPos() const = 0;

    virtual void setPos(const std::pair<int, int> &value) = 0;

    virtual int getOrientation() const = 0;

    virtual void setOrientation(int value) = 0;

    virtual int getLevel() const = 0;

    virtual void setLevel(int value) = 0;

    virtual bool isInIncantation() const = 0;

    virtual void setInIncantation(bool value) = 0;

    virtual bool getIsAlive() const = 0;

    virtual void setIsAlive(bool isAlive) = 0;

};
