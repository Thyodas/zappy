/*
** EPITECH PROJECT, 2023
** gui
** File description:
** ITeam
*/

#ifndef ITEAM_HPP_
    #define ITEAM_HPP_

    #include <memory>
    #include <unordered_map>

    #include "IPlayer.hpp"

namespace GUI {
    class ITeam {
        public:
            virtual ~ITeam() = default;
            virtual std::unordered_map<int, std::shared_ptr<IPlayer>>& getPlayers() = 0;
            virtual IPlayer& getPlayerById(int id) = 0;
            virtual void addPlayer(int id, std::shared_ptr<IPlayer> player) = 0;
    };
};

#endif /* !ITEAM_HPP_ */
