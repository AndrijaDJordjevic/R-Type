/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu]
** File description:
** Server
*/

#include "../Headers/Map.hpp"

UsableMap charToUsableMap(char c)
{
    switch (c)
    {
        case '.': return UsableMap::SPACE;
        case 'W': return UsableMap::WALL;
        case 'B': return UsableMap::BREAKABLE_WALL;
        case 'K': return UsableMap::KILL_WALL;
        case 'P': return UsableMap::POWER_UP;
        default: throw std::invalid_argument("Invalid character in map string");
    }
}

std::vector<std::vector<UsableMap>> fileToVector(std::string filePath)
{
    std::ifstream infile(filePath);
    std::vector<std::vector<UsableMap>> map;
    std::string line;

    if (!infile.is_open()) {
        std::cerr << "Error opening file: " << filePath << std::endl;
        return map;
    }

    while (std::getline(infile, line))
    {
        std::vector<UsableMap> row;
        for (char c : line)
        {
            row.push_back(charToUsableMap(c));
        }
        map.push_back(row);
    }
    return map;
}

void printVectorString(std::vector<std::vector<UsableMap>> map)
{
    for (const auto& vec : map) {
        for (const auto& elem : vec) {
            std::cout << static_cast<int>(elem);
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

std::vector<Room> ParseRoomsFile(const std::string& filename) {
    std::vector<Room> rooms;

    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return rooms;
    }

    std::string line;
    Room currentRoom;

    while (std::getline(file, line)) {
        line.erase(line.find_last_not_of(" \t") + 1);
        line.erase(0, line.find_first_not_of(" \t"));

        if (line.empty()) {
            continue;
        }

        if (line == "{") {
            currentRoom = {};
        } else if (line == "}") {
            rooms.push_back(currentRoom);
        } else {
            std::istringstream iss(line);
            std::string key, value;

            if (std::getline(iss, key, ':') && std::getline(iss, value)) {
                key = key.substr(0, key.find_last_not_of(" \t") + 1);
                value = value.substr(value.find_first_not_of(" \t"));

                if (key == "Map_name") {
                    currentRoom.setName(value);
                } else if (key == "Path") {
                    currentRoom.setPath(value);
                } else if (key == "x") {
                    currentRoom.setx(std::stoi(value));
                } else if (key == "y") {
                    currentRoom.sety(std::stoi(value));
                } else if (key == "Difficulty") {
                    currentRoom.setDifficulty(std::stoi(value));
                } else if (key == "boss") {
                    currentRoom.setBoss(value == "true");
                }
            }
        }
    }

    file.close();
    return rooms;
}