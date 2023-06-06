/*
** EPITECH PROJECT, 2023
** B-YEP-400-STG-4-1-zappy-remi.mergen
** File description:
** RayLibCamera
*/

#ifndef RAYLIBCAMERA_HPP_
    #define RAYLIBCAMERA_HPP_

    #include "IGraphicalModule.hpp"
    #include "Vector3f.hpp"
    #include "ICamera.hpp"
    #include <raylib.h>

namespace GUI {
    class RayLibCamera : public GUI::ICamera {
        public:
            RayLibCamera() {
                camera.position = (Vector3){ 10.0f, 10.0f, 10.0f };
                camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
                camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
                camera.fovy = 45.0f;
                camera.projection = CAMERA_PERSPECTIVE;
            };
            ~RayLibCamera() = default;
            void setPosition(Vector3f pos) {
                camera.position = (Vector3){ pos.x, pos.y, pos.z };
            };
            void setTarget(Vector3f target) {
                camera.target = (Vector3){ target.x, target.y, target.z };
            };
            Vector3f getPosition() const {
                return (GUI::Vector3f){camera.position.x, camera.position.y, camera.position.z};
            };
            Vector3f getTarget() const {
                return (GUI::Vector3f){camera.target.x, camera.target.y, camera.target.z};
            };

            Camera camera;
    };
};

#endif /* !RAYLIBCAMERA_HPP_ */
