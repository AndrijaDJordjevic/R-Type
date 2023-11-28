/*
** EPITECH PROJECT, 2023
** Server
** File description:
** main
*/

#include "Headers/Server.hpp"

void printHelp(void)
{
    printf("USAGE:\n\t./Rtype_server -p port"
    "\n\tport\tis the port number\n");
}

int main(int ac, char **av)
{
    int port = -1;

    if (ac == 2 && (strcmp(av[1], "--help") == 0 || strcmp(av[1], "-h"))) {
        printHelp();
        return 0;
    }
    if (checkArgsInit(av, &port) == -1 || ac < 2) {
        fprintf(stderr, "ERROR WRONG ARGS\n");
        printHelp();
        return 84;
    }
    std::cout << "port = " << port << std::endl;
    Server *data_serv = new Server(port);

    data_serv->waitForClient();
    return 0;
}
