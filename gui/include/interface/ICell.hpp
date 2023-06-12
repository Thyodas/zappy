/*
** EPITECH PROJECT, 2023
** gui
** File description:
** ICell
*/

#ifndef ICELL_HPP_
    #define ICELL_HPP_

    #include "IGraphicalModule.hpp"
    #include <vector>

namespace GUI {
    enum Object {
        OBJ_FOOD,
        OBJ_LINEMATE,
        OBJ_DERAUMERE,
        OBJ_SIBUR,
        OBJ_MENDIANE,
        OBJ_PHIRAS,
        OBJ_THYSTAME
    };

    class ICell {
        public:
            virtual ~ICell() = default;
            virtual GUI::Vector2i getPos() const = 0;
    };
};

#endif /* !ICELL_HPP_ */
