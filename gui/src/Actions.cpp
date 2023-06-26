/*
** EPITECH PROJECT, 2023
** gui
** File description:
** Actions
*/

#include "Actions.hpp"
#include <algorithm>

GUI::Actions::Actions() : _frequence(-1)
{
    _actions[MOVE] = &Actions::c_move;
    _actions[TAKE_OBJECT] = &Actions::c_takeObject;
    _actions[SET_OBJECT] = &Actions::c_dropObject;
    _actions[DIE] = &Actions::c_die;
    _actions[BROADCAST] = &Actions::c_broadcast;
    _actions[INCANTATION_BEGIN] = &Actions::c_incantationBegin;
}

void GUI::Actions::addAction(ActionType type, int playerId, Direction direction, Vector2i pos, float timestamp)
{
    _playersActions[playerId].push_back(ActionData(type, playerId, direction, pos, timestamp));
}

void GUI::Actions::addAction(ActionType type, int playerId, float timestamp)
{
    _playersActions[playerId].push_back(ActionData(type, playerId, timestamp));
}

void GUI::Actions::addAction(ActionData action)
{
    _playersActions[action.getPlayerId()].push_back(ActionData(action));
}

void GUI::Actions::deleteAction(int playerId)
{
    _playersActions[playerId].pop_front();
}

bool GUI::Actions::isAction(int playerId)
{
    return _playersActions[playerId].size() > 0;
}

GUI::ActionData GUI::Actions::getAction(int playerId)
{
    return _playersActions[playerId].front();
}

void GUI::Actions::setGridSize(GUI::Vector3f size)
{
    _gridSize = size;
}

GUI::AnimationType GUI::Actions::execute(std::shared_ptr<IPlayer>& player, std::shared_ptr<ICell>& cell, ActionData &data, std::map<int, std::shared_ptr<IPlayer>>& players, double now)
{
    return (this->*_actions[data.getType()])(player, data, cell, players, now);
}

double GUI::Actions::getDuration(ActionType type)
{
    return _actionsTime[type];
}

void GUI::Actions::setFrequence(double frequence)
{
    _frequence = frequence;
    _actionsTime[MOVE] = 7 / _frequence;
    _actionsTime[LOOK] = 7 / _frequence;
    _actionsTime[INVENTORY] = 1 / _frequence;
    _actionsTime[BROADCAST] = 7 / _frequence;
    _actionsTime[FORK] = 42 / _frequence;
    _actionsTime[EJECT] = 7 / _frequence;
    _actionsTime[DIE] = 7 / _frequence;
    _actionsTime[TAKE_OBJECT] = 7 / _frequence;
    _actionsTime[SET_OBJECT] = 7 / _frequence;
    _actionsTime[INCANTATION_BEGIN] = 300 / _frequence;
}

// Uncomment to move player while animating
GUI::AnimationType GUI::Actions::c_move(std::shared_ptr<IPlayer>& player, ActionData &data, [[maybe_unused]] std::shared_ptr<ICell>& cell, [[maybe_unused]] std::map<int, std::shared_ptr<IPlayer>>& players, double now)
{
    if (player->getAnimation() != ANIM_WALKING && player->getPos() != data.getPos())
        player->setAnimation(ANIM_WALKING);
    double elapsed = now - data.getTimestamp();

    if (elapsed < _actionsTime[MOVE] * 1000) {
        // double progress = elapsed / (_actionsTime[MOVE] * 1000);
        // float toMove = progress * _gridSize.z;
        // GUI::Vector3f offset = player->getOffset();
        switch (data.getDirection()) {
            case NORTH:
                // player->setOffset({0, 0, -toMove});
                player->setOrientation(NORTH);
                break;
            case SOUTH:
                // player->setOffset({0, 0, toMove});
                player->setOrientation(SOUTH);
                break;
            case WEST:
                // player->setOffset({-toMove, 0, 0});
                player->setOrientation(WEST);
                break;
            case EAST:
                // player->setOffset({toMove, 0, 0});
                player->setOrientation(EAST);
                break;
            default:
                break;
        }
        player->setOffset({0, 0, 0});
        return ANIM_WALKING;
    } else {
        player->setOffset({0, 0, 0});
        player->setAnimation(ANIM_IDLE);
        player->setPos(data.getPos());
        return AnimationType::ANIM_END;
    }
}

GUI::AnimationType GUI::Actions::c_takeObject(std::shared_ptr<IPlayer>& player, ActionData &data, [[maybe_unused]] std::shared_ptr<ICell>& cell, [[maybe_unused]] std::map<int, std::shared_ptr<IPlayer>>& players, double now)
{
    if (player->getAnimation() != ANIM_CROUNCH)
        player->setAnimation(ANIM_CROUNCH);
    double elapsed = now - data.getTimestamp();

    if (elapsed < _actionsTime[TAKE_OBJECT] * 1000) {
        return ANIM_CROUNCH;
    } else {
        player->setAnimation(ANIM_IDLE);
        return AnimationType::ANIM_END;
    }
}

GUI::AnimationType GUI::Actions::c_dropObject(std::shared_ptr<IPlayer>& player, ActionData &data, [[maybe_unused]] std::shared_ptr<ICell>& cell, [[maybe_unused]] std::map<int, std::shared_ptr<IPlayer>>& players, double now)
{
    if (player->getAnimation() != ANIM_CROUNCH)
        player->setAnimation(ANIM_CROUNCH);
    double elapsed = now - data.getTimestamp();

    if (elapsed < _actionsTime[SET_OBJECT] * 1000) {
        return ANIM_CROUNCH;
    } else {
        player->setAnimation(ANIM_IDLE);
        return AnimationType::ANIM_END;
    }
}

GUI::AnimationType GUI::Actions::c_die(std::shared_ptr<IPlayer> &player, ActionData &data, [[maybe_unused]] std::shared_ptr<ICell>& cell, [[maybe_unused]] std::map<int, std::shared_ptr<IPlayer>>& players, double now)
{
    if (player->getAnimation() != ANIM_DIE)
        player->setAnimation(ANIM_DIE);
    double elapsed = now - data.getTimestamp();

    if (elapsed < _actionsTime[DIE] * 1000) {
        return ANIM_DIE;
    } else {
        player->setAnimation(ANIM_IDLE);
        return AnimationType::ANIM_END;
    }
}

GUI::AnimationType GUI::Actions::c_broadcast(std::shared_ptr<IPlayer> &player, ActionData &data, [[maybe_unused]] std::shared_ptr<ICell>& cell, [[maybe_unused]] std::map<int, std::shared_ptr<IPlayer>>& players, double now)
{
    if (player->getAnimation() != ANIM_TPOSE)
        player->setAnimation(ANIM_TPOSE);
    double elapsed = now - data.getTimestamp();

    if (elapsed < _actionsTime[BROADCAST] * 1000) {
        return ANIM_TPOSE;
    } else {
        player->setAnimation(ANIM_IDLE);
        return AnimationType::ANIM_END;
    }
}

GUI::AnimationType GUI::Actions::c_incantationBegin(std::shared_ptr<IPlayer> &player, ActionData &data, [[maybe_unused]] std::shared_ptr<ICell>& cell, [[maybe_unused]] std::map<int, std::shared_ptr<IPlayer>>& players, double now)
{
    if (player->getAnimation() != ANIM_SPELL)
        player->setAnimation(ANIM_SPELL);
    double elapsed = now - data.getTimestamp();

    if (elapsed < _actionsTime[INCANTATION_BEGIN] * 1000) {
        return ANIM_SPELL;
    } else {
        player->setAnimation(ANIM_IDLE);
        return AnimationType::ANIM_END;
    }
}
