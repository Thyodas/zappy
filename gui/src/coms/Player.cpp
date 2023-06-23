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

    Vector2i Player::getPos() const {
        return pos;
    }

    void Player::setPos(Vector2i value) {
        Player::pos = value;
    }

    GUI::Direction Player::getOrientation() const {
        return orientation;
    }

    void Player::setOrientation(GUI::Direction direction) {
        Player::orientation = direction;
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

    void Player::opOnInventoryAtIndex(int index, int value) {
        Player::inventory[index] += value;
    }

    bool Player::getIsAlive() const {
        return isAlive;
    }

    void Player::setIsAlive(bool value) {
        Player::isAlive = value;
    }

    bool Player::getIsLayingEgg() const {
        return isLayingEgg;
    }

    void Player::setIsLayingEgg(bool value) {
        Player::isLayingEgg = value;
    }

    bool Player::getIsMoving() const {
        return isMoving;
    }

    void Player::setIsMoving(bool value) {
        Player::isMoving = value;
    }

    bool Player::getIsEjecting() const {
        return isEjecting;
    }

    void Player::setIsEjecting(bool value) {
        Player::isEjecting = value;
    }

    GUI::Vector2i &Player::getNextPos() {
        return nextPos;
    }

    void Player::setNextPos(GUI::Vector2i &value) {
        Player::nextPos = value;
    }

    GUI::Vector3f Player::getOffset() const {
        return _offset;
    }

    void Player::setOffset(const GUI::Vector3f &offset) {
        _offset = offset;
    }

    int Player::getCurrentFrame() const {
        return _currentFrame;
    }

    void Player::setCurrentFrame(int currentFrame) {
        _currentFrame = currentFrame;
    }

    GUI::AnimationType Player::getAnimation() const {
        return _currentAnim;
    }

    void Player::setAnimation(GUI::AnimationType animationType) {
        _currentAnim = animationType;
    }

    float Player::getRotationAngle() const {
        switch (orientation) {
            case GUI::Direction::NORTH:
                return 0;
            case GUI::Direction::EAST:
                return 90;
            case GUI::Direction::SOUTH:
                return 180;
            case GUI::Direction::WEST:
                return 270;
            default:
                return 0;
        }
    }
} // GUI
