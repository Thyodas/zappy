/*
** EPITECH PROJECT, 2023
** gui
** File description:
** IClock
*/

#ifndef ICLOCK_HPP_
    #define ICLOCK_HPP_

namespace GUI {
    class IClock {
        public:
            virtual ~IClock() = default;
            virtual void restart() = 0;
            virtual double getElapsedTime() const = 0;
    };
};

#endif /* !ICLOCK_HPP_ */
