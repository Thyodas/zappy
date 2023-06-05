/*
** EPITECH PROJECT, 2023
** B-YEP-400-STG-4-1-zappy-remi.mergen
** File description:
** ICore
*/

#ifndef ICORE_HPP_
    #define ICORE_HPP_

namespace GUI {
    enum GraphicalLib {
        RAYLIB
    };

    struct Vector2f {
        float x;
        float y;
    };

    class ICore {
        public:
            ~ICore() = default;

            virtual void init(GraphicalLib lib, Vector2f windowSize) = 0;
            virtual void run() = 0;
        protected:
        private:
    };
};

#endif /* !ICORE_HPP_ */
