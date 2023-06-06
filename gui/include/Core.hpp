/*
** EPITECH PROJECT, 2023
** B-YEP-400-STG-4-1-zappy-remi.mergen
** File description:
** Core
*/

#ifndef CORE_HPP_
    #define CORE_HPP_

    #include <memory>

    #include "IParser.hpp"
    #include "ICore.hpp"
    #include "GraphicalFactory.hpp"
    #include "Scene.hpp"

namespace GUI {
    class Core : public GUI::ICore {
        public:
            Core();
            ~Core();
            void init(GUI::GraphicalLib lib, GUI::Vector2i windowSize);
            void run();
        private:
            bool _running;
            GUI::Vector2i _windowSize;
            GUI::config _config;
            std::shared_ptr<IGraphicalModule> _module;
            std::shared_ptr<Scene> _scene;
    };
};

#endif /* !CORE_HPP_ */
