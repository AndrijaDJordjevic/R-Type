/*
** EPITECH PROJECT, 2023
** rtype
** File description:
** client
*/

#include "Client.hpp"

Client::Client(const std::string& server_ip, const std::string& server_port) : _socket(io_context), _server_ip(server_ip)
{
    _commandHandlers["NEW"] = std::bind(&Client::cmd_NEW, this, std::placeholders::_1);
    _commandHandlers["ACCEPT"] = std::bind(&Client::cmd_ACCEPT, this, std::placeholders::_1);
    _commandHandlers["CONNECTED"] = std::bind(&Client::cmd_CONNECTED, this, std::placeholders::_1);
    asio::ip::tcp::resolver resolver(io_context);
    asio::ip::tcp::resolver::results_type endpoints = resolver.resolve(_server_ip, server_port);
    asio::connect(_socket, endpoints);
    receiveResponse();
}

void Client::sendFirstRequest()
{
    binaryMsgClient message;
    message.errorCode = 0;

    std::cout << "select port to connect : ";
    std::string userInput;
    std::getline(std::cin, userInput);
    std::string command = "NEW " + userInput;
    std::strncpy(message.cmd, command.c_str(), sizeof(message.cmd));
    std::array<char, sizeof(binaryMsgClient)> messageBuffer;
    std::memcpy(messageBuffer.data(), &message, sizeof(binaryMsgClient));
    asio::async_write(_socket, asio::buffer(messageBuffer, sizeof(messageBuffer)),
        [this](const std::error_code& ec, std::size_t bytes_transferred) {
            if (ec) {
                std::cerr << "Erreur send : " << ec.message() << std::endl;
            }
        }
    );

}

void Client::sendRequest(const Inputs& inputs, const std::string& command)
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

void Client::receiveResponse()
{
    try {
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
                    } else {
                        std::cerr << "Commande inconnue : " << firstWord << std::endl;
                    }
                    receiveResponse();
                } else {
                    std::cerr << "Erreur lors de la réception : " << error.message() << std::endl;
                }
            }
        );
    } catch (const std::exception& e) {
        std::cerr << "Exception dans receiveResponse : " << e.what() << std::endl;    }
}


void Client::cmd_NEW(const binaryMsgServer& message)
{
    std::istringstream cmdStream(message.cmd);
    std::string cmd;
    int newPort = -1;
    cmdStream >> cmd;
    cmdStream >> newPort;
    if (newPort > 0) {
        _newServerPort = std::to_string(newPort);
        asio::ip::tcp::resolver resolver(io_context);
        asio::ip::tcp::resolver::results_type endpoints = resolver.resolve(_server_ip, _newServerPort);
        pid_t child_pid = fork();
        if (child_pid == 0) {
            Lobby lobby(_server_ip, _newServerPort);
            lobby.run();
            exit(0);
        } else if (child_pid < 0) {
            std::cout << "error fork" << std::endl;
        } else {
            std::cerr << "Error with cmd NEW" << std::endl;
        }
    }
}

void Client::cmd_ACCEPT(const binaryMsgServer& message)
{
    std::cout << "ACCEPT" << std::endl;
}

void Client::cmd_CONNECTED(const binaryMsgServer& message)
{
    std::cout << "There is already a game, do you want to join it? (y/n)" << std::endl;
    std::string userInput;
    std::getline(std::cin, userInput);
    if (userInput == "y") {
        cmd_NEW(message);
    } else if (userInput == "n") {
        sendFirstRequest();
        receiveResponse();
    } else {
        std::cout << "write y or n" << std::endl;
        cmd_CONNECTED(message);
    }
}

void Client::run()
{
    asio::io_service::work work(io_context);

    io_context.run();
}
