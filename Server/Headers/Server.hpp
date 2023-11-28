/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu]
** File description:
** Server
*/

#ifndef SERVER_HPP_
    #define SERVER_HPP_

    #include <algorithm>
    #include <cstring>
    #include <iostream>
    #include <vector>
    #include <chrono>
    #include <thread>
    #include <random>
    #include <functional>
    #include <asio.hpp>
    #include <asio/ts/buffer.hpp>
    #include <asio/ts/internet.hpp>
    #include "Systems.hpp"
    #include <list>
    #include <sys/wait.h>

    #include "Registry.hpp"
    #include "Lobby.hpp"

    class Server {
        public:
            Server();
            Server(int port);
            ~Server();

            void connectToLobby(std::shared_ptr<asio::ip::tcp::socket> client_socket, std::vector<std::string> list_cmd, int clientId);
            void sendError(std::shared_ptr<asio::ip::tcp::socket> client_socket, int port);
            void sendConnected(std::shared_ptr<asio::ip::tcp::socket> client_socket, int port);
            void sendNewToClient(std::shared_ptr<asio::ip::tcp::socket> client_socket, int port);
            void handle_accept(std::shared_ptr<asio::ip::tcp::socket> client_socket);
            void handle_read_serv(std::shared_ptr<asio::ip::tcp::socket> client_socket);
            void handle_read_serv_next(std::shared_ptr<asio::ip::tcp::socket> client_socket, std::array<char, sizeof(binaryMsgClient)> recvBuffer, std::size_t bytes_read);
            void startAsyncReceiveServ(void);
            void findFuncServ(int clientId, std::shared_ptr<asio::ip::tcp::socket> client_socket, std::string cmd);
            void handle_quit(std::shared_ptr<asio::ip::tcp::socket> client_socket, std::vector<std::string> list_cmd, int clientId);
            binaryMsgServer getFilledMsgServ(int error, std::string cmd);
            void waitForClient(void);

            const std::vector<std::string> _functionListStr = {"NEW", "LEAVE"};
            std::vector<std::function<void(std::shared_ptr<asio::ip::tcp::socket>&, std::vector<std::string>, int)>> _functionList = {
                std::bind(&Server::connectToLobby, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3),
                std::bind(&Server::handle_quit, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3)
            };
        private:
            int _port;
            int _nbLobby;
            asio::io_context _context;
            asio::ip::tcp::acceptor _acceptor;
            std::list<int> _portList;
    };

    // CheckArgs.cpp
    int checkArgsInit(char **av, int *port);
    int check_p(char **av, int i, int *port);
    int checkList(std::string str, std::vector<std::string> list);

#endif /* !SERVER_HPP_ */
