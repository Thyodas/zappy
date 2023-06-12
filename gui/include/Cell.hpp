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
    #include <vector>

namespace GUI {
    class Cell : public GUI::ICell {
        public:
            Cell(GUI::Vector2i pos);
            ~Cell();
            GUI::Vector2i getPos() const;
            std::vector<Object> getObjects() const;
        protected:
        private:
            GUI::Vector2i _pos;
            std::vector<Object> _objects;
    };
};

#endif /* !CELL_HPP_ */
