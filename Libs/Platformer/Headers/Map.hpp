/*
** EPITECH PROJECT, 2023
** Libs [WSL: Ubuntu]
** File description:
** Map
*/

#ifndef MAP_HPP_
    #define MAP_HPP_

    #include "Registry.hpp"
    #include "Systems.hpp"
    #include "SFML/Graphics.hpp"
    #include <string>
    #include <list>

struct RectangleInfo {
    int x;
    int y;
    int width;
    int height;
};

class Map {
    public:
        Map();
        ~Map();

        void OpenFileMap(std::string path);
        void CreateShape(Registry &r, RectangleInfo i);
        void FindAllShape(Registry &r);
        void ClearMap(Registry &r);
        void LoadMap(Registry &r, std::string path);

        void Systems(Registry &r);
        void Display(Registry &r, sf::RenderWindow &window);
        void Event(Registry &r, sf::Event &event, sf::RenderWindow &rw);

    private:
        bool _loadMap;
        int  _nbrMap;
        std::vector<std::string> _pathmap;

        std::list<std::string> _map;
        std::vector<size_t> _entity;
        sf::RectangleShape _rectangle;

        std::function<void(RectangleShape &r, Velocity &v)> _ResetMove = ResetMvmtMap;
        std::function<void(RectangleShape &r, Velocity &v)> _MoveX = MvmtSystemsMapX;
        std::function<void(RectangleShape &r, Velocity &v)> _MoveMX = MvmtSystemsMapMX;
};

#endif /* !MAP_HPP_ */
