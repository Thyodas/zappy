/*
** EPITECH PROJECT, 2023
** zappy_gui
** File description:
** Coms.hpp
*/

#pragma once

#include <memory>
#include <iostream>
#include <memory>
#include <functional>
#include <algorithm>
#include <map>
#include <sstream>
#include "Network.hpp"
#include "Config.hpp"

namespace GUI {

    using cmdHandlerFunct = std::function<std::shared_ptr<IConfig>
                    (const std::shared_ptr<IConfig> &, const std::string &)>;

    class Coms {
    public:
        /**
         * @brief Set the size of the map
         * @param conf
         * @param answer
         * @return Config conf
         */
        static std::shared_ptr<IConfig> setMapSize(const std::shared_ptr<IConfig> &conf, const std::string &answer) {
            if (!verifyNbParam(answer, 2)) return conf;
            std::string tmp;
            std::stringstream ss(answer);
            std::vector<std::string> params;
            while (!std::cin.eof() && std::getline(ss, tmp, ' '))
                params.push_back(tmp);
           conf->getMapSize().x = std::stoi(params[0]);
           conf->getMapSize().y = std::stoi(params[1]);
            return conf;
        }

        /**
         * @brief Set the content of a tile
         * @param conf
         * @param answer
         * @return Config conf
         */
        static std::shared_ptr<IConfig> setMapTile(const std::shared_ptr<IConfig> &conf, const std::string &answer) {
            if (!verifyNbParam(answer, 9)) return conf;
            std::string tmp;
            std::stringstream ss(answer);
            std::vector<std::string> params;
            while (!std::cin.eof() && std::getline(ss, tmp, ' '))
                params.push_back(tmp);
            GUI::Vector2i pos = {std::stoi(params[0]), std::stoi(params[1])};
            std::vector<int> content = {std::stoi(params[2]), std::stoi(params[3]), std::stoi(params[4]), std::stoi(params[5]), std::stoi(params[6]), std::stoi(params[7]),
                                                std::stoi(params[8])};
            conf->getMapContent().emplace(std::make_pair(pos, content));
            return conf;
        }

        /**
         * @brief Set the name of a team
         * @param conf
         * @param answer
         * @return Config conf
         */
        static std::shared_ptr<IConfig> tnaCommand(const std::shared_ptr<IConfig> &conf, const std::string &answer) {
            if (!verifyNbParam(answer, 1)) return conf;
                std::string tmp;
                std::stringstream ss(answer);
                std::vector<std::string> params;
                while (!std::cin.eof() && std::getline(ss, tmp, ' '))
                    params.push_back(tmp);

                params[0].erase(params[0].size() - 1);
                auto teams = conf->getTeams();
                if (std::find(teams.begin(), teams.end(), params[0]) == teams.end()) {
                    conf->addTeam(params[0]);
                }
            return conf;
        }

        /**
         * @brief Add a new player
         * @param conf
         * @param answer
         * @return Config conf
         */
        static std::shared_ptr<IConfig> addPlayer(const std::shared_ptr<IConfig> &conf, const std::string &answer) {
            if (!verifyNbParam(answer, 6)) return conf;
                std::string tmp;
                std::stringstream ss(answer);
                std::vector<std::string> params;
                while (!std::cin.eof() && std::getline(ss, tmp, ' '))
                    params.push_back(tmp);
                std::shared_ptr<Player> newPlayer = std::make_shared<Player>();

                newPlayer->id = std::stoi(params[0]);
                newPlayer->pos = {std::stoi(params[1]), std::stoi(params[2])};
                newPlayer->orientation = static_cast<GUI::Direction>(std::stoi(params[3]));
                newPlayer->level = std::stoi(params[4]);
                newPlayer->teamName = params[5].erase(params[5].size() - 1, 1);

                auto teams = conf->getTeams();
                if (std::find(teams.begin(), teams.end(), params[0]) == teams.end()) {
                    conf->addTeam(params[0]);
                }

                conf->addPlayer(newPlayer->id, newPlayer);
            return conf;
        }

        static std::shared_ptr<IConfig> setPlayerPos(const std::shared_ptr<IConfig> &conf, const std::string &answer) {
            if (!verifyNbParam(answer, 4)) return conf;
                std::string tmp;
                std::stringstream ss(answer);
                std::vector<std::string> params;
                while (!std::cin.eof() && std::getline(ss, tmp, ' '))
                    params.push_back(tmp);
                int id = std::stoi(params[0]);
                GUI::Vector2i pos = {std::stoi(params[1]), std::stoi(params[2])};
                int orientation = std::stoi(params[3]);
                for (auto &player : conf->getPlayers()) {
                    if (player.second->getId() != id) continue;
                    conf->getActions().addAction(ActionType::MOVE, player.second->getId(), static_cast<Direction>(orientation), pos, conf->getClock()->getElapsedTime());
                    break;
                }
            return conf;
        }

        static std::shared_ptr<IConfig> setPlayerLvl(const std::shared_ptr<IConfig> &conf, const std::string &answer) {
            if (!verifyNbParam(answer, 2)) return conf;
                std::string tmp;
                std::stringstream ss(answer);
                std::vector<std::string> params;
                while (!std::cin.eof() && std::getline(ss, tmp, ' '))
                    params.push_back(tmp);
                int id = std::stoi(params[0]);
                int level = std::stoi(params[1]);
                for (auto &player : conf->getPlayers()) {
                    if (player.second->getId() != id) continue;
                    player.second->setLevel(level);
                    break;
                }
            return conf;
        }

        static std::shared_ptr<IConfig> setPlayerInventory(const std::shared_ptr<IConfig> &conf, const std::string &answer) {
            if (!verifyNbParam(answer, 10)) return conf;
                std::string tmp;
                std::stringstream ss(answer);
                std::vector<std::string> params;
                while (!std::cin.eof() && std::getline(ss, tmp, ' '))
                    params.push_back(tmp);
                int id = std::stoi(params[0]);
                GUI::Vector2i pos = {std::stoi(params[1]), std::stoi(params[2])};
                std::unordered_map<GUI::Object, int> inventory = {
                        {OBJ_FOOD, std::stoi(params[3])},
                        {OBJ_LINEMATE, std::stoi(params[4])},
                        {OBJ_DERAUMERE, std::stoi(params[5])},
                        {OBJ_SIBUR, std::stoi(params[6])},
                        {OBJ_MENDIANE, std::stoi(params[7])},
                        {OBJ_PHIRAS, std::stoi(params[8])},
                        {OBJ_THYSTAME, std::stoi(params[9])}
                };
                for (auto &player : conf->getPlayers()) {
                    if (player.second->getId() != id) continue;
                    player.second->setPos(pos);
                    player.second->setInventory(inventory);
                    break;
                }
            return conf;
        }

        static std::shared_ptr<IConfig> playerExpulsion(const std::shared_ptr<IConfig> &conf, const std::string &answer) {
            if (!verifyNbParam(answer, 1)) return conf;
                std::string tmp;
                std::stringstream ss(answer);
                std::vector<std::string> params;
                while (!std::cin.eof() && std::getline(ss, tmp, ' '))
                    params.push_back(tmp);
                int id = std::stoi(params[0]);
                std::vector<int> playersOnTile;
                if (conf->getPlayers().find(id) != conf->getPlayers().end()) {
                    std::shared_ptr<IPlayer> player = conf->getPlayers().at(id);
                    conf->getActions().addAction(ActionType::MOVE, player->getId(), static_cast<Direction>(player->getOrientation()), player->getPos(), conf->getClock()->getElapsedTime());
                }
            return conf;
        }

        static std::shared_ptr<IConfig> playerBroadcast(const std::shared_ptr<IConfig> &conf, const std::string &answer) {
            if (!verifyNbParam(answer, 2)) return conf;
                std::string tmp;
                std::stringstream ss(answer);
                std::vector<std::string> params;
                while (!std::cin.eof() && std::getline(ss, tmp, ' '))
                    params.push_back(tmp);
                int id = std::stoi(params[0]);
                for (auto &player : conf->getPlayers()) {
                    if (player.second->getId() != id) continue;
                    conf->getActions().addAction(ActionType::BROADCAST, player.second->getId(), conf->getClock()->getElapsedTime());
                    break;
                }
            return conf;
        }

        static std::shared_ptr<IConfig> playerStartIncantation(const std::shared_ptr<IConfig> &conf, const std::string &answer) {
                std::string tmp;
                std::stringstream ss(answer);
                std::vector<std::string> params;
                while (!std::cin.eof() && std::getline(ss, tmp, ' '))
                    params.push_back(tmp);
                GUI::Vector2i pos = {std::stoi(params[0]), std::stoi(params[1])};
                int firstPlayer = std::stoi(params[3]);
                conf->getActions().addAction(ActionType::INCANTATION_BEGIN, firstPlayer, conf->getClock()->getElapsedTime());
            return conf;
        }

        static std::shared_ptr<IConfig> playerEndIncantation(const std::shared_ptr<IConfig> &conf, const std::string &answer) {
            if (!verifyNbParam(answer, 3)) return conf;
            return conf;
        }

        static std::shared_ptr<IConfig> eggLayingByPlayer(const std::shared_ptr<IConfig> &conf, [[maybe_unused]] const std::string &answer) {
            return conf;
        }

        static std::shared_ptr<IConfig> playerDropResource(const std::shared_ptr<IConfig> &conf, const std::string &answer) {
            if (!verifyNbParam(answer, 2)) return conf;
                std::string tmp;
                std::stringstream ss(answer);
                std::vector<std::string> params;
                while (!std::cin.eof() && std::getline(ss, tmp, ' '))
                    params.push_back(tmp);
                int id = std::stoi(params[0]);
                const int resourceIndex = std::stoi(params[1]);
                for (auto &player : conf->getPlayers()) {
                    if (player.second->getId() != id) continue;
                    Object obj = static_cast<Object>(resourceIndex);
                    conf->getActions().addAction(ActionData(ActionType::SET_OBJECT, player.second->getId(), player.second->getPos(), conf->getClock()->getElapsedTime(), obj));
                    break;
                }
            return conf;
        }

        static std::shared_ptr<IConfig> playerCollectResource(const std::shared_ptr<IConfig> &conf, const std::string &answer) {
            if (!verifyNbParam(answer, 2)) return conf;
                std::string tmp;
                std::stringstream ss(answer);
                std::vector<std::string> params;
                while (!std::cin.eof() && std::getline(ss, tmp, ' '))
                    params.push_back(tmp);
                int id = std::stoi(params[0]);
                const int resourceIndex = std::stoi(params[1]);
                for (auto &player : conf->getPlayers()) {
                    if (player.second->getId() != id) continue;
                    Object obj = static_cast<Object>(resourceIndex);
                    conf->getActions().addAction(ActionData(ActionType::TAKE_OBJECT, player.second->getId(), player.second->getPos(), conf->getClock()->getElapsedTime(), obj));
                    break;
                }
            return conf;
        }

        static std::shared_ptr<IConfig> playerDie(const std::shared_ptr<IConfig> &conf, const std::string &answer) {
            if (!verifyNbParam(answer, 1)) return conf;
                std::string tmp;
                std::stringstream ss(answer);
                std::vector<std::string> params;
                while (!std::cin.eof() && std::getline(ss, tmp, ' '))
                    params.push_back(tmp);
                int id = std::stoi(params[0]);
                for (auto &player :conf->getPlayers()) {
                    if (player.second->getId() != id) continue;
                    player.second->setIsAlive(false);
                    conf->getDeadPlayers().push_back(player.first);
                    conf->getActions().addAction(ActionData(ActionType::DIE, player.second->getId(), conf->getClock()->getElapsedTime()));
                    break;
                }
            return conf;
        }

        static std::shared_ptr<IConfig> eggLaidByPlayer(const std::shared_ptr<IConfig> &conf, [[maybe_unused]] const std::string &answer) {
            if (!verifyNbParam(answer, 4)) return conf;
            std::string tmp;
            std::stringstream ss(answer);
            std::vector<std::string> params;
            while (!std::cin.eof() && std::getline(ss, tmp, ' '))
                params.push_back(tmp);
            int id = std::stoi(params[0]);
            Vector2i pos = {std::stoi(params[2]), std::stoi(params[3])};
            Egg egg;
                egg.pos = pos;
                egg.id = id;
            conf->getEggs().insert({egg.id, egg});
            return conf;
        }

        static std::shared_ptr<IConfig> playerConnectForEgg(const std::shared_ptr<IConfig> &conf, [[maybe_unused]] const std::string &answer) {
            if (!verifyNbParam(answer, 1)) return conf;
            std::string tmp;
            std::stringstream ss(answer);
            std::vector<std::string> params;
            while (!std::cin.eof() && std::getline(ss, tmp, ' '))
                params.push_back(tmp);
            int id = std::stoi(params[0]);
            conf->getEggs().erase(id);
            return conf;
        }

        static std::shared_ptr<IConfig> eggDie(const std::shared_ptr<IConfig> &conf, [[maybe_unused]] const std::string &answer) {
            if (!verifyNbParam(answer, 1)) return conf;
            std::string tmp;
            std::stringstream ss(answer);
            std::vector<std::string> params;
            while (!std::cin.eof() && std::getline(ss, tmp, ' '))
                params.push_back(tmp);
            int id = std::stoi(params[0]);
            conf->getEggs().erase(id);
            return conf;
        }

        static std::shared_ptr<IConfig> setTimeUnit(const std::shared_ptr<IConfig> &conf, const std::string &answer) {
            if (!verifyNbParam(answer, 1)) return conf;
            std::string tmp;
            std::stringstream ss(answer);
            std::vector<std::string> params;
            while (!std::cin.eof() && std::getline(ss, tmp, ' '))
                params.push_back(tmp);
            conf->getActions().setFrequence(std::stoi(params[0]));
            conf->setFrequence(std::stoi(params[0]));
            return conf;
        }

        static std::shared_ptr<IConfig> endOfGame(const std::shared_ptr<IConfig> &conf, const std::string &answer) {
            if (!verifyNbParam(answer, 1)) return conf;
            std::string tmp;
            std::stringstream ss(answer);
            std::vector<std::string> params;
            while (!std::cin.eof() && std::getline(ss, tmp, ' '))
                params.push_back(tmp);
            for (auto &player:conf->getPlayers())
                player.second->setIsAlive(false);
            conf->setIsEnd(true);
            conf->setWinnerTeam(params[0]);
            return conf;
        }

        static std::shared_ptr<IConfig> serverMessage(const std::shared_ptr<IConfig> &conf, const std::string &answer) {
            if (!verifyNbParam(answer, 2)) return conf;
            conf->setServerMessage(answer);
            return conf;
        }

        static std::shared_ptr<IConfig> unknownCmd(const std::shared_ptr<IConfig> &conf, [[maybe_unused]] const std::string &answer) {
            return conf;
        }

        static std::shared_ptr<IConfig> cmdParameter(const std::shared_ptr<IConfig> &conf, [[maybe_unused]] const std::string &answer) {
            return conf;
        }

        Coms() = delete;
        Coms(const std::string &ip, int port) {
            init(ip, port);

            commandHandler.emplace("msz", setMapSize);
            commandHandler.emplace("bct", setMapTile);
            commandHandler.emplace("tna", tnaCommand);
            commandHandler.emplace("pnw", addPlayer);
            commandHandler.emplace("ppo", setPlayerPos);
            commandHandler.emplace("plv", setPlayerLvl);
            commandHandler.emplace("pin", setPlayerInventory);
            commandHandler.emplace("pex", playerExpulsion);
            commandHandler.emplace("pbc", playerBroadcast);
            commandHandler.emplace("pic", playerStartIncantation);
            commandHandler.emplace("pie", playerEndIncantation);
            commandHandler.emplace("pfk", eggLayingByPlayer);
            commandHandler.emplace("pdr", playerDropResource);
            commandHandler.emplace("pgt", playerCollectResource);
            commandHandler.emplace("pdi", playerDie);
            commandHandler.emplace("enw", eggLaidByPlayer);
            commandHandler.emplace("ebo", playerConnectForEgg);
            commandHandler.emplace("edi", eggDie);
            commandHandler.emplace("sgt", setTimeUnit);
            commandHandler.emplace("sst", setTimeUnit);
            commandHandler.emplace("seg", endOfGame);
            commandHandler.emplace("smg", serverMessage);
            commandHandler.emplace("suc", unknownCmd);
            commandHandler.emplace("spb", cmdParameter);
        }

        ~Coms() { disconnect(); }

        void init(const std::string &ip, int port);

        void process();

        const std::shared_ptr<IConfig> &getConf() const;

        std::string _answer;
        void addRequest(const std::string &request);
    private:
        std::unique_ptr<INetwork> _network = std::make_unique<Network>();
        bool _requestToSend = false;
        std::string _request;
        std::shared_ptr<IConfig> _conf = std::make_shared<Config>();
        std::map<std::string, cmdHandlerFunct> commandHandler;

        int connect(const std::string &ip, int port);
        void disconnect();
        void reset_fd();
        int select();
        void send();
        bool receive();
        void handleRequest();


        static bool verifyNbParam(const std::string &answer, int nbParam) {
            int nb = 0;
            for (auto &i : answer) {
                if (i == ' ')
                    nb++;
            }
            if (nb != nbParam - 1) {
                std::cerr << "Error: bad number of parameters" << std::endl;
                return false;
            } else
                return true;
        }
    };
} // GUI
