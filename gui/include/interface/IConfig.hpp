/*
** EPITECH PROJECT, 2023
** zappy_gui
** File description:
** IConfig.hpp
*/

#pragma once

#include "IPlayer.hpp"
#include "Egg.hpp"
#include <memory>
#include "Actions.hpp"
#include "Chrono.hpp"

namespace GUI {
    class IConfig {
    public:
        virtual ~IConfig() = default;
        virtual GUI::Vector2i &getMapSize() = 0;
        virtual void setMapSize(const GUI::Vector2i &value) = 0;
        virtual std::map<GUI::Vector2i, std::vector<int>> &getMapContent() = 0;
        virtual void setMapContent(const std::map<GUI::Vector2i, std::vector<int>> &value) = 0;
        virtual std::map<int, Egg> &getEggs() = 0;
        virtual void setEggs(const std::map<int, Egg> &value) = 0;
        virtual int getTimeUnit() = 0;
        virtual void setTimeUnit(int value) = 0;
        virtual std::string &getServerMessage() = 0;
        virtual void setServerMessage(const std::string &value) = 0;
        virtual std::string &getWinnerTeam() = 0;
        virtual void setWinnerTeam(const std::string &value) = 0;
        virtual bool isEnd() = 0;
        virtual void setIsEnd(bool value) = 0;
        virtual bool isInitialized() const = 0;
        virtual std::vector<std::string> getTeams() const = 0;
        virtual void addTeam(const std::string &name) = 0;
        virtual void addPlayer(int id, std::shared_ptr<IPlayer> player) = 0;
        virtual std::map<int, std::shared_ptr<IPlayer>>& getPlayers() = 0;
        virtual Actions &getActions() = 0;
        virtual std::shared_ptr<IClock> &getClock() = 0;
        virtual std::vector<int>& getDeadPlayers() = 0;
        virtual void deletePlayer(int id) = 0;
    };

} // GUI
