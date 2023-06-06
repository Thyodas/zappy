/*
** EPITECH PROJECT, 2023
** B-YEP-400-STG-4-1-zappy-remi.mergen
** File description:
** IGraphicalModule
*/

#ifndef IGRAPHICALMODULE_HPP_
    #define IGRAPHICALMODULE_HPP_

    #include <unordered_map>
    #include <string>
    #include "Vector3f.hpp"
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
        F
    };

    enum C_Color {
        C_RED,
        C_GREEN,
        C_BLUE,
        C_BLACK,
        C_YELLOW,
        C_MAGENTA,
        C_CYAN,
        C_WHITE
    };

    struct Vector2f {
        float x;
        float y;
    };

    struct Vector2i {
        int x;
        int y;
    };

    class IGraphicalModule {
        public:
            virtual ~IGraphicalModule() = default;
            virtual void loadModels(std::unordered_map<ModelEntity, modelConfig> models) = 0;
            virtual void drawModel(ModelEntity model, Vector2f position, float scale, Vector3f rotation) = 0;
            // virtual void clear(C_Color color) = 0;
            virtual void init(GUI::Vector2i size) = 0;
            virtual void close() = 0;
            virtual void display() = 0;
            virtual void handleEvents() = 0;
            virtual bool isKeyPressed(GUI::Key key) = 0;
            virtual bool isInteraction() = 0;
            virtual GUI::Vector2i getMousePosition() = 0;
            virtual void draw() = 0;
    };
};

#endif /* !IGRAPHICALMODULE_HPP_ */
