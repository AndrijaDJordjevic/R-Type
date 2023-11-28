/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu]
** File description:
** SpriteFrame
*/

#ifndef SPRITEFRAME_HPP_
    #define SPRITEFRAME_HPP_

struct SpriteFrame {
    int _spriteFrame;
    int _witdh;
    int _height;

    SpriteFrame(int spriteFrame, int w, int h) : _spriteFrame(spriteFrame), _witdh(w), _height(h) {}
};

#endif /* !SPRITEFRAME_HPP_ */
