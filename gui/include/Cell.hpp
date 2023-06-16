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
    #include <unordered_map>

namespace GUI {
    class Cell : public GUI::ICell {
        public:
            Cell(GUI::Vector2i pos);
            ~Cell();
            GUI::Vector2i getPos() const;
            std::unordered_map<Object, int> getObjects() const;
            void addObject(GUI::Object object);
        protected:
        private:
            GUI::Vector2i _pos;
            std::unordered_map<Object, int> _objects;
    };
};

#endif /* !CELL_HPP_ */
