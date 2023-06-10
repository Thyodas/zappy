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
    #include "RayLibCamera.hpp"
    #include <vector>

namespace GUI {
    struct ModelData {
        Model model;
        Texture texture;
        GUI::Vector3f size;
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
            bool isKeyReleased(GUI::Key key);
            bool isMouseButtonPressed(GUI::Mouse button);
            GUI::Vector2f getMousePosition();
            void loadModels(std::unordered_map<ModelEntity, modelConfig> models);
            void drawModel(ModelEntity model, Vector3f position, float scale, Vector3f rotation);
            void preDraw(std::shared_ptr<ICamera> camera);
            void postDraw();
            GUI::Vector3f getModelSize(ModelEntity model);
            void clear(C_Color color);
            void drawGrid(int size, float spacing);
            GUI::Vector3f mousePosFromGrid(GUI::Vector2i position, int cellSize, int numberOfCells);
        private:
            std::unordered_map<ModelEntity, ModelData> _models;
            std::unordered_map<GUI::Key, KeyboardKey> _keys;
            std::unordered_map<GUI::Mouse, MouseButton> _mouseButtons;
            std::unordered_map<GUI::C_Color, Color> _colors;
            std::unordered_map<GUI::Key, bool> _pressedKeys;
            std::unordered_map<GUI::Key, bool> _releasedKeys;
            std::unordered_map<GUI::Mouse, bool> _pressedMouseButtons;
            GUI::Vector2f _mousePosition;
    };
};

#endif /* !RAYLIB_HPP_ */
