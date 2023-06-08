/*
** EPITECH PROJECT, 2023
** B-YEP-400-STG-4-1-zappy-remi.mergen
** File description:
** Vector3f
*/

#ifndef VECTOR3F_HPP_
    #define VECTOR3F_HPP_

namespace GUI {
    class Vector3f {
        public:
            Vector3f(float xx, float yy, float zz) : x(xx), y(yy), z(zz) {};
            Vector3f() : x(0), y(0), z(0) {};
            Vector3f(const Vector3f &other) = default;
            ~Vector3f() = default;

            Vector3f operator+(const Vector3f &other) const
            {
                return Vector3f(x + other.x, y + other.y, z + other.z);
            };
            Vector3f operator-(const Vector3f &other) const
            {
                return Vector3f(x - other.x, y - other.y, z - other.z);
            };
            Vector3f& operator=( const Vector3f& v ) {
            	this->x = v.x;
                this->y = v.y;
                this->z = v.z;
                return *this;

            };
            float x;
            float y;
            float z;
    };
};

#endif /* !VECTOR3F_HPP_ */
