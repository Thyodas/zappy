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
        ModelAnimation *animation;
        Texture texture;
        GUI::Vector3f size;
        GUI::Vector3f rotation;
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
            void preDraw();
            void postDraw();
            GUI::Vector3f getModelSize(ModelEntity model);
            void clear(C_Color color);
            void drawGrid(GUI::Vector2i size, float spacing, GUI::C_Color color);
            GUI::Vector3f mousePosFromGrid(GUI::Vector2i position, int cellSize, GUI::Vector2i numberOfCells);
            void drawText(std::string text, GUI::Vector2f position, int size, C_Color color);
            void drawRectangle(GUI::Vector2f position, GUI::Vector2f size, C_Color color);
            void enable3DMode(std::shared_ptr<ICamera> camera);
            void disable3DMode();
            bool isInteraction();
            void animateModel(ModelEntity model, AnimationType type, int frame);
            int getMaxFrame(ModelEntity model, AnimationType type);
            void rotateModel(ModelEntity model, Direction direction);
            bool isModelSelected(ModelEntity model, Vector3f position, float scale, std::shared_ptr<ICamera> camera);
        private:
            std::unordered_map<ModelEntity, ModelData> _models;
            std::unordered_map<GUI::Key, KeyboardKey> _keys;
            std::unordered_map<GUI::Mouse, MouseButton> _mouseButtons;
            std::unordered_map<GUI::C_Color, Color> _colors;
            std::unordered_map<GUI::Key, bool> _pressedKeys;
            std::unordered_map<GUI::Key, bool> _releasedKeys;
            std::unordered_map<GUI::Mouse, bool> _pressedMouseButtons;
            GUI::Vector2f _mousePosition;
            RayCollision _collision;
            Ray _ray;
    };
};

#endif /* !RAYLIB_HPP_ */
