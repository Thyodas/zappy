/*
** EPITECH PROJECT, 2023
** zappy_gui
** File description:
** network.hpp
*/

#pragma once

#include "interface/INetwork.hpp"

namespace GUI {

    class Network final : public INetwork {
        public:
            Network();

            ~Network() final;

            int connect(const std::string &ip, int port) final;

            void disconnect() final;

            void reset_fd() final;

            int select() final;

            bool send(std::string message) final;

            bool receive() final;

            std::string getAnswer() const final { return _answer; }
    private:
            int _server_fd = 0;
            fd_set _readfds = {0};
            fd_set _writefds = {0};
            std::string _answer;
            struct timeval _tv = {1,0};
    };

} // GUI
