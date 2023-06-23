/*
** EPITECH PROJECT, 2023
** gui
** File description:
** Parser
*/

#ifndef PARSER_HPP_
    #define PARSER_HPP_

    #include <libconfig.h++>
    #include "IParser.hpp"
    #include "Model.hpp"
    #include <iostream>
    #include <map>
    #include <string>
    #include <utility>

namespace GUI {
    class Parser : public GUI::IParser {
        public:
            Parser(const std::string& path);
            ~Parser();
            GUI::ModelEntity getModelEntity(const std::string& name);
            config parseConfig();
        protected:
        private:
            libconfig::Config _config;
            std::map<GUI::ModelEntity, std::string> _models;
    };
};

#endif /* !PARSER_HPP_ */
