/*
** EPITECH PROJECT, 2023
** B-YEP-400-STG-4-1-zappy-remi.mergen
** File description:
** ICore
*/

#ifndef ICORE_HPP_
    #define ICORE_HPP_

    #include "IGraphicalModule.hpp"
    #include "GraphicalFactory.hpp"

namespace GUI {
    class ICore {
        public:
            virtual ~ICore() = 0;

            virtual void init(GraphicalLib lib, GUI::Vector2i windowSize) = 0;
            virtual void run() = 0;
        protected:
        private:
    };
};

#endif /* !ICORE_HPP_ */
