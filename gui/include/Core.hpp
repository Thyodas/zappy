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
    #include "IMap.hpp"
    #include "Coms.hpp"
    #include "ArgsParser.hpp"
    #include "Team.hpp"

namespace GUI {
    class Core : public GUI::ICore {
        public:
            Core(GUI::Args args);
            ~Core();
            void init(GUI::GraphicalLib lib, GUI::Vector2i windowSize);
            void run();
        private:
            void handleUserInput();
            void handleZoom();
            void handleSelection();
            void draw();
            void drawGround();
            void drawCellDetails(std::shared_ptr<ICell> cell);
            void drawEntities(std::shared_ptr<ICell> cell);
            void handleEndGame();
            bool _running;
            GUI::Vector2i _windowSize;
            GUI::config _config;
            std::shared_ptr<IGraphicalModule> _module;
            std::shared_ptr<Scene> _scene;
            std::shared_ptr<IMap> _map;
            std::unordered_map<GUI::Object, std::string> _objectsMap;
            std::unordered_map<GUI::Object, GUI::ModelEntity> _objToModels;
            std::vector<GUI::ModelEntity> _models;
            bool _drawObjects;
            Coms _coms;
    };
};  // namespace GUI

#endif /* !CORE_HPP_ */
