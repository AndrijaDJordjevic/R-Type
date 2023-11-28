/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu]
** File description:
** Server
*/

#include "../Headers/Map.hpp"
#include <chrono>
#include <thread>

int ServerLogic(void)
{
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    Map map;
    int intervalle_affichage = 1;
    auto temps_debut = std::chrono::high_resolution_clock::now();
    
    while (true) {
        auto temps_actuel = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> temps_ecoule = temps_actuel - temps_debut;

        if (temps_ecoule.count() >= intervalle_affichage) {
            map.UpdateMap();
            std::cout << "PRINT CURRENT MAP :" << std::endl;
            printVectorString(map.getCurrentMap());
            std::cout << "PRINT COMING NEXT :" << std::endl;
            printVectorString(map.getNextMap());
            temps_debut = temps_actuel;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    return 0;
}