/*
** EPITECH PROJECT, 2023
** B-YEP-400-STG-4-1-zappy-remi.mergen
** File description:
** RayLib
*/

#ifndef RAYLIB_HPP_
    #define RAYLIB_HPP_

    #include <unordered_map>

    #include "raylib.h"
    #include "IGraphicalModule.hpp"

namespace GUI {
    struct ModelData {
        Model model;
        Texture texture;
    };

    class RayLib : public IGraphicalModule{
        public:
            RayLib();
            ~RayLib();
            void init(GUI::Vector2i size);
            void close();
            void display();
            void handleEvents();
            bool isKeyPressed(GUI::Key key);
            bool isInteraction();
            GUI::Vector2i getMousePosition();
            void loadModels(std::unordered_map<ModelEntity, modelConfig> models);
            void drawModel(ModelEntity model, Vector2f position, float scale, Vector3f rotation);
            void draw();
        private:
            std::unordered_map<ModelEntity, ModelData> _models;
            std::unordered_map<GUI::Key, KeyboardKey> _keys;
            GUI::Vector2i _mousePosition;
    };
};

#endif /* !RAYLIB_HPP_ */
