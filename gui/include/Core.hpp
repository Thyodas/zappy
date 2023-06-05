/*
** EPITECH PROJECT, 2023
** B-YEP-400-STG-4-1-zappy-remi.mergen
** File description:
** Core
*/

#ifndef CORE_HPP_
    #define CORE_HPP_

    #include "./interface/ICore.hpp"

namespace GUI {
    class Core : public GUI::ICore {
        public:
            Core();
            ~Core();
            void init(GUI::GraphicalLib lib, GUI::Vector2f windowSize);
            void run();
        private:
            bool _running;
    };
};

#endif /* !CORE_HPP_ */
