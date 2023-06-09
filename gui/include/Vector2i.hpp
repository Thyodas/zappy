/*
** EPITECH PROJECT, 2023
** gui
** File description:
** Vector2i
*/

#ifndef VECTOR2I_HPP_
#define VECTOR2I_HPP_

namespace GUI {
    class Vector2i {
        public:
            Vector2i(int x, int y) {
                this->x = x;
                this->y = y;
            };
            Vector2i() {
                this->x = 0;
                this->y = 0;
            };
            ~Vector2i() = default;
            bool operator==(const Vector2i &v2) {
                return (this->x == v2.x && this->y == v2.y);
            };
            Vector2i operator+(const Vector2i &v2) {
                return (Vector2i(this->x + v2.x, this->y + v2.y));
            };
            int x;
            int y;
    };
};

#endif /* !VECTOR2I_HPP_ */
