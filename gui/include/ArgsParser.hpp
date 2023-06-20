/*
** EPITECH PROJECT, 2023
** gui
** File description:
** ArgsParser
*/

#ifndef ARGSPARSER_HPP_
    #define ARGSPARSER_HPP_

    #include <iostream>

namespace GUI {
    struct Args {
        int port;
        std::string machine;
    };
    class ArgsParser {
        public:
            ArgsParser();
            ~ArgsParser();
            static Args parseArgs(int argc, char **argv);
        protected:
        private:
            Args _args;
    };
};

#endif /* !ARGSPARSER_HPP_ */
