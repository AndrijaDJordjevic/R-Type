/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu]
** File description:
** Player
*/

#ifndef PLAYER_HPP_
#define PLAYER_HPP_

struct Id {
    int _Id;
    size_t _Index;

    Id(int id, size_t index) : _Id(id), _Index(index) {}
};

#endif /* !PLAYER_HPP_ */
