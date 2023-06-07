/*
** EPITECH PROJECT, 2023
** gui
** File description:
** Map
*/

#ifndef MAP_HPP_
    #define MAP_HPP_

    #include <memory>
    #include <vector>

    #include "IMap.hpp"
    #include "ICell.hpp"
    #include "Cell.hpp"

namespace GUI {
    class Map : public IMap {
        public:
            Map(GUI::Vector2i ssize);
            ~Map();
            GUI::Vector2i getSize() const;
            std::shared_ptr<GUI::ICell>& getCell(GUI::Vector2i pos);
        protected:
        private:
            GUI::Vector2i _size;
            std::vector<std::vector<std::shared_ptr<GUI::ICell>>> _map;
    };
};

#endif /* !MAP_HPP_ */
