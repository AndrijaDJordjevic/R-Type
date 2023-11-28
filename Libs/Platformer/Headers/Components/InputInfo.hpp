/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu]
** File description:
** Input
*/
struct InputInfo {
    bool _left;
    bool _right;
    bool _up;
    bool _down;
    bool _fire;

    InputInfo(bool lk, bool rk, bool dk, bool uk, bool fk) : _left(lk), _right(rk), _up(uk), _down(dk), _fire(fk) {}
};
