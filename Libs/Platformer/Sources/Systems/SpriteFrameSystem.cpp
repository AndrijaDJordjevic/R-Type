/*
** EPITECH PROJECT, 2023
** Libs [WSL: Ubuntu]
** File description:
** SpriteFrameSystem
*/

#include "Systems.hpp"

void UpdateFrameSprite(SpriteFrame &s, Clock &c, Input &i)
{
    if (c.refresh()) {
        if (i._right || i._left)
            s._spriteFrame += 1;
        else
            s._spriteFrame = 0;
    }
    if (s._spriteFrame > 11)
        s._spriteFrame = 0;
}
