/*
** EPITECH PROJECT, 2023
** gui
** File description:
** Parser
*/

#include "Parser.hpp"
#include <string>
#include <map>
#include <string>

GUI::Parser::Parser(const std::string& path)
{
    try {
        _config.readFile(path.c_str());
    } catch (const libconfig::FileIOException &e) {
        std::cerr << "Error while reading file." << std::endl;
        exit(84);
    } catch (const libconfig::ParseException &e) {
        std::cerr << "Parse error at " << e.getFile() << ":" << e.getLine() << " - " << e.getError() << std::endl;
        exit(84);
    }
}

GUI::Parser::~Parser()
{
}

GUI::ModelEntity GUI::Parser::getModelEntity(const std::string& name)
{
    std::map<GUI::ModelEntity, std::string> models = {
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

    for (auto &model : models) {
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

            config.models.insert({
                this->getModelEntity(name),
                (GUI::modelConfig){
                    modelPath,
                    texturePath
                }
            });
        }
    } catch (const libconfig::SettingNotFoundException &e) {
        std::cerr << "Setting not found." << std::endl;
        exit(84);
    } catch (const libconfig::SettingTypeException &e) {
        std::cerr << "Setting type error." << std::endl;
        exit(84);
    } catch (const libconfig::SettingException &e) {
        std::cerr << "Setting error." << std::endl;
        exit(84);
    }
    return config;
}
