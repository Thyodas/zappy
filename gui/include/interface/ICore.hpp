/*
** EPITECH PROJECT, 2023
** B-YEP-400-STG-4-1-zappy-remi.mergen
** File description:
** ICore
*/

#pragma once

    #include "IGraphicalModule.hpp"
    #include "GraphicalFactory.hpp"

namespace GUI {
    class ICore {
        public:
            virtual ~ICore() = default;

            virtual void init(GraphicalLib lib, GUI::Vector2i windowSize) = 0;
            virtual void run() = 0;
        protected:
        private:
    };
};  // namespace GUI
