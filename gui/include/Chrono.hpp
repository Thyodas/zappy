/*
** EPITECH PROJECT, 2023
** gui
** File description:
** Chrono
*/

#ifndef CHRONO_HPP_
    #define CHRONO_HPP_

    #include <chrono>
    #include "IClock.hpp"

    #define NANO_TO_MILLI 1'000'000.0

namespace GUI {
    class Chrono : public IClock {
        public:
            Chrono() { restart(); };
            ~Chrono() = default;
            void restart() {
                _start_time = _clock.now();
            };
            double getElapsedTime() const {
                auto elapsed_time_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(_clock.now() - _start_time).count();
                return static_cast<double>(elapsed_time_ns) / NANO_TO_MILLI;
            };
        protected:
        private:
            std::chrono::high_resolution_clock _clock;
            std::chrono::high_resolution_clock::time_point _start_time;
    };
};

#endif /* !CHRONO_HPP_ */
