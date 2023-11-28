/*
** EPITECH PROJECT, 2023
** Server
** File description:
** CheckArgs
*/

#include "../Headers/Server.hpp"

static std::vector<std::string> string_args = {"-p"};

int checkList(std::string str, std::vector<std::string> list)
{
    for (int x = 0; x <= 0; x++) {
        if (str.compare(list[x]) == 0)
            return 0;
    } return -1;
}

int check_p(char **av, int i, int *port)
{
    if (strcmp(av[i], "-p") == 0 && av[i + 1] != NULL && atoi(av[i + 1]) != 0) {
        *port = atoi(av[i + 1]);
        asio::io_service io_service;
        asio::ip::tcp::acceptor acceptor(io_service);
        try {
            acceptor.open(asio::ip::tcp::v4());
            acceptor.bind(asio::ip::tcp::endpoint(asio::ip::tcp::v4(), *port));
        } catch (const std::exception& e) {
            acceptor.close();
            io_service.stop();
            std::cout << "Port " << *port << " isn't accessible. (Already in use)" << std::endl;
            return -1;
        }
        acceptor.close();
        io_service.stop();
        return 0;
    }
    return (checkList(av[i], string_args));
}

int checkArgsInit(char **av, int *port)
{
    for (int i = 1; av[i] != NULL; i += 2) {
        if (check_p(av, i, port) == -1)
            return -1;
    } return 0;
}