/*
** EPITECH PROJECT, 2023
** rtype
** File description:
** Lobby
*/

#pragma once

#include "Game.hpp"
#include <iostream>
#include <asio.hpp>
#include <string>
#include <memory>
#include <map>
#include <functional>
#include <chrono>
#include <thread>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

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
    Inputs input;
    char cmd[1024];
};

class Lobby
{
public:
    Lobby(const std::string& server_ip, const std::string& server_port);
    ~Lobby();

    void run();
    // void sendFirstRequest();
    void sendRequest(const Inputs& inputs, const std::string& command);
    void receiveResponse();
    // void receiveResponseLobby();

    void cmd_GAME(const binaryMsgServer& message);
    // void cmd_NEW(const binaryMsgServer& message);
    void cmd_ACCEPT(const binaryMsgServer& message);
    void cmd_CONNECTED(const binaryMsgServer& message);
    void cmd_WIN(const binaryMsgServer& message);
    void cmd_LOSE(const binaryMsgServer& message);


private:
    Registry _registry;
    std::unique_ptr<Game> _game;
    Entity _entity;
    int _curent_id;
    asio::io_context io_context;
    asio::io_context _io_context_lobby;
    asio::ip::tcp::socket _socket;
    std::shared_ptr<asio::ip::tcp::socket> _socket_lobby;
    std::map<std::string, std::function<void(const binaryMsgServer&)>> _commandHandlers;
    struct binaryMsgServer _received_message;
    std::array<char, sizeof(binaryMsgServer)> _recv_buf;
    const std::string& _server_ip;
};
