/*
** EPITECH PROJECT, 2023
** B-YEP-400-STG-4-1-zappy-remi.mergen
** File description:
** Scene
*/

#ifndef SCENE_HPP_
    #define SCENE_HPP_

    #include "Camera.hpp"

class Scene {
    public:
        Scene() {};
        ~Scene() = default;
        GUI::Camera& getCamera() {
            return camera;
        };
    private:
        GUI::Camera camera;
        // TODO: add a list of objects
};

#endif /* !SCENE_HPP_ */
