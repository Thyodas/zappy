/*
** EPITECH PROJECT, 2023
** gui
** File description:
** Parser
*/

#include "Parser.hpp"

GUI::Parser::Parser(const std::string& path)
{
    _models = {
        {GUI::ModelEntity::GOLEM, "golem"},
        {GUI::ModelEntity::GRASS_BLOCK, "grass_block"},
        {GUI::ModelEntity::FOOD, "food"},
        {GUI::ModelEntity::LINEMATE, "linemate"},
        {GUI::ModelEntity::DERAUMERE, "deraumere"},
        {GUI::ModelEntity::SIBUR, "sibur"},
        {GUI::ModelEntity::MENDIANE, "mendiane"},
        {GUI::ModelEntity::PHIRAS, "phiras"},
        {GUI::ModelEntity::THYSTAME, "thystame"}
    };

    try {
        _config.readFile(path.c_str());
    } catch (const libconfig::FileIOException &e) {
        throw std::runtime_error("Error while reading file.");
    } catch (const libconfig::ParseException &e) {
        throw std::runtime_error("Error while parsing file.");
    }
}

GUI::Parser::~Parser()
{
}

GUI::ModelEntity GUI::Parser::getModelEntity(const std::string& name)
{
    for (auto &model : _models) {
        if (model.second == name)
            return model.first;
    }
    throw std::runtime_error("Model not found.");
}

GUI::config GUI::Parser::parseConfig()
{
    GUI::config config;
    try {
        libconfig::Setting &configSetting = _config.getRoot();
        libconfig::Setting &models = configSetting["models"];

        config.models.reserve(models.getLength());
        for (int i = 0; i < models.getLength(); ++i) {
            libconfig::Setting &setting = models[i];

            std::string name = setting["name"];
            std::string modelPath = setting["modelPath"];
            std::string texturePath = setting["texturePath"];

            float scale = setting["scale"];

            libconfig::Setting &rotation = setting["rotation"];
            float x = rotation[0];
            float y = rotation[1];
            float z = rotation[2];
            Vector3f rotationVector(x, y, z);

            config.models.insert({
                this->getModelEntity(name),
                (GUI::modelConfig){
                    modelPath,
                    texturePath,
                    scale,
                    rotationVector
                }
            });
        }
    } catch (const libconfig::SettingNotFoundException &e) {
        throw std::runtime_error("Setting not found.");
    } catch (const libconfig::SettingTypeException &e) {
        throw std::runtime_error("Setting type error.");
    } catch (const libconfig::SettingException &e) {
        throw std::runtime_error("Setting error.");
    }
    return config;
}
