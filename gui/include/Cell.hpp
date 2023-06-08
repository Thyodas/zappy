/*
** EPITECH PROJECT, 2023
** gui
** File description:
** Cell
*/

#ifndef CELL_HPP_
    #define CELL_HPP_

    #include "ICell.hpp"
    #include "IGraphicalModule.hpp"

namespace GUI {
    class Cell : public GUI::ICell {
        public:
            Cell(GUI::Vector2i pos);
            ~Cell();
            GUI::Vector2i getPos() const;
        protected:
        private:
            GUI::Vector2i _pos;
    };
};

#endif /* !CELL_HPP_ */
