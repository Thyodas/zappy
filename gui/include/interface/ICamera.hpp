/*
** EPITECH PROJECT, 2023
** gui
** File description:
** ICamera
*/

#ifndef ICAMERA_HPP_
    #define ICAMERA_HPP_

    #include "Vector3f.hpp"

namespace GUI {
    class ICamera {
        public:
            virtual ~ICamera() = default;
            virtual void setPosition(Vector3f pos) = 0;
            virtual void setTarget(Vector3f target) = 0;
            virtual void rotateX(float angle) = 0;
            virtual void rotateY(float angle) = 0;
            virtual Vector3f getPosition() const = 0;
            virtual Vector3f getTarget() const = 0;
            virtual void zoom(float value) = 0;
    };
};

#endif /* !ICAMERA_HPP_ */
