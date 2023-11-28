/*
** EPITECH PROJECT, 2023
** rtype
** File description:
** Lobby
*/

#include "Lobby.hpp"

Lobby::Lobby(const std::string& server_ip, const std::string& server_port) : _socket(io_context), _server_ip(server_ip)
{
    _registry = Registry();
    _game = std::make_unique<Game>(std::make_shared<Registry>(_registry));
    _commandHandlers["GAME"] = std::bind(&Lobby::cmd_GAME, this, std::placeholders::_1);
    _commandHandlers["ACCEPT"] = std::bind(&Lobby::cmd_ACCEPT, this, std::placeholders::_1);
    _commandHandlers["CONNECTED"] = std::bind(&Lobby::cmd_CONNECTED, this, std::placeholders::_1);
    _commandHandlers["WIN"] = std::bind(&Lobby::cmd_WIN, this, std::placeholders::_1);
    _commandHandlers["LOSE"] = std::bind(&Lobby::cmd_LOSE, this, std::placeholders::_1);
    asio::ip::tcp::resolver resolver(io_context);
    asio::ip::tcp::resolver::results_type endpoints = resolver.resolve(_server_ip, server_port);
    asio::connect(_socket, endpoints);
    
    receiveResponse();
}

Lobby::~Lobby()
{
}

void Lobby::sendRequest(const Inputs& inputs, const std::string& command)
{
    binaryMsgClient message;

    message.errorCode = 0;
    message.input.left = inputs.left;
    message.input.right = inputs.right;
    message.input.up = inputs.up;
    message.input.down = inputs.down;
    std::strncpy(message.cmd, command.c_str(), sizeof(message.cmd));
    std::array<char, sizeof(binaryMsgClient)> messageBuffer;
    std::memcpy(messageBuffer.data(), &message, sizeof(binaryMsgClient));
    asio::async_write(_socket, asio::buffer(messageBuffer, sizeof(messageBuffer)),
        [this](const std::error_code& ec, std::size_t bytes_transferred) {
            if (ec)
                std::cerr << "Error sending data: " << ec.message() << std::endl;
        }
    );
}

void Lobby::receiveResponse()
{
    asio::async_read(_socket, asio::buffer(_recv_buf),
        [this](const asio::error_code& error, std::size_t bytes_transferred) {
            if (!error) {
                std::memcpy(&_received_message, _recv_buf.data(), sizeof(binaryMsgServer));
                std::string receivedCommand = _received_message.cmd;
                std::istringstream iss(receivedCommand);
                std::string firstWord;
                iss >> firstWord;
                if (_commandHandlers.find(firstWord) != _commandHandlers.end()) {
                    _commandHandlers[firstWord](_received_message);
                    if (firstWord == "WIN" || firstWord == "LOSE")
                        exit(0);
                } else {
                    std::cerr << "Commande inconnue : " << firstWord << std::endl;
                }
                _game->updateData(_curent_id, _entity);
            } else {
                std::cerr << "Erreur lors de la réception : " << error.message() << std::endl;
            }
            receiveResponse();
        }
    );
}

void Lobby::cmd_GAME(const binaryMsgServer& message)
{
    if (message.entityInfo.id != 0) {
        _curent_id = message.entityInfo.id;
        _entity.x = message.entityInfo.x;
        _entity.y = message.entityInfo.y;
        _entity.spriteType = message.entityInfo.spriteType;
        _entity.name = std::string(message.entityInfo.name);
        _entity.hp = message.entityInfo.hp;
        _entity.velocityX = message.entityInfo.velocity_x;
        _entity.velocityY = message.entityInfo.velocity_y;
        _entity.deleted = message.entityInfo.deleted;
        _game->updateData(_curent_id, _entity);
    }
    std::optional<Inputs> input = _game->refresh();

    if (input.has_value()) {
        Inputs inputs = input.value();
        sendRequest(inputs, "INPUT test");
    } else {
        std::cerr << "." << std::endl;
    }
}

void Lobby::cmd_ACCEPT(const binaryMsgServer& message)
{
    std::cout << "ACCEPT" << std::endl;
}

void Lobby::cmd_CONNECTED(const binaryMsgServer& message)
{
    std::cout << "CONNECTED" << std::endl;
}

void Lobby::cmd_WIN(const binaryMsgServer& message)
{
    _game->endOfGame(true);
}

void Lobby::cmd_LOSE(const binaryMsgServer& message)
{
    _game->endOfGame(false);
}

void Lobby::run()
{
    asio::io_service::work work(io_context);

    io_context.run();
}

