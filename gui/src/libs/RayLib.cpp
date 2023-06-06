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
    _keys[GUI::Key::LEFT]           = KeyboardKey::KEY_LEFT;
    _keys[GUI::Key::RIGHT]          = KeyboardKey::KEY_RIGHT;
    _keys[GUI::Key::UP]             = KeyboardKey::KEY_UP;
    _keys[GUI::Key::DOWN]           = KeyboardKey::KEY_DOWN;
    _keys[GUI::Key::Z]              = KeyboardKey::KEY_Z;
    _keys[GUI::Key::Q]              = KeyboardKey::KEY_Q;
    _keys[GUI::Key::S]              = KeyboardKey::KEY_S;
    _keys[GUI::Key::D]              = KeyboardKey::KEY_D;

    for (auto &key : _keys)
        _pressedKeys[key.first] = false;
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
    for (auto& model : _models) {
        UnloadModel(model.second.model);
        UnloadTexture(model.second.texture);
    }
    CloseWindow();
}

void GUI::RayLib::display()
{
}

void GUI::RayLib::handleEvents()
{
    for (auto &key : _keys) {
        if (IsKeyDown(key.second))
            _pressedKeys[key.first] = true;
    }
}

bool GUI::RayLib::isKeyPressed(GUI::Key key)
{
    for (auto &pressedKey : _pressedKeys) {
        if (pressedKey.first == key && pressedKey.second == true) {
            pressedKey.second = false;
            return true;
        }
    }
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

void GUI::RayLib::drawModel(ModelEntity model, Vector3f position, float scale, Vector3f rotation)
{
    DrawModelEx(_models[model].model, {position.x, position.y, position.z}, {0, 1, 0}, rotation.x, {scale, scale, scale}, WHITE);
}

void GUI::RayLib::preDraw(std::shared_ptr<ICamera> camera)
{
    BeginDrawing();
    // Todo: add clear(color) function
    ClearBackground(RAYWHITE);
    BeginMode3D(std::dynamic_pointer_cast<RayLibCamera>(camera)->camera);
}

void GUI::RayLib::postDraw()
{
    EndMode3D();
    EndDrawing();
}