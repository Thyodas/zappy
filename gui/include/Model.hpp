/*
** EPITECH PROJECT, 2023
** gui
** File description:
** Model
*/

#ifndef MODEL_HPP_
    #define MODEL_HPP_

namespace GUI {
    enum ModelEntity {
        GOLEM
    };

    struct modelConfig {
        std::string modelPath;
        std::string texturePath;
    };
};

#endif /* !MODEL_HPP_ */
