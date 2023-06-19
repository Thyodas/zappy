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
#include "Egg.hpp"

namespace GUI {

    class Config final : public IConfig {
        public:
            Config() = default;
            ~Config() final = default;

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
