/*
** EPITECH PROJECT, 2023
** B-YEP-400-STG-4-1-zappy-remi.mergen
** File description:
** Camera
*/

#ifndef CAMERA_HPP_
    #define CAMERA_HPP_

    #include "IGraphicalModule.hpp"
    #include "Vector3f.hpp"
    #include "ICamera.hpp"

namespace GUI {
    class Camera : public GUI::ICamera {
        public:
            Camera() {};
            ~Camera() = default;
            void setPosition(Vector3f pos) {
                _pos = pos;
            };
            void setTarget(Vector3f target) {
                _target = target;
            };
            Vector3f& getPosition() {
                return _pos;
            };
            Vector3f& getTarget() {
                return _target;
            };
        private:
            float _fov;
            Vector3f _pos;
            Vector3f _target;
    };
};

#endif /* !CAMERA_HPP_ */
