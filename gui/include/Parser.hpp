/*
** EPITECH PROJECT, 2023
** gui
** File description:
** Parser
*/

#ifndef PARSER_HPP_
    #define PARSER_HPP_

    #include "libconfig.h++"
    #include "IParser.hpp"
    #include "Model.hpp"
    #include <iostream>

namespace GUI {
    class Parser : public GUI::IParser {
        public:
            Parser(const std::string& path);
            ~Parser();
            config parseConfig();
        protected:
        private:
            libconfig::Config _config;
    };
};

#endif /* !PARSER_HPP_ */
