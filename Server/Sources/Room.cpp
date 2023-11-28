/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu]
** File description:
** Server
*/

#include "../Headers/Map.hpp"

Room::~Room()
{

}

std::string Room::getName() 
{
    return this->_name;
}

void Room::setName(std::string name)
{
    this->_name = name;
}

std::string Room::getPath()
{
    return this->_path;
}

void Room::setPath(std::string path)
{
    this->_path = path;
}

int Room::getx()
{
    return this->_x;
}

void Room::setx(int x)
{
    this->_x = x;
}

int Room::gety()
{
    return this->_y;
}

void Room::sety(int y)
{
    this->_y = y;
}

int Room::getDifficulty()
{
    return this->_difficulty;
}

void Room::setDifficulty(int difficulty)
{
    this->_difficulty = difficulty;
}

bool Room::getBoss()
{
    return this->_boss;
}

void Room::setBoss(bool boss)
{
    this->_boss = boss;
}
