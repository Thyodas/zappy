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
    #include <map>

    #include "IMap.hpp"
    #include "ICell.hpp"
    #include "Cell.hpp"

namespace GUI {
    class Map : public IMap {
        public:
            Map(GUI::Vector2i ssize, std::map<GUI::Vector2i, std::vector<int>>);
            ~Map();
            Vector2i getSize() const;
            std::shared_ptr<GUI::ICell>& getCell(GUI::Vector2i pos);
            bool selectionMode() const;
            GUI::Vector2i getSelectionBlock() const;
            void setSelectionBlock(GUI::Vector2i selectionBlock);
            SelectionType selectionType() const;
            void setSelectionMode(bool selectionMode, SelectionType type);
            void setSelectionMode(bool selectionMode, SelectionType type, int playerId);
            int getPlayerId() const;
        protected:
        private:
            GUI::Vector2i _size;
            std::vector<std::vector<std::shared_ptr<GUI::ICell>>> _map;
            bool _selectionMode;
            GUI::Vector2i _selectionBlock;
            SelectionType _selectionType;
            int _playerId;
    };
};

#endif /* !MAP_HPP_ */
