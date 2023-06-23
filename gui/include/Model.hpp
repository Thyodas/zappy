/*
** EPITECH PROJECT, 2023
** gui
** File description:
** Model
*/

#ifndef MODEL_HPP_
    #define MODEL_HPP_

    #include <vector>
    #include <utility>
    #include "Vector3f.hpp"

namespace GUI {
    /*
    ** @brief Enum of all the models
    */
    enum ModelEntity {
        GOLEM,
        GRASS_BLOCK,
        FOOD,
        LINEMATE,
        DERAUMERE,
        SIBUR,
        MENDIANE,
        PHIRAS,
        THYSTAME
    };

    /*
    ** @brief Structure to contain model relative data parsed by an IParser
    */
    struct modelConfig {
        std::string modelPath;
        std::string texturePath;
        float scale;
        Vector3f rotation;
    };
};

#endif /* !MODEL_HPP_ */
