/*
** EPITECH PROJECT, 2023
** B-YEP-400-STG-4-1-zappy-remi.mergen
** File description:
** Core
*/

#include "Parser.hpp"
#include "Map.hpp"
#include "Core.hpp"

GUI::Core::Core(GUI::Args args) : _running(true), _scene(std::make_shared<Scene>()), _map(nullptr), _drawObjects(true), _coms(args.machine, args.port)
{
    IParser *parser = new Parser("config.cfg");
    _config = parser->parseConfig();
    delete parser;

    _objectsMap = {
        {GUI::Object::OBJ_FOOD, "food"},
        {GUI::Object::OBJ_LINEMATE, "linemate"},
        {GUI::Object::OBJ_DERAUMERE, "deraumere"},
        {GUI::Object::OBJ_SIBUR, "sibur"},
        {GUI::Object::OBJ_MENDIANE, "mendiane"},
        {GUI::Object::OBJ_PHIRAS, "phiras"},
        {GUI::Object::OBJ_THYSTAME, "thystame"},
    };
    _objToModels = {
        {GUI::Object::OBJ_FOOD, GUI::ModelEntity::FOOD},
        {GUI::Object::OBJ_LINEMATE, GUI::ModelEntity::LINEMATE},
        {GUI::Object::OBJ_DERAUMERE, GUI::ModelEntity::DERAUMERE},
        {GUI::Object::OBJ_SIBUR, GUI::ModelEntity::SIBUR},
        {GUI::Object::OBJ_MENDIANE, GUI::ModelEntity::MENDIANE},
        {GUI::Object::OBJ_PHIRAS, GUI::ModelEntity::PHIRAS},
        {GUI::Object::OBJ_THYSTAME, GUI::ModelEntity::THYSTAME},
    };
    _models = {
        GUI::ModelEntity::FOOD,
        GUI::ModelEntity::LINEMATE,
        GUI::ModelEntity::DERAUMERE,
        GUI::ModelEntity::SIBUR,
        GUI::ModelEntity::MENDIANE,
        GUI::ModelEntity::PHIRAS,
        GUI::ModelEntity::THYSTAME,
    };
}

GUI::Core::~Core() {}

void GUI::Core::init(GUI::GraphicalLib lib, GUI::Vector2i windowSize)
{
    _module = GUI::GraphicalFactory::createModule(lib);
    _windowSize = windowSize;
    _module->init(_windowSize);
    _module->loadModels(_config.models);

    _coms.getConf()->getActions().setGridSize(_module->getModelSize(ModelEntity::GRASS_BLOCK));

    while (!this->_coms.getConf()->isInitialized())
        this->_coms.process();
    _map = std::make_shared<Map>(_coms.getConf()->getMapSize(), _coms.getConf()->getMapContent());
    _coms.getConf()->getActions().setFrequence(_coms.getConf()->getFrequence());

    GUI::Vector3f groundSize = _module->getModelSize(ModelEntity::GRASS_BLOCK);
    _scene->getCamera()->setPosition(Vector3f(_map->getSize().x * groundSize.x / 2, 20, 20));
}

void GUI::Core::handleZoom()
{
    if (_module->isKeyPressed(GUI::Key::LEFT)) {
        _scene->getCamera()->rotateX(1);
    } else if (_module->isKeyPressed(GUI::Key::RIGHT)) {
        _scene->getCamera()->rotateX(-1);
    } else if (_module->isKeyPressed(GUI::Key::UP)) {
        _scene->getCamera()->rotateY(1);
    } else if (_module->isKeyPressed(GUI::Key::DOWN)) {
        _scene->getCamera()->rotateY(-1);
    }
}

void GUI::Core::handleSelection()
{
    GUI::Vector2i currentSelection = _map->getSelectionBlock();
    GUI::Vector2i mapSize = _map->getSize();

    if (_module->isKeyReleased(GUI::Key::LEFT)) {
        currentSelection.x = (currentSelection.x - 1 + mapSize.x) % mapSize.x;
    }
    if (_module->isKeyReleased(GUI::Key::RIGHT)) {
        currentSelection.x = (currentSelection.x + 1) % mapSize.x;
    }
    if (_module->isKeyReleased(GUI::Key::UP)) {
        currentSelection.y = (currentSelection.y - 1 + mapSize.x) % mapSize.y;
    }
    if (_module->isKeyReleased(GUI::Key::DOWN)) {
        currentSelection.y = (currentSelection.y + 1) % mapSize.y;
    }

    _map->setSelectionBlock(currentSelection);
}


void GUI::Core::handleUserInput()
{
    _module->handleEvents();
    if (_module->isKeyPressed(GUI::Key::ESCAPE))
        _running = false;
    if (_map->selectionMode() && _map->selectionType() == GUI::SelectionType::BLOCK)
        handleSelection();
    else
        handleZoom();
    if (_module->isKeyReleased(GUI::Key::R)) {
        _map->setSelectionMode(!_map->selectionMode(), GUI::SelectionType::BLOCK);
    }
    if (_module->isKeyPressed(GUI::Key::Z)) {
        _scene->getCamera()->zoom(0.1);
    } else if (_module->isKeyPressed(GUI::Key::S)) {
        _scene->getCamera()->zoom(-0.1);
    }
    if (_module->isKeyReleased(GUI::Key::H)) {
        _drawObjects = !_drawObjects;
    }
}

void GUI::Core::run()
{
    while (_running) {
        if (_coms.getConf()->isEnd()) {
            handleEndGame();
            _running = false;
            break;
        }
        handleConfigUpdate();
        _coms.process();
        handleUserInput();
        this->draw();
    }
    _module->close();
}

void GUI::Core::handleConfigUpdate()
{
    if (_coms.getConf()->getMapContent().size() > 0) {
        for (auto &block : _coms.getConf()->getMapContent()) {
            _map->getCell(block.first)->setObjects(block.second);
        }
        _coms.getConf()->getMapContent().clear();
    }

    if (_coms.getConf()->getDeadPlayers().size() > 0) {
        for (auto player : _coms.getConf()->getDeadPlayers()) {
            _coms.getConf()->deletePlayer(player);
        }
        _coms.getConf()->getDeadPlayers().clear();
    }
}

void GUI::Core::handleEndGame()
{
    std::string endMessage = "The winner is: " + _coms.getConf()->getWinnerTeam();
    std::string exitMsg = "Press esc to exit";
    while (!_module->isKeyPressed(GUI::Key::ESCAPE)) {
        _module->handleEvents();
        _module->preDraw();
        _module->clear(C_Color::C_BLACK);
        _module->drawText(endMessage, (Vector2f){static_cast<float>((_windowSize.x - endMessage.length() * 25 / 2) / 2), static_cast<float>(_windowSize.y / 2)}, 25, GUI::C_Color::C_GREEN);
        _module->drawText(exitMsg, (Vector2f){static_cast<float>((_windowSize.x - exitMsg.length() * 25 / 2) / 2), static_cast<float>(_windowSize.y / 2 + 50)}, 25, GUI::C_Color::C_GREEN);
        _module->postDraw();
    }
}

void GUI::Core::drawGround()
{
    GUI::Vector3f grassSize = _module->getModelSize(ModelEntity::GRASS_BLOCK);
    for (int y = -(_map->getSize().y * grassSize.x / 2 - (grassSize.x / 2)), yy = 0; y <= (_map->getSize().y * grassSize.x / 2 - (grassSize.x / 2)); y += 2, yy++) {
        for (int x = -(_map->getSize().x * grassSize.z / 2 - (grassSize.z / 2)), xx = 0; x <= (_map->getSize().x * grassSize.z / 2 - (grassSize.z / 2)); x += 2, xx++) {
            if (_map->selectionMode() && _map->selectionType() == SelectionType::BLOCK && _map->getSelectionBlock() == (GUI::Vector2i){xx, yy})
                continue;
            else
                _module->drawModel(ModelEntity::GRASS_BLOCK, Vector3f(x, -grassSize.y, y), 1, Vector3f(0, 0, 0));
        }
    }
}

void GUI::Core::draw()
{
    _module->preDraw();
    _module->clear(C_Color::C_WHITE);
    _module->enable3DMode(_scene->getCamera());
    this->drawGround();
    _module->drawGrid(_map->getSize(), _module->getModelSize(ModelEntity::GRASS_BLOCK).x, GUI::C_Color::C_RED);
    if (_drawObjects) {
        for (int y = 0; y < _map->getSize().y; y++) {
            for (int x = 0; x < _map->getSize().x; x++) {
                this->drawEntities(_map->getCell((GUI::Vector2i){x, y}));
            }
        }
    }
    this->drawPlayers();
    _module->disable3DMode();
    if (_map->selectionMode())
        this->drawCellDetails(_map->getCell(_map->getSelectionBlock()));
    _module->postDraw();
}

void GUI::Core::drawCellDetails(std::shared_ptr<ICell> cell)
{
    std::unordered_map<GUI::Object, int> stock;
    std::string type;
    Vector2i pos;

    if (_map->selectionType() == SelectionType::BLOCK) {
        stock = cell->getObjects();
        type = "Cell";
        pos = cell->getPos();
    } else {
        if (_coms.getConf()->getPlayers().find(_map->getPlayerId()) == _coms.getConf()->getPlayers().end())
            return;
        std::shared_ptr<IPlayer> player = _coms.getConf()->getPlayers()[_map->getPlayerId()];
        stock = player->getInventory();
        type = "Player";
        pos = player->getPos();
    }
    _module->drawRectangle((Vector2f){0, 0}, (Vector2f){static_cast<float>(30 * _windowSize.x / 100), static_cast<float>(_windowSize.y)}, GUI::C_Color::C_BLACK);

    std::string position = "Position: " + std::to_string(pos.x) + ", " + std::to_string(pos.y);
    _module->drawText(position, (Vector2f){10, 10}, 20, GUI::C_Color::C_WHITE);

    type = "Type: " + type;
    _module->drawText(type, (Vector2f){static_cast<float>(_windowSize.x - type.length() * 10 - 15), 10}, 20, GUI::C_Color::C_BLACK);

    int index = 0;
    for (auto &i : _objectsMap) {
        _module->drawText(i.second, (Vector2f){10, static_cast<float>(_windowSize.y / _objectsMap.size() * index + 40)}, 20, GUI::C_Color::C_WHITE);
        _module->drawText(std::to_string(stock[i.first]), (Vector2f){200, static_cast<float>(_windowSize.y / _objectsMap.size() * index + 40)}, 20, GUI::C_Color::C_WHITE);
        index++;
    }
}

void GUI::Core::drawEntities(std::shared_ptr<ICell> cell)
{
    float offsetX = 0.25;
    float offsetZ = 0.25;
    int count = 0;
    Vector3f grassSize = _module->getModelSize(ModelEntity::GRASS_BLOCK);
    for (auto &obj : cell->getObjects()) {
        if (obj.second >= 1) {
            Vector3f pos = _module->mousePosFromGrid(cell->getPos(), grassSize.x, _map->getSize());
            if (count != 0 && count % 3 == 0) {
                offsetX = 0.25;
                offsetZ += 0.25;
            }
            ModelEntity model = _objToModels[obj.first];
            Vector3f modelSize = _module->getModelSize(model);
            pos.z += offsetZ * grassSize.x;
            pos.x += offsetX * grassSize.x;
            if (model != ModelEntity::FOOD)
                pos.y += modelSize.y / 4;
            _module->drawModel(_objToModels[obj.first], pos, _config.models[model].scale, Vector3f(0, 0, 0));
            offsetX += 0.25;
            count++;
        }
    }
}

void GUI::Core::drawPlayers()
{
    Actions actions = _coms.getConf()->getActions();
    Vector3f offset = {0, 0, 0};
    for (auto &player : _coms.getConf()->getPlayers()) {
        if (player.second == nullptr || (player.second != nullptr && player.second->getIsAlive() == false))
            continue;
        Vector3f pos = _module->mousePosFromGrid(player.second->getPos(), _module->getModelSize(ModelEntity::GRASS_BLOCK).x, _map->getSize());
        if (actions.isAction(player.first)) {
            ActionData action = actions.getAction(player.first);
            AnimationType animation = actions.execute(player.second, _map->getCell(player.second->getPos()), action, _coms.getConf()->getPlayers(), _coms.getConf()->getClock()->getElapsedTime());
            if (animation == AnimationType::ANIM_END) {
                _coms.getConf()->getActions().deleteAction(player.first);
                player.second->setAnimation(AnimationType::ANIM_IDLE);
                continue;
            }
            offset = player.second->getOffset();
            float framerate = static_cast<float>(_module->getMaxFrame(ModelEntity::GOLEM, animation) / (actions.getDuration(action.getType()) * 1000));
            int frame = static_cast<int>((_coms.getConf()->getClock()->getElapsedTime() - action.getTimestamp()) * framerate);
            if (frame < _module->getMaxFrame(ModelEntity::GOLEM, animation))
                player.second->setCurrentFrame(frame);
        } else {
            player.second->setAnimation(AnimationType::ANIM_IDLE);
            player.second->setCurrentFrame(player.second->getCurrentFrame() + 1);
            if (_module->getMaxFrame(ModelEntity::GOLEM, player.second->getAnimation()) <= player.second->getCurrentFrame())
                player.second->setCurrentFrame(0);
        }
        _module->rotateModel(ModelEntity::GOLEM, player.second->getOrientation());
        _module->animateModel(ModelEntity::GOLEM, player.second->getAnimation(), player.second->getCurrentFrame());
        Vector3f groundSize = _module->getModelSize(ModelEntity::GRASS_BLOCK);
        Vector3f finalPos = {
            pos.x + offset.x + _module->getModelSize(ModelEntity::GRASS_BLOCK).x / 2,
            pos.y + offset.y,
            pos.z + offset.z + _module->getModelSize(ModelEntity::GRASS_BLOCK).x / 2
        };
        handleCharacterSelection(finalPos, player.second->getId());
        _module->drawModel(ModelEntity::GOLEM, finalPos, _config.models[ModelEntity::GOLEM].scale, _config.models[ModelEntity::GOLEM].rotation);
    }
}

void GUI::Core::handleCharacterSelection(Vector3f pos, int playerId)
{
    if (_module->isMouseButtonPressed(GUI::Mouse::BUTTON_LEFT)) {
        if (_module->isModelSelected(ModelEntity::GOLEM, pos, _config.models[ModelEntity::GOLEM].scale, _scene->getCamera())) {
            _map->setSelectionMode(true, SelectionType::PLAYER, playerId);
        } else {
            _map->setSelectionMode(false, SelectionType::NONE);
        }
    }
}
