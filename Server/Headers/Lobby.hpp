/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-1-rtype-adam.bentaleb
** File description:
** Lobby
*/

#ifndef LOBBY_HPP_
#define LOBBY_HPP_

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

    #define MAX_PLAYER 4

struct Inputs {
    bool left;
    bool right;
    bool up;
    bool down;
};

struct s_entity {
    int id;
    int x;
    int y;
    char name[1024];
    int spriteType;
    int hp;
    int velocity_x;
    int velocity_y;
    int deleted;
};

struct binaryMsgServer {
    int64_t errorCode;
    s_entity entityInfo;
    char cmd[1024];
};

struct binaryMsgClient {
    int64_t errorCode;
    Inputs _input;
    char cmd[1024];
};

class Lobby {
    public:
        Lobby(int port);
        ~Lobby();

        class ClientInLobby {
            public:
                ClientInLobby(Registry& registry);
                ~ClientInLobby() {};

                void initClient(void);
                void initBullet(void);
                void setRecvMsg(binaryMsgClient recvdMsg);
                binaryMsgClient getRecvMsg();
                void setId(int id);
                int getId(void);
                void setDeleted(int deleted);
                int getDeleted(void);
                void setX(int x);
                int getX(void);
                void setY(int y);
                int getY(void);
                void setName(char *name);
                char *getName(void);
                void setSpriteFrame(int spriteFrame);
                int getSpriteFrame(void);
                void setHp(int hp);
                int getHp(void);
                int getVY(void);
                int getVX(void);
                std::shared_ptr<asio::ip::tcp::socket> getSocket();
                void setSocket(std::shared_ptr<asio::ip::tcp::socket> socket);
                size_t getIdEntity(void);

            private:
                std::shared_ptr<asio::ip::tcp::socket> _client_socket;
                binaryMsgClient _recvdMsg;
                asio::io_context _uselessContext;

                size_t _idEntity;
                Registry &_registry;
        };

        void waitForClient(void);

        void initRegistry(void);
        void gameSystems(void);

        void handle_accept(std::shared_ptr<asio::ip::tcp::socket> client_socket);
        void handle_read(std::shared_ptr<asio::ip::tcp::socket> client_socket);
        void handle_read_next(std::shared_ptr<asio::ip::tcp::socket> client_socket, std::array<char, sizeof(binaryMsgClient)> recvBuffer, std::size_t bytes_read);
        void startAsyncReceive(void);
        void handle_quit(std::shared_ptr<asio::ip::tcp::socket> client_socket, std::vector<std::string> list_cmd, int clientId);
        void findFunc(int clientId, std::shared_ptr<asio::ip::tcp::socket> client_socket);
        int findClient(std::shared_ptr<asio::ip::tcp::socket> client_socket);
        void sendNewConnection(std::shared_ptr<asio::ip::tcp::socket> client_socket, int clientId, int i);
        void connectToLobby(std::shared_ptr<asio::ip::tcp::socket> client_socket, int clientId);
        void sendTooManyPlayer(std::shared_ptr<asio::ip::tcp::socket> client_socket);
        void sendAlreadyConnected(int clientId);
        binaryMsgServer getFilledMsg(int error, std::string cmd, int idx_fill);
        void handleInput(std::shared_ptr<asio::ip::tcp::socket> client_socket, std::vector<std::string> list_cmd, int clientId);
        void startSendLoop(void);
        void sendInfoGame(int i, int idx_fill);
        void sendInfoGameLoop(int idx);
        bool isPlayer(binaryMsgServer message);
        void callLoose(void);
        void callWin(void);
        int checkEnd();

        std::vector<std::function<void(std::shared_ptr<asio::ip::tcp::socket>, std::vector<std::string>, int)>> _functionList =
            {std::bind(&Lobby::handleInput, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3),
            std::bind(&Lobby::handle_quit, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3)};

        const std::vector<std::string> _functionListStr = {"INPUT", "LEAVE"};
        private:
            int _port;
            int _nbPlayer;

            asio::io_context _context;
            asio::ip::tcp::acceptor _acceptor;
            asio::steady_timer _timer;

            ClientInLobby _listClient[MAX_PLAYER] {
                ClientInLobby(_registry),
                ClientInLobby(_registry),
                ClientInLobby(_registry),
                ClientInLobby(_registry)
            };

            std::shared_ptr<Clock> _clock;
            float _refreshMvmt;
            float _refreshFireRate;
            float _refreshSpawnRate;
            int score;

            inline static Registry _registry;
        };

#endif /* !LOBBY_HPP_ */
