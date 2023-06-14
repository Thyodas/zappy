/*
** EPITECH PROJECT, 2023
** gui
** File description:
** IMap
*/

#ifndef IMAP_HPP_
    #define IMAP_HPP_

    #include <memory>

    #include "IGraphicalModule.hpp"
    #include "ICell.hpp"

namespace GUI {
    class IMap {
        public:
            virtual ~IMap() = default;
            virtual int getSize() const = 0;
            virtual std::shared_ptr<GUI::ICell>& getCell(GUI::Vector2i pos) = 0;
            virtual bool selectionMode() const = 0;
            virtual void setSelectionMode(bool selectionMode) = 0;
            virtual GUI::Vector2i getSelectionBlock() const = 0;
            virtual void setSelectionBlock(GUI::Vector2i block) = 0;
    };
};

#endif /* !IMAP_HPP_ */
