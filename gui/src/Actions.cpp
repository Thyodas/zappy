/*
** EPITECH PROJECT, 2023
** gui
** File description:
** Actions
*/

#include "Actions.hpp"
#include <algorithm>

GUI::Actions::Actions() : _frequence(100)
{
    _actionsTime[MOVE] = 7 / _frequence;
    _actionsTime[LOOK] = 7 / _frequence;
    _actionsTime[INVENTORY] = 1 / _frequence;
    _actionsTime[BROADCAST] = 7 / _frequence;
    _actionsTime[CONNECT_NBR] = 0 / _frequence;
    _actionsTime[FORK] = 42 / _frequence;
    _actionsTime[EJECT] = 7 / _frequence;
    _actionsTime[DIE] = 0 / _frequence;
    _actionsTime[TAKE_OBJECT] = 7 / _frequence;
    _actionsTime[SET_OBJECT] = 7 / _frequence;
    _actionsTime[INCANTATION] = 300 / _frequence;

    _actions[MOVE] = &Actions::c_move;
}

void GUI::Actions::addAction(ActionType type, int playerId, Direction direction, Vector2i pos, float timestamp)
{
    _playersActions[playerId].push_back(ActionData(type, playerId, direction, pos, timestamp));
}

void GUI::Actions::addAction(ActionType type, int playerId, float timestamp)
{
    _playersActions[playerId].push_back(ActionData(type, playerId, timestamp));
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

GUI::AnimationType GUI::Actions::c_move(std::shared_ptr<IPlayer>& player, ActionData &data, double now)
{
    if (player->getAnimation() != ANIM_WALKING && player->getPos() != data.getPos())
        player->setAnimation(ANIM_WALKING);
    double elapsed = now - data.getTimestamp();

    if (elapsed < _actionsTime[MOVE] * 1000) {
        double progress = elapsed / (_actionsTime[MOVE] * 1000);
        float toMove = progress * _gridSize.z;
        GUI::Vector3f offset = player->getOffset();

        switch (data.getDirection()) {
            case NORTH:
                player->setOffset({0, 0, -toMove});
                player->setOrientation(NORTH);
                break;
            case SOUTH:
                player->setOffset({0, 0, toMove});
                player->setOrientation(SOUTH);
                break;
            case WEST:
                player->setOffset({-toMove, 0, 0});
                player->setOrientation(WEST);
                break;
            case EAST:
                player->setOffset({toMove, 0, 0});
                player->setOrientation(EAST);
                break;
            default:
                break;
        }
        return ANIM_WALKING;
    } else {
        player->setOffset({0, 0, 0});
        player->setAnimation(ANIM_IDLE);
        player->setPos(data.getPos());
        return AnimationType::ANIM_END;
    }
}

void GUI::Actions::setGridSize(GUI::Vector3f size)
{
    _gridSize = size;
}

GUI::AnimationType GUI::Actions::execute(std::shared_ptr<IPlayer>& player, ActionData &data, double now)
{
    return (this->*_actions[data.getType()])(player, data, now);
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
    _actionsTime[CONNECT_NBR] = 0 / _frequence;
    _actionsTime[FORK] = 42 / _frequence;
    _actionsTime[EJECT] = 7 / _frequence;
    _actionsTime[DIE] = 0 / _frequence;
    _actionsTime[TAKE_OBJECT] = 7 / _frequence;
    _actionsTime[SET_OBJECT] = 7 / _frequence;
    _actionsTime[INCANTATION] = 300 / _frequence;
}
