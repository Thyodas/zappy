/*
** EPITECH PROJECT, 2023
** zappy_gui
** File description:
** Coms.cpp
*/

#include <iostream>
#include "Coms.hpp"

namespace GUI {
    int Coms::connect(const std::string &ip, int port) {
        return _network->connect(ip, port);
    }

    void Coms::disconnect() {
        _network->disconnect();
    }

    void Coms::reset_fd() {
        _network->reset_fd();
    }

    void Coms::addRequest(const std::string &request) {
        if (!_request.empty())
            _request += request;
        else
            _request = request;
        _requestToSend = true;
    }

    void Coms::send() {
        if (_requestToSend && _network->send(_request)) {
            _requestToSend = false;
            _request.clear();
        }
    }

    bool Coms::receive() {
        if (_network->receive()) {
            _answer = _network->getAnswer();
            std::cout << "[Info] Received command " + _answer << std::endl;
            return true;
        }
        return false;
    }

    int Coms::select() {
        int returnVal = _network->select();
        return returnVal;
    }

    void Coms::process() {
        if (select() == -1)
            throw std::runtime_error(">COMS: select failed");
        receive();
        handleRequest();
        send();
        reset_fd();
    }

    void Coms::init(const std::string &ip, int port) {
        connect(ip, port);
        reset_fd();
        addRequest("GRAPHIC\n");
        select();
        send();
        reset_fd();
        addRequest("tna\n");
    }

    void Coms::handleRequest() {
        if (_answer.empty() || _answer == "WELCOME\n")
            return;
        std::string tmp;
        std::stringstream ss(_answer);
        while(!std::cin.eof() && std::getline(ss, tmp, '\n')) {
            std::string cmd = _answer.substr(0, 3);
            if (commandHandler.find(cmd) == commandHandler.end()) {
                return;
            }
            std::string params = _answer.substr(4);
            _conf = commandHandler[cmd](_conf, params);
        }
    }

    const std::shared_ptr<IConfig> &Coms::getConf() const {
        return _conf;
    }
} // GUI
