/*
** EPITECH PROJECT, 2023
** Libs [WSL: Ubuntu]
** File description:
** Clock
*/

#ifndef CLOCK_HPP_
    #define CLOCK_HPP_

#include <chrono>

class Clock {
    public:
        Clock(float refreshRate) : _refreshRate(refreshRate) {
            _lastRefresh = _clock.now();
        }
        ~Clock() = default;
        bool refresh() {
            auto currentTime = _clock.now();
            auto elapsedMilliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - _lastRefresh).count();

            if (elapsedMilliseconds >= static_cast<int>(_refreshRate * 1000)) {
                _lastRefresh = currentTime;
                return true;
            }
            return false;
        }

    private:
        std::chrono::steady_clock _clock;
        std::chrono::steady_clock::time_point _lastRefresh;
        float _refreshRate;
};

#endif /* !CLOCK_HPP_ */
