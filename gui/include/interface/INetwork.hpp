/*
** EPITECH PROJECT, 2023
** zappy_gui
** File description:
** INetwork.hpp
*/

#pragma once

#include <string>

namespace GUI {
    class INetwork {
        public:
            virtual ~INetwork() = default;

            virtual int connect(const std::string &ip, int port) = 0;
            virtual void disconnect() = 0;
            virtual void reset_fd() = 0;
            virtual int select() = 0;
            virtual bool send(std::string message) = 0;
            virtual bool receive() = 0;
            virtual std::string getAnswer() const = 0;
        protected:
        private:
    };
}
