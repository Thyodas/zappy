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

namespace GUI {

    class Config final : public IConfig {
        public:
            Config() = default;
            ~Config() final = default;

            bool isInitialized() const {
                return mapSize.first != 0 && mapSize.second != 0;
            };

        const std::pair<int, int> &getMapSize() const final {
            return mapSize;
        }

        void setMapSize(const std::pair<int, int> &value) final {
            Config::mapSize = value;
        }

        const std::map<std::pair<int, int>, std::vector<int>> &getMapContent() const final {
            return mapContent;
        }

        void setMapContent(const std::map<std::pair<int, int>, std::vector<int>> &value) final {
            Config::mapContent = value;
        }

        const std::map<int, std::string> &getTeamsName() const final {
            return teamsName;
        }

        void setTeamsName(const std::map<int, std::string> &value) final {
            Config::teamsName = value;
        }

        const std::map<int, std::shared_ptr<IPlayer>> &getPlayers() const final {
            return players;
        }

        void setPlayers(const std::map<int, std::shared_ptr<IPlayer>> &value) final {
            Config::players = value;
        }

        const std::map<int, Egg> &getEggs() const final {
            return eggs;
        }

        void setEggs(const std::map<int, Egg> &value) final {
            Config::eggs = value;
        }

        int getTimeUnit() const final {
            return timeUnit;
        }

        void setTimeUnit(int value) final {
            Config::timeUnit = value;
        }

        bool isEndGame() const final {
            return endGame;
        }

        void setEndGame(bool value) final {
            Config::endGame = value;
        }

        const std::string &getServerMessage() const final {
            return serverMessage;
        }

        void setServerMessage(const std::string &value) final {
            Config::serverMessage = value;
        }

        const std::string &getWinnerTeam() const final {
            return winnerTeam;
        }

        void setWinnerTeam(const std::string &value) final {
            Config::winnerTeam = value;
        }

        bool isEnd1() const final {
            return isEnd;
        }

        void setIsEnd(bool value) final {
            Config::isEnd = value;
        }

        public:
            std::pair<int, int> mapSize = {0, 0}; // X, Y
            std::map<std::pair<int, int>, std::vector<int>> mapContent; // pos{X,Y}, content{q0, q1, q2, q3, q4, q5, q6}
            std::map<int, std::string> teamsName; // teamId, teamName
            std::map<int, std::shared_ptr<IPlayer>> players; // playerId, player
            std::map<int, Egg> eggs; // eggId, Egg
            int timeUnit = 100; // time unit in ms
            bool endGame = true; // true if the game is over
            std::string serverMessage; // message from the server
            std::string winnerTeam; // name of the winner team
            bool isEnd = false; // true if the game is over
    };

} // GUI
