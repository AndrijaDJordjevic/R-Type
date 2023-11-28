/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu]
** File description:
** main
*/

#include "Client.hpp"

int main(int argc, char** argv) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <server_ip> <server_port>" << std::endl;
        return 84;
    }

    std::string server_ip = argv[1];
    std::string server_port = argv[2];

    try {
        Client client(server_ip, server_port);
        client.sendFirstRequest();
        client.run();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 84;
    }

    return 0;
}