/*
** EPITECH PROJECT, 2023
** gui
** File description:
** ICell
*/

#ifndef ICELL_HPP_
    #define ICELL_HPP_

    #include "IGraphicalModule.hpp"

namespace GUI {
    class ICell {
        public:
            virtual ~ICell() = default;
            virtual GUI::Vector2i getPos() const = 0;
    };
};

#endif /* !ICELL_HPP_ */
