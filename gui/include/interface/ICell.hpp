/*
** EPITECH PROJECT, 2023
** gui
** File description:
** ICell
*/

#ifndef ICELL_HPP_
    #define ICELL_HPP_

    #include "IGraphicalModule.hpp"
    #include <unordered_map>

namespace GUI {
    enum Object {
        OBJ_FOOD,
        OBJ_LINEMATE,
        OBJ_DERAUMERE,
        OBJ_SIBUR,
        OBJ_MENDIANE,
        OBJ_PHIRAS,
        OBJ_THYSTAME,
        OBJ_LAST_ELEMENT
    };

    class ICell {
        public:
            virtual ~ICell() = default;
            virtual GUI::Vector2i getPos() const = 0;
            virtual std::unordered_map<GUI::Object, int> getObjects() const = 0;
            virtual void addObject(GUI::Object object) = 0;
    };
};

#endif /* !ICELL_HPP_ */
