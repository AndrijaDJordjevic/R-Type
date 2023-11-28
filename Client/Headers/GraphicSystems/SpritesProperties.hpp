/*
** EPITECH PROJECT, 2023
** rtype
** File description:
** spritesProperties
*/

#pragma once

//FONT
#define FONT_PATH "Client/Assets/Fonts/CatCafe.ttf"

//BACKGROUND
#define CAVE_0_PATH "Client/Assets/Sprites/cave_bg_0.png"
#define CAVE_1_PATH "Client/Assets/Sprites/cave_bg_1.png"
#define CAVE_2_PATH "Client/Assets/Sprites/cave_bg_2.png"
#define CAVE_3_PATH "Client/Assets/Sprites/cave_bg_3.png"
#define CAVE_SIZE_X 384
#define CAVE_SIZE_Y 216
#define CAVE_SHEET_WIDTH 3
#define CAVE_SHEET_HEIGHT 1

//PLAYER
#define PLAYER_PATH "Client/Assets/Sprites/playerSprite.png"
#define PLAYER_SIZE_X 34 // sprite pixels width
#define PLAYER_SIZE_Y 15 // sprite pixels height
#define PLAYER_SHEET_WIDTH 4 // number of sprites in width
#define PLAYER_SHEET_HEIGHT 4 // number of sprites in height

//PROJECTILE
#define PROJECTILE_PATH "Client/Assets/Sprites/projectile.png"
#define PROJECTILE_SIZE_X 16
#define PROJECTILE_SIZE_Y 8
#define PROJECTILE_SHEET_WIDTH 1
#define PROJECTILE_SHEET_HEIGHT 1

//ENEMY
#define ENEMY_PATH "Client/Assets/Sprites/enemy.png"
#define ENEMY_SIZE_X 34
#define ENEMY_SIZE_Y 15
#define ENEMY_SHEET_WIDTH 3
#define ENEMY_SHEET_HEIGHT 1

enum SpriteType {
    PLAYER = 1,
    PROJECTILE = 2,
    ENEMY = 3,
    CAVE_0 = 4,
    CAVE_1 = 5,
    CAVE_2 = 6,
    CAVE_3 = 7
};
