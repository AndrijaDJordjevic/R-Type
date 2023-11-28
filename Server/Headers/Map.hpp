/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu]
** File description:
** Server
*/

#ifndef MAP_HPP_
#define MAP_HPP_

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>

enum UsableMap {
    SPACE,
    WALL,
    BREAKABLE_WALL,
    KILL_WALL,
    POWER_UP,
};

class Room {
    public:
        Room(): _x(0), _y(0), _difficulty(0), _boss(false) {}
        ~Room();

        void PrintInfo() {
        std::cout << "Name: " << _name << std::endl;
        std::cout << "X: " << _x << std::endl;
        std::cout << "Y: " << _y << std::endl;
        std::cout << "Path: " << _path << std::endl;
        std::cout << "Difficulty: " << _difficulty << std::endl;
        std::cout << "Boss: " << (_boss ? "true" : "false") << std::endl;
        std::cout << std::endl;
        }
        std::string getName();
        void setName(std::string name);
        std::string getPath();
        void setPath(std::string path);
        int getx();
        void setx(int x);
        int gety();
        void sety(int y);
        int getDifficulty();
        void setDifficulty(int difficulty);
        bool getBoss();
        void setBoss(bool boss);

    protected:
        std::string _name;
        std::string _path;
        int _x;
        int _y;
        int _difficulty;
        bool _boss;
};

class Map {
    public:
        Map();
        ~Map();
        void PrintMaps();
        void PrintRoomsInfos();
        void SetupMapRooms();
        void UpdateMap();
        void CopyMap(std::vector<std::vector<UsableMap>> *map, bool boss);

        std::vector<std::vector<UsableMap>> getCurrentMap();
        std::vector<std::vector<UsableMap>> getNextMap();
        

    protected:
        std::vector<Room> _rooms;
        std::vector<std::vector<std::vector<UsableMap>>> _maps;
        std::vector<std::vector<UsableMap>> _current_map;
        std::vector<std::vector<UsableMap>> _next_map;
        int _current_room;
        int x_max;
        int y_max;
    private:
};

std::vector<std::vector<UsableMap>> fileToVector(std::string filePath);
void printVectorString(std::vector<std::vector<UsableMap>> map);
std::vector<Room> ParseRoomsFile(const std::string& filename);

#endif
