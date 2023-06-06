/*
** EPITECH PROJECT, 2023
** B-YEP-400-STG-4-1-zappy-remi.mergen
** File description:
** GraphicalFactory
*/

#ifndef GRAPHICALFACTORY_HPP_
    #define GRAPHICALFACTORY_HPP_

    #include <memory>
    #include <stdexcept>

    #include "interface/IGraphicalModule.hpp"
    #include "libs/RayLib.hpp"

namespace GUI {
    enum GraphicalLib {
        RAYLIB
    };

    class GraphicalFactory {
        public:
            GraphicalFactory();
            ~GraphicalFactory();
            static std::shared_ptr<GUI::IGraphicalModule> createModule(GraphicalLib lib);
    };
};

#endif /* !GRAPHICALFACTORY_HPP_ */
