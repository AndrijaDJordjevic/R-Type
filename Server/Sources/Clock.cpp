/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** clock
*/

#include "../Headers/Components/Clock.hpp"

Clock::Clock(float refreshRate) : _refreshRate(refreshRate) {
    _lastRefresh = _clock.now();
}

bool Clock::refresh() {
    auto currentTime = _clock.now();
    auto elapsedMilliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - _lastRefresh).count();

    if (elapsedMilliseconds >= static_cast<int>(_refreshRate * 1000)) {
        _lastRefresh = currentTime;
        return true;
    }
    return false;
}

bool Clock::canUpdate(float delay, float &lastRefresh) const
{
    if (lastRefresh + delay * 1000 <= getTimeMilli()) {
        lastRefresh = getTimeMilli();
        return true;
    }
    return false;
}

float Clock::getTimeMilli() const
{
    return std::chrono::duration_cast<std::chrono::milliseconds>(_clock.now().time_since_epoch()).count();
}
