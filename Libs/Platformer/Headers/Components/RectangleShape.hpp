/*
** EPITECH PROJECT, 2023
** Libs [WSL: Ubuntu]
** File description:
** Shape
*/

#ifndef SHAPE_HPP_
    #define SHAPE_HPP_

struct RectangleShape {
    int _width;
    int _height;

    RectangleShape(int w, int h) : _width(w), _height(h) {}
};

#endif /* !SHAPE_HPP_ */
