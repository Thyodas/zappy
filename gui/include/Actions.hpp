/*
** EPITECH PROJECT, 2023
** gui
** File description:
** Actions
*/

#ifndef ACTIONS_HPP_
    #define ACTIONS_HPP_

    #include "IPlayer.hpp"
    #include "Vector2i.hpp"
    #include "AnimationType.hpp"

    #include <functional>
    #include <vector>
    #include <memory>
    #include <unordered_map>
    #include <deque>

    #define FORWARD_TIME 7.0f

namespace GUI {
    enum ActionType {
        MOVE,
        LOOK,
        INVENTORY,
        BROADCAST,
        CONNECT_NBR,
        FORK,
        EJECT,
        DIE,
        TAKE_OBJECT,
        SET_OBJECT,
        INCANTATION
    };

    class ActionData {
        public:
            ActionData(ActionType type, int playerId, Direction direction, Vector2i pos, float timestamp) : _timestamp(timestamp), _type(type), _playerId(playerId), _inProgress(false), _direction(direction), _pos(pos) {};
            ActionData(ActionType type, int playerId, float timestamp) : _timestamp(timestamp), _type(type), _playerId(playerId), _inProgress(false), _direction(D_VOID), _pos({0, 0}) {};
            ~ActionData() = default;

            bool operator==(const ActionData& action) {
                return _type == action.getType() && _playerId == action.getPlayerId();
            };

            ActionType getType() const {
                return _type;
            };
            int getPlayerId() const {
                return _playerId;
            };
            double getTimestamp() const {
                return _timestamp;
            };
            void setTimestamp(double timestamp) {
                _timestamp = timestamp;
            };
            Direction getDirection() const {
                return _direction;
            };
            void setDirection(Direction direction) {
                _direction = direction;
            };
            Vector2i getPos() const {
                return _pos;
            };
            void setPos(Vector2i pos) {
                _pos = pos;
            };
        private:
            double _timestamp;
            ActionType _type;
            int _playerId;
            bool _inProgress;
            Direction _direction;
            Vector2i _pos;
    };

    class Actions {
        public:
            Actions();
            ~Actions() = default;

            void addAction(ActionType type, int playerId, float timestamp);
            void addAction(ActionType type, int playerId, Direction direction, Vector2i pos, float timestamp);
            void deleteAction(int playerId);
            void setGridSize(GUI::Vector3f size);
            bool isAction(int playerId);
            ActionData getAction(int playerId);
            AnimationType execute(std::shared_ptr<IPlayer>& player, ActionData& data, double now);
            double getDuration(ActionType type);
            void setFrequence(double frequence);
        protected:
        private:
            GUI::Vector3f _gridSize;

            std::unordered_map<ActionType, AnimationType (Actions::*)(std::shared_ptr<IPlayer>&, ActionData&, double)> _actions;
            std::unordered_map<int, std::deque<ActionData>> _playersActions;

            std::unordered_map<ActionType, double> _actionsTime;
            double _frequence;

            AnimationType c_move(std::shared_ptr<IPlayer> &player, ActionData &data, double now);
    };
};

#endif /* !ACTIONS_HPP_ */
