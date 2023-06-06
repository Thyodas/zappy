/*
** EPITECH PROJECT, 2023
** gui
** File description:
** IParser
*/

#ifndef IPARSER_HPP_
    #define IPARSER_HPP_

    #include <unordered_map>
    #include "Model.hpp"
    #include <string>

namespace GUI {
    struct config {
        std::unordered_map<ModelEntity, modelConfig> models;
    };

    class IParser {
        public:
            ~IParser() = default;
            virtual config parseConfig() = 0;
    };
};

#endif /* !IPARSER_HPP_ */
