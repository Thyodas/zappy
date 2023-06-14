/*
** EPITECH PROJECT, 2023
** B-YEP-400-STG-4-1-zappy-remi.mergen
** File description:
** RayLib
*/

#include "RayLib.hpp"

GUI::RayLib::RayLib()
{
    _keys[GUI::Key::LEFT]               = KeyboardKey::KEY_Q;
    _keys[GUI::Key::UP]                 = KeyboardKey::KEY_Z;
    _keys[GUI::Key::RIGHT]              = KeyboardKey::KEY_D;
    _keys[GUI::Key::DOWN]               = KeyboardKey::KEY_S;
    _keys[GUI::Key::SPACE]              = KeyboardKey::KEY_SPACE;
    _keys[GUI::Key::ESCAPE]             = KeyboardKey::KEY_ESCAPE;
    _keys[GUI::Key::R]                  = KeyboardKey::KEY_R;
    _keys[GUI::Key::F]                  = KeyboardKey::KEY_F;
    _keys[GUI::Key::LEFT]               = KeyboardKey::KEY_LEFT;
    _keys[GUI::Key::RIGHT]              = KeyboardKey::KEY_RIGHT;
    _keys[GUI::Key::UP]                 = KeyboardKey::KEY_UP;
    _keys[GUI::Key::DOWN]               = KeyboardKey::KEY_DOWN;
    _keys[GUI::Key::Z]                  = KeyboardKey::KEY_Z;
    _keys[GUI::Key::Q]                  = KeyboardKey::KEY_Q;
    _keys[GUI::Key::S]                  = KeyboardKey::KEY_S;
    _keys[GUI::Key::D]                  = KeyboardKey::KEY_D;

    _mouseButtons[GUI::Mouse::BUTTON_LEFT]     = MOUSE_LEFT_BUTTON;
    _mouseButtons[GUI::Mouse::BUTTON_RIGHT]    = MOUSE_RIGHT_BUTTON;

    _colors[GUI::C_Color::C_WHITE]      = WHITE;
    _colors[GUI::C_Color::C_BLACK]      = BLACK;
    _colors[GUI::C_Color::C_BLUE]       = BLUE;
    _colors[GUI::C_Color::C_RED]        = RED;
    _colors[GUI::C_Color::C_GREEN]      = GREEN;
    _colors[GUI::C_Color::C_YELLOW]     = YELLOW;

    for (auto &key : _keys) {
        _pressedKeys[key.first] = false;
        _releasedKeys[key.first] = false;
    }
    for (auto &pressedButton : _pressedMouseButtons)
        _pressedMouseButtons[pressedButton.first] = false;
}

GUI::RayLib::~RayLib()
{
}

void GUI::RayLib::init(GUI::Vector2i size)
{
    InitWindow(size.x, size.y, "Zappy");
    SetTargetFPS(60);
    SetConfigFlags(FLAG_MSAA_4X_HINT);
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
    Vector2 mousePos = GetMousePosition();
    _mousePosition = {mousePos.x, mousePos.y};
    for (auto &key : _keys) {
        if (IsKeyDown(key.second)) {
            _pressedKeys[key.first] = true;
            _releasedKeys[key.first] = false;
        } else if (IsKeyReleased(key.second)) {
            _releasedKeys[key.first] = true;
            _pressedKeys[key.first] = false;
        }
    }
    for (auto &mouseButton : _mouseButtons) {
        if (IsMouseButtonDown(mouseButton.second))
            _pressedMouseButtons[mouseButton.first] = true;
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

GUI::Vector2f GUI::RayLib::getMousePosition()
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
        BoundingBox bounds = GetModelBoundingBox(_models[model.first].model);
        _models[model.first].size = {
            bounds.max.x - bounds.min.x,
            bounds.max.y - bounds.min.y,
            bounds.max.z - bounds.min.z
        };
    }
}

void GUI::RayLib::drawModel(ModelEntity model, Vector3f position, float scale, Vector3f rotation)
{
    DrawModelEx(_models[model].model, {position.x, position.y, position.z}, {0, 1, 0}, rotation.x, {scale, scale, scale}, WHITE);
}

void GUI::RayLib::preDraw()
{
    BeginDrawing();
    this->clear(GUI::C_Color::C_WHITE);
}

void GUI::RayLib::postDraw()
{
    EndDrawing();
}

GUI::Vector3f GUI::RayLib::getModelSize(ModelEntity model)
{
    return _models[model].size;
}

void GUI::RayLib::clear(GUI::C_Color color)
{
    ClearBackground(_colors[color]);
}

void GUI::RayLib::drawGrid(int size, float spacing)
{
    DrawGrid(size, spacing);
}

GUI::Vector3f GUI::RayLib::mousePosFromGrid(GUI::Vector2i position, int cellSize, int numberOfCells) {
    float x = static_cast<float>(position.x) * cellSize - (cellSize * numberOfCells) / 2.0f;
    float z = static_cast<float>(position.y) * cellSize - (cellSize * numberOfCells) / 2.0f;
    float y = 0;

    return GUI::Vector3f(x, y, z);
}

bool GUI::RayLib::isMouseButtonPressed(GUI::Mouse button)
{
    for (auto &pressedMouseButton : _pressedMouseButtons) {
        if (pressedMouseButton.first == button && pressedMouseButton.second == true) {
            pressedMouseButton.second = false;
            return true;
        }
    }
    return false;
}

bool GUI::RayLib::isKeyReleased(GUI::Key key)
{
    for (auto &releasedKey : _releasedKeys) {
        if (releasedKey.first == key && releasedKey.second == true) {
            releasedKey.second = false;
            return true;
        }
    }
    return false;
}

void GUI::RayLib::drawText(std::string text, GUI::Vector2f position, int fontSize, GUI::C_Color color)
{
    DrawText(text.c_str(), position.x, position.y, fontSize, _colors[color]);
}

void GUI::RayLib::drawRectangle(GUI::Vector2f position, GUI::Vector2f size, GUI::C_Color color)
{
    DrawRectangle(position.x, position.y, size.x, size.y, _colors[color]);
}

void GUI::RayLib::enable3DMode(std::shared_ptr<GUI::ICamera> camera)
{
    BeginMode3D(std::dynamic_pointer_cast<RayLibCamera>(camera)->camera);
}

void GUI::RayLib::disable3DMode()
{
    EndMode3D();
}