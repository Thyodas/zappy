/*
** EPITECH PROJECT, 2023
** gui
** File description:
** Model
*/

#ifndef MODEL_HPP_
    #define MODEL_HPP_

namespace GUI {
    /*
    ** @brief Enum of all the models
    */
    enum ModelEntity {
        GOLEM
    };

    /*
    ** @brief Structure to contain model relative data parsed by an IParser
    */
    struct modelConfig {
        std::string modelPath;
        std::string texturePath;
    };
};

#endif /* !MODEL_HPP_ */
