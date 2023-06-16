/*
** EPITECH PROJECT, 2023
** zappy_gui
** File description:
** Player.cpp
*/

#include "Player.hpp"

namespace GUI {
    const std::string &Player::getTeamName() const {
        return teamName;
    }

    void Player::setTeamName(const std::string &value) {
        Player::teamName = value;
    }

    int Player::getId() const {
        return id;
    }

    void Player::setId(int value) {
        Player::id = value;
    }

    const std::pair<int, int> &Player::getPos() const {
        return pos;
    }

    void Player::setPos(const std::pair<int, int> &value) {
        Player::pos = value;
    }

    int Player::getOrientation() const {
        return orientation;
    }

    void Player::setOrientation(int value) {
        Player::orientation = value;
    }

    int Player::getLevel() const {
        return level;
    }

    void Player::setLevel(int value) {
        Player::level = value;
    }

    bool Player::isInIncantation() const {
        return inIncantation;
    }

    void Player::setInIncantation(bool value) {
        Player::inIncantation = value;
    }

    const std::map<int, int> &Player::getInventory() const {
        return inventory;
    }

    void Player::setInventory(const std::map<int, int> &value) {
        Player::inventory = value;
    }

    void Player::setInventoryAtIndex(int index, int value) {
        Player::inventory[index] = value;
    }

    bool Player::getIsAlive() const {
        return isAlive;
    }

    void Player::setIsAlive(bool value) {
        Player::isAlive = value;
    }
} // GUI
