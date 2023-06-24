/*
** EPITECH PROJECT, 2023
** zappy_gui
** File description:
** Config.hpp
*/

#pragma once

#include <utility>
#include <string>
#include <vector>
#include "IConfig.hpp"
#include "Player.hpp"
#include "Actions.hpp"
#include "Chrono.hpp"

namespace GUI {

    class Config final : public IConfig {
        public:
            Config() = default;
            ~Config() final = default;

        bool isInitialized() const {
            return mapSize.x != 0 && mapSize.y != 0 && (int)mapContent.size() == mapSize.x * mapSize.y && _freq != -1;
        };

        GUI::Vector2i &getMapSize() final {
            return mapSize;
        }

        void setMapSize(const GUI::Vector2i &value) final {
            mapSize = value;
        }

        std::map<GUI::Vector2i, std::vector<int>> &getMapContent() final {
            return mapContent;
        }

        void setMapContent(const std::map<GUI::Vector2i, std::vector<int>> &value) final {
            mapContent = value;
        }

        std::map<int, Egg> &getEggs() final {
            return eggs;
        }

        void setEggs(const std::map<int, Egg> &value) final {
            eggs = value;
        }

        int getTimeUnit() final {
            return timeUnit;
        }

        void setTimeUnit(int value) final {
            timeUnit = value;
        }

        std::string &getServerMessage() final {
            return serverMessage;
        }

        void setServerMessage(const std::string &value) final {
            serverMessage = value;
        }

        std::string &getWinnerTeam() final {
            return winnerTeam;
        }

        void setWinnerTeam(const std::string &value) final {
            winnerTeam = value;
        }

        bool isEnd() final {
            return _isEnd;
        }

        void setIsEnd(bool value) final {
            _isEnd = value;
        }

        std::vector<std::string> getTeams() const {
            return _teams;
        }

        void addTeam(const std::string &name) {
            _teams.push_back(name);
        }

        std::map<int, std::shared_ptr<IPlayer>> &getPlayers() final {
            return players;
        }

        void addPlayer(int id, std::shared_ptr<IPlayer> player) {
            players.insert({id, player});
        }

        void deletePlayer(int id) {
            players.erase(id);
        }

        Actions &getActions() final {
            return _actions;
        }

        std::shared_ptr<IClock> &getClock() final {
            return _clock;
        }

        std::vector<int>& getDeadPlayers() final {
            return _deadPlayers;
        }

        int getFrequence() const final {
            return _freq;
        }

        void setFrequence(int freq) final {
            _freq = freq;
        }

        public:
            GUI::Vector2i mapSize = {0, 0}; // X, Y
            std::map<GUI::Vector2i, std::vector<int>> mapContent; // pos{X,Y}, content{q0, q1, q2, q3, q4, q5, q6}
            std::map<int, Egg> eggs; // eggId, Egg
            int timeUnit = 100; // time unit in ms
            std::string serverMessage; // message from the server
            std::string winnerTeam = "none"; // name of the winner team
            bool _isEnd = false; // true if the game is over
            int _freq = -1; // frequency of the server

            std::map<int, std::shared_ptr<IPlayer>> players; // playerId, player
            std::vector<std::string> _teams;
            std::vector<int> _deadPlayers;
            Actions _actions;
            std::shared_ptr<IClock> _clock = std::make_shared<Chrono>();
    };

} // GUI
