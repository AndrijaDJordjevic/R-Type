/*
** EPITECH PROJECT, 2023
** Libs [WSL: Ubuntu]
** File description:
** Color
*/

#ifndef COLOR_HPP_
    #define COLOR_HPP_

enum {
    BLACK,
    WHITE,
    RED,
    YELLOW,
    BLUE,
    GREEN,
    PURPLE
};

struct Color {
    int _Color;

    Color(int color) : _Color(color) {}
};

#endif /* !COLOR_HPP_ */
