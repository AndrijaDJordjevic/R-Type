/*
** EPITECH PROJECT, 2023
** rtype
** File description:
** client
*/

#pragma once

#include "Game.hpp"
#include "Lobby.hpp"
#include <iostream>
#include <asio.hpp>
#include <string>
#include <memory>
#include <map>
#include <functional>


class Client
{
public:
    Client(const std::string& server_ip, const std::string& server_port);

    void run();
    void sendFirstRequest();
    void sendRequest(const Inputs& inputs, const std::string& command);
    void receiveResponse();

    void cmd_GAME(const binaryMsgServer& message);
    void cmd_NEW(const binaryMsgServer& message);
    void cmd_ACCEPT(const binaryMsgServer& message);
    void cmd_CONNECTED(const binaryMsgServer& message);

private:
    Registry _registry;
    std::unique_ptr<Game> _game;
    asio::io_context io_context;
    asio::io_context _io_context_lobby;
    asio::ip::tcp::socket _socket;
    std::shared_ptr<asio::ip::tcp::socket> _socket_lobby;
    std::map<std::string, std::function<void(const binaryMsgServer&)>> _commandHandlers;
    struct binaryMsgServer _received_message;
    std::array<char, sizeof(binaryMsgServer)> _recv_buf;
    std::string _newServerPort;
    const std::string& _server_ip;
};
