/*
** EPITECH PROJECT, 2023
** zappy_gui
** File description:
** network.cpp
*/

#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <iostream>
#include "Network.hpp"
#include "../utils/CFunctionWrapper.hpp"

namespace GUI {
    Network::Network() {
        FD_ZERO(&_readfds);
        FD_ZERO(&_writefds);
    }

    Network::~Network() {
        disconnect();
    }

    int Network::connect(const std::string &ip, int port) {
        struct sockaddr_in serv_addr = {
                .sin_family = AF_INET,
                .sin_port = htons(port),
                .sin_addr = {0},
                .sin_zero = {0}
        };
        if ((_server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
            std::cerr << ">NTWK: Socket creation error" << std::endl;
            return -1;
        }
        if (inet_pton(AF_INET, ip.c_str(), &serv_addr.sin_addr) <= 0) {
            std::cerr << ">NTWK: Invalid address / Address not supported" << std::endl;
            return -1;
        }
        if (c_connect(_server_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
            std::cerr << ">NTWK: Connection Failed" << std::endl;
            return -1;
        }
        std::cerr << ">NTWK: Connected" << std::endl;
        return 0;
    }

    void Network::disconnect() {
        close(_server_fd);
    }
    void Network::reset_fd() {
        FD_ZERO(&_readfds);
        FD_ZERO(&_writefds);
        FD_SET(_server_fd, &_readfds);
        FD_SET(_server_fd, &_writefds);
    }

    int Network::select() {
        return c_select(FD_SETSIZE, &_readfds, &_writefds, nullptr, nullptr);
    }

    bool Network::send(std::string message) {
        if (!FD_ISSET(_server_fd, &_writefds)) return false;
        write(_server_fd, message.c_str(), message.size());
        return true;
    }

    bool Network::receive() {
        if (!FD_ISSET(_server_fd, &_readfds)) return false;
        _answer.clear();
        char buff[3] = {0};
        ssize_t len = 1;
        while (len > 0) {
            len = read(_server_fd, buff, 1);
            buff[1] = '\0';
            _answer.append(buff);
            if (buff[0] == '\n')
                break;

        }
        return true;
    }
} // GUI
