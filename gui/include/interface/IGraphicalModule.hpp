/*
** EPITECH PROJECT, 2023
** B-YEP-400-STG-4-1-zappy-remi.mergen
** File description:
** IGraphicalModule
*/

#ifndef IGRAPHICALMODULE_HPP_
    #define IGRAPHICALMODULE_HPP_

    #include <unordered_map>
    #include <memory>
    #include <string>
    #include "Vector3f.hpp"
    #include "ICamera.hpp"
    #include "Vector2i.hpp"
    #include "Model.hpp"

namespace GUI {
    enum Key {
        UP,
        DOWN,
        LEFT,
        RIGHT,
        SPACE,
        ESCAPE,
        R,
        F,
        Z,
        Q,
        S,
        D
    };

    enum Mouse {
        BUTTON_LEFT,
        BUTTON_RIGHT
    };

    enum C_Color {
        C_RED,
        C_GREEN,
        C_BLUE,
        C_BLACK,
        C_YELLOW,
        C_WHITE
    };

    struct Vector2f {
        float x;
        float y;
    };

    class IGraphicalModule {
        public:
            virtual ~IGraphicalModule() = default;
            virtual void loadModels(std::unordered_map<ModelEntity, modelConfig> models) = 0;
            virtual void drawModel(ModelEntity model, Vector3f position, float scale, Vector3f rotation) = 0;
            virtual void clear(C_Color color) = 0;
            virtual void init(GUI::Vector2i size) = 0;
            virtual void close() = 0;
            virtual void display() = 0;
            virtual void handleEvents() = 0;
            virtual bool isKeyPressed(GUI::Key key) = 0;
            virtual bool isKeyReleased(GUI::Key key) = 0;
            virtual GUI::Vector2f getMousePosition() = 0;
            virtual void preDraw(std::shared_ptr<ICamera> camera) = 0;
            virtual void postDraw() = 0;
            virtual GUI::Vector3f getModelSize(ModelEntity model) = 0;
            virtual void drawGrid(int size, float spacing) = 0;
            virtual bool isMouseButtonPressed(GUI::Mouse button) = 0;
            virtual GUI::Vector3f mousePosFromGrid(GUI::Vector2i position, int cellSize, int numberOfCells) = 0;
    };
};

#endif /* !IGRAPHICALMODULE_HPP_ */
