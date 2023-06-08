/*
** EPITECH PROJECT, 2023
** B-YEP-400-STG-4-1-zappy-remi.mergen
** File description:
** Scene
*/

#ifndef SCENE_HPP_
    #define SCENE_HPP_

    #include "ICamera.hpp"
    #include "RayLibCamera.hpp"

class Scene {
    public:
        Scene() : _camera(std::make_shared<GUI::RayLibCamera>()) {};
        ~Scene() = default;
        std::shared_ptr<GUI::ICamera>& getCamera() {
            return _camera;
        };
    private:
        std::shared_ptr<GUI::ICamera> _camera;
        // TODO: add a list of objects
};

#endif /* !SCENE_HPP_ */
