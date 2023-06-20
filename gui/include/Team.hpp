/*
** EPITECH PROJECT, 2023
** gui
** File description:
** Team
*/

#ifndef TEAM_HPP_
    #define TEAM_HPP_

    #include "ITeam.hpp"

namespace GUI {
    class Team : public ITeam {
        public:
            Team() {};
            ~Team() = default;
            std::unordered_map<int, std::shared_ptr<IPlayer>>& getPlayers() {
                return _players;
            };
            IPlayer& getPlayerById(int id) {
                return *_players[id];
            };
        protected:
        private:
            std::unordered_map<int, std::shared_ptr<IPlayer>> _players;
    };
};

#endif /* !TEAM_HPP_ */
