/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu]
** File description:
** Name
*/

#pragma once

#include <chrono>

class Clock {
public:
    Clock(float refreshRate);
    ~Clock() = default;
    bool refresh();
    bool canUpdate(float delay, float &lastUpdate) const;
    float getTimeMilli() const;
private:
    std::chrono::steady_clock _clock;
    std::chrono::steady_clock::time_point _lastRefresh;
    float _refreshRate;
};