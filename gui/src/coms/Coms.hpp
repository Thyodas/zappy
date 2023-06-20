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
//            conf->getMapSize().first = std::stoi(params[0]); TODO: fix
//            conf->getMapSize().second = std::stoi(params[1]);
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
            std::pair<int, int> pos = {std::stoi(params[0]), std::stoi(params[1])};
            std::vector<int> content = {std::stoi(params[2]), std::stoi(params[3]), std::stoi(params[4]), std::stoi(params[5]), std::stoi(params[6]), std::stoi(params[7]),
                                                std::stoi(params[8])};
            conf->getMapContent()[pos] = content;
            return conf;
        }

        /**
         * @brief Set the name of a team
         * @param conf
         * @param answer
         * @return Config conf
         */
        static std::shared_ptr<IConfig> setTeamsName(const std::shared_ptr<IConfig> &conf, const std::string &answer) {
            if (!verifyNbParam(answer, 1)) return conf;
                std::string tmp;
                std::stringstream ss(answer);
                std::vector<std::string> params;
                while (!std::cin.eof() && std::getline(ss, tmp, ' '))
                    params.push_back(tmp);
                int newId = conf->getTeamsName().end()->first + 1;
                conf->getTeamsName()[newId] = params[0];
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
                std::shared_ptr<Player> newPlayer;
                newPlayer->id = std::stoi(params[0].substr(1));
                newPlayer->pos = {std::stoi(params[1]), std::stoi(params[2])};
                newPlayer->orientation = std::stoi(params[3]);
                newPlayer->level = std::stoi(params[4]);
                newPlayer->teamName = params[5];
                conf->getPlayers()[newPlayer->id] = newPlayer;
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
                std::pair<int, int> pos = {std::stoi(params[1]), std::stoi(params[2])};
                int orientation = std::stoi(params[3]);
                for (auto &player : conf->getPlayers()) {
                    if (player.second->getId() != id) continue;
                    player.second->setPos(pos);
                    player.second->setOrientation(orientation);
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
                std::pair<int, int> pos = {std::stoi(params[1]), std::stoi(params[2])};
                std::map<int, int> inventory = {
                        {1, std::stoi(params[3])},
                        {2, std::stoi(params[4])},
                        {3, std::stoi(params[5])},
                        {4, std::stoi(params[6])},
                        {5, std::stoi(params[7])},
                        {6, std::stoi(params[8])},
                        {7, std::stoi(params[9])}
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
            if (!verifyNbParam(answer, 2)) return conf;
                std::string tmp;
                std::stringstream ss(answer);
                std::vector<std::string> params;
                while (!std::cin.eof() && std::getline(ss, tmp, ' '))
                    params.push_back(tmp);
                int id = std::stoi(params[0]);
                for (auto &player : conf->getPlayers()) {
                    if (player.second->getId() != id) continue;
                    player.second->setIsEjecting(true);
                    break;
                }
            return conf;
        }

        static std::shared_ptr<IConfig> playerBroadcast(const std::shared_ptr<IConfig> &conf, [[maybe_unused]] const std::string &answer) {
            return conf;
            //TODO: idk what to do with this case
        }

        static std::shared_ptr<IConfig> playerStartIncantation(const std::shared_ptr<IConfig> &conf, const std::string &answer) {
//                TODO: variadic number of params
// return c (!verifyNbParam(answer, 2)) continue;
                std::string tmp;
                std::stringstream ss(answer);
                std::vector<std::string> params;
                while (!std::cin.eof() && std::getline(ss, tmp, ' '))
                    params.push_back(tmp);
                std::pair<int, int> pos = {std::stoi(params[0]), std::stoi(params[1])};
                for (u_long i = 3; i < params.size(); i++) {
                    for (auto &player : conf->getPlayers()) {
                        if (!(player.second->getPos() == pos)) continue;
                        player.second->setInIncantation(true);
                        break;
                    }
                }
            return conf;
        }

        static std::shared_ptr<IConfig> playerEndIncantation(const std::shared_ptr<IConfig> &conf, const std::string &answer) {
            if (!verifyNbParam(answer, 3)) return conf;
            std::string tmp;
            std::stringstream ss(answer);
            std::vector<std::string> params;
            while (!std::cin.eof() && std::getline(ss, tmp, ' '))
                params.push_back(tmp);
            std::pair<int, int> pos = {std::stoi(params[0]), std::stoi(params[1])};
            int result = std::stoi(params[2]); // 1 if success, 0 if fail
            for (u_long i = 3; i < params.size(); i++) {
                for (auto &player : conf->getPlayers()) {
                    if (!(player.second->getPos() == pos)) continue;
                    player.second->setInIncantation(result != 1);
                    player.second->setLevel(result == 1 ? player.second->getLevel() + 1 : player.second->getLevel());
                    break;
                }
            }
            return conf;
        }

        static std::shared_ptr<IConfig> eggLayingByPlayer(const std::shared_ptr<IConfig> &conf, [[maybe_unused]] const std::string &answer) {
            if (!verifyNbParam(answer, 1)) return conf;
            std::string tmp;
            std::stringstream ss(answer);
            std::vector<std::string> params;
            while (!std::cin.eof() && std::getline(ss, tmp, ' '))
                params.push_back(tmp);
            int id = std::stoi(params[0]);
            for (auto &player : conf->getPlayers()) {
                if (player.second->getId() != id) continue;
                player.second->setIsLayingEgg(true);
                break;
            }
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
                    player.second->opOnInventoryAtIndex(resourceIndex, -1);
                    conf->getMapContent()[player.second->getPos()].at(resourceIndex) += 1;
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
                    player.second->opOnInventoryAtIndex(resourceIndex, +1);
                    conf->getMapContent()[player.second->getPos()].at(resourceIndex) -= 1;
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
                    break;
                }
            return conf;
        }

        static std::shared_ptr<IConfig> eggLaidByPlayer(const std::shared_ptr<IConfig> &conf, [[maybe_unused]] const std::string &answer) {
            if (!verifyNbParam(answer, 1)) return conf;
            std::string tmp;
            std::stringstream ss(answer);
            std::vector<std::string> params;
            while (!std::cin.eof() && std::getline(ss, tmp, ' '))
                params.push_back(tmp);
            int id = std::stoi(params[0]);
            Egg egg;
            for (auto &player :conf->getPlayers()) {
                if (player.second->getId() != id)  continue;
                egg.pos = player.second->getPos();
                egg.id = (int)conf->getEggs().size() + 1;
                player.second->setIsLayingEgg(false);
                break;
            }
            conf->getEggs()[egg.id] = egg;
            return conf;
        }

        static std::shared_ptr<IConfig> playerConnectForEgg(const std::shared_ptr<IConfig> &conf, [[maybe_unused]] const std::string &answer) {
            return conf;
        }

        static std::shared_ptr<IConfig> eggDie(const std::shared_ptr<IConfig> &conf, [[maybe_unused]] const std::string &answer) {
            if (!verifyNbParam(answer, 1)) return conf;
            std::string tmp;
            std::stringstream ss(answer);
            std::vector<std::string> params;
            while (!std::cin.eof() && std::getline(ss, tmp, ' '))
                params.push_back(tmp);
            int eggNbr = std::stoi(params[0]);
            for (auto &egg :conf->getEggs()) {
                if (egg.second.id != eggNbr)  continue;
                egg.second.isAlive = false;
                break;
            }
            return conf;
        }

        static std::shared_ptr<IConfig> setTimeUnit(const std::shared_ptr<IConfig> &conf, const std::string &answer) {
            if (!verifyNbParam(answer, 1)) return conf;
            std::string tmp;
            std::stringstream ss(answer);
            std::vector<std::string> params;
            while (!std::cin.eof() && std::getline(ss, tmp, ' '))
                params.push_back(tmp);
            conf->setTimeUnit(std::stoi(params[0]));
            return conf;
        }

        static std::shared_ptr<IConfig> changeTimeUnit(const std::shared_ptr<IConfig> &conf, const std::string &answer) {
            setTimeUnit(conf, answer);
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
            commandHandler.emplace("tna", setTeamsName);
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
            commandHandler.emplace("sst", changeTimeUnit);
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
        void addRequest(const std::string &request);
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
