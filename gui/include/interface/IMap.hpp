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
            virtual GUI::Vector2i getSize() const = 0;
            virtual std::shared_ptr<GUI::ICell>& getCell(GUI::Vector2i pos) = 0;
    };
};

#endif /* !IMAP_HPP_ */
