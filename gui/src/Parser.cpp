/*
** EPITECH PROJECT, 2023
** gui
** File description:
** Parser
*/

#include "Parser.hpp"
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

            if (name == "golem") {
                std::cout << "inside condition" << std::endl;
                config.models.insert({
                    GUI::ModelEntity::GOLEM,
                    (GUI::modelConfig){
                        modelPath,
                        texturePath
                    }
                });
            }
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
