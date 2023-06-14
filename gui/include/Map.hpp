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
            Map(int ssize);
            ~Map();
            int getSize() const;
            std::shared_ptr<GUI::ICell>& getCell(GUI::Vector2i pos);
            bool selectionMode() const;
            void setSelectionMode(bool selectionMode);
            GUI::Vector2i getSelectionBlock() const;
            void setSelectionBlock(GUI::Vector2i selectionBlock);
            std::vector<std::shared_ptr<GUI::ICell>> getCells();
        protected:
        private:
            int _size;
            std::vector<std::vector<std::shared_ptr<GUI::ICell>>> _map;
            bool _selectionMode;
            GUI::Vector2i _selectionBlock;
            std::unordered_map<GUI::Object, float> _objectsDensity;
    };
};

#endif /* !MAP_HPP_ */
