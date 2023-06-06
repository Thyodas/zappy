/*
** EPITECH PROJECT, 2023
** B-YEP-400-STG-4-1-zappy-remi.mergen
** File description:
** RayLib
*/

#include "RayLib.hpp"

GUI::RayLib::RayLib()
{
    _keys[GUI::Key::LEFT]           = KeyboardKey::KEY_Q;
    _keys[GUI::Key::UP]             = KeyboardKey::KEY_Z;
    _keys[GUI::Key::RIGHT]          = KeyboardKey::KEY_D;
    _keys[GUI::Key::DOWN]           = KeyboardKey::KEY_S;
    _keys[GUI::Key::SPACE]          = KeyboardKey::KEY_SPACE;
    _keys[GUI::Key::ESCAPE]         = KeyboardKey::KEY_ESCAPE;
    _keys[GUI::Key::R]              = KeyboardKey::KEY_R;
    _keys[GUI::Key::F]              = KeyboardKey::KEY_F;
}

GUI::RayLib::~RayLib()
{
}

void GUI::RayLib::init(GUI::Vector2i size)
{
    InitWindow(size.x, size.y, "Zappy");
    SetTargetFPS(60);
}

void GUI::RayLib::close()
{
}

void GUI::RayLib::display()
{
}

void GUI::RayLib::handleEvents()
{
}

bool GUI::RayLib::isKeyPressed(GUI::Key key)
{
    return false;
}

bool GUI::RayLib::isInteraction()
{
    return false;
}

GUI::Vector2i GUI::RayLib::getMousePosition()
{
    return _mousePosition;
}

void GUI::RayLib::loadModels(std::unordered_map<ModelEntity, modelConfig> models)
{
    _models.reserve(models.size());
    for (auto &model : models) {
        _models[model.first].model = LoadModel(model.second.modelPath.c_str());
        _models[model.first].texture = LoadTexture(model.second.texturePath.c_str());
        _models[model.first].model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = _models[model.first].texture;
    }
}

void GUI::RayLib::drawModel(ModelEntity model, Vector2f position, float scale, Vector3f rotation)
{
}

void GUI::RayLib::draw()
{
    BeginDrawing();
    ClearBackground(RAYWHITE);

    // BeginMode3D(camera);
    // EndMode3D();

    EndDrawing();
}
