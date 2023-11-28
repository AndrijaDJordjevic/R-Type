/**
 * @file Server.cpp
 * @author antoine
 * @brief file that containing all the serer management fonctions
 * @version 0.1
 * @date 2023-10-02
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "../Headers/Server.hpp"

/**
 * @brief Construct a new Server:: Server object wthout parametre
 * !!!Don't use this fonction!!! use the constructor with the port instead
 * 
 */

Server::Server() : _port(-1), _nbLobby(0), _context(), _acceptor(_context, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), _port))
{
    asio::error_code ec;

    if (!ec) {
        std::cout << "That's not supposed to happen" << std::endl;
    } else {
        std::cout << "That's a bug" << std::endl;
    }
    exit(84);
}

/**
 * @brief Construct a new Server:: Server object with port parametre
 * 
 * @param port
 */

Server::Server(int port) : _port(port), _nbLobby(0), _context(), _acceptor(_context, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), port))
{
    asio::error_code ec;

    if (!ec) {
        std::cout << "Socket connected" << std::endl;
    } else {
        std::cout << "Socket error" << ec << std::endl;
    } try {
        startAsyncReceiveServ();
    } catch (const std::exception& e) {
        std::cerr << "ERROR: " << e.what() << std::endl;
    }
}

/**
 * @brief Receive information from clients
 * 
 */

void Server::startAsyncReceiveServ(void)
{
    std::shared_ptr<asio::ip::tcp::socket> client_socket = std::make_shared<asio::ip::tcp::socket>(_context);

    _acceptor.async_accept(*client_socket, [this, client_socket](const asio::error_code& error) {
        if (error) {
            std::cerr << "accept error: " << error.message() << std::endl;
        }
        else {
            handle_accept(client_socket);
        }
        startAsyncReceiveServ();
    });
}

Server::~Server()
{
}

/**
 * @brief use the command that he received and find the right function
 * 
 */

void Server::findFuncServ(int clientId, std::shared_ptr<asio::ip::tcp::socket> client_socket, std::string cmd)
{
    std::istringstream iss(cmd);
    std::vector<std::string> list_cmd;
    std::string temp;

    while (iss >> temp)
        list_cmd.push_back(temp);
    for (int i = 0; i < _functionListStr.size(); i++) {
        if (list_cmd.empty()) {
            if (cmd.compare("") == 0)
                break;
            if (cmd.compare(_functionListStr[i]) != 0) {
                _functionList[i](std::ref(client_socket), std::ref(list_cmd), clientId);
                return;
            }
        }
        if (_functionListStr[i].compare(list_cmd[0]) == 0) {
            list_cmd.erase(list_cmd.begin());
            _functionList[i](std::ref(client_socket), std::ref(list_cmd), clientId);
            return;
        }
    }
    std::array<char, sizeof(binaryMsgServer)> messageBuffer;
    binaryMsgServer message = getFilledMsgServ(-1, "ERROR: unknown command");
    std::memcpy(messageBuffer.data(), &message, sizeof(binaryMsgServer));
    asio::async_write(*client_socket, asio::buffer(messageBuffer), [this](const asio::error_code& error, std::size_t bytes_transferred) {
        if (error || bytes_transferred <= 0) {
            std::cerr << "Send error: " << error.message() << std::endl;
            return;
        }
    });
}

void Server::handle_accept(std::shared_ptr<asio::ip::tcp::socket> client_socket)
{
    binaryMsgServer message;

    std::cout << "Accepted a new connection." << std::endl;

    message.errorCode = 0;
    strcpy(message.cmd, "ACCEPT");
    std::array<char, sizeof(binaryMsgServer)> messageBuffer;
    std::memcpy(messageBuffer.data(), &message, sizeof(binaryMsgServer));

    asio::async_write(*client_socket, asio::buffer(messageBuffer), [this](const asio::error_code& error, std::size_t bytes_transferred) {
        if (error || bytes_transferred <= 0) {
            std::cerr << "Send error: " << error.message() << std::endl;
            return;
        }
    });

    handle_read_serv(client_socket);
}

void Server::handle_read_serv_next(std::shared_ptr<asio::ip::tcp::socket> client_socket, std::array<char, sizeof(binaryMsgClient)> recvBuffer, std::size_t bytes_read)
{
    binaryMsgClient recvMsg;
    if (bytes_read >= sizeof(binaryMsgClient)) {
        std::memcpy(&recvMsg, recvBuffer.data(), sizeof(binaryMsgClient));
//        std::cout << "Client sent : " << recvMsg.cmd << std::endl;
    } else {
        std::cerr << "ERROR: invalid read" << std::endl;
        return;
    }
    findFuncServ(0, client_socket, recvMsg.cmd);
    handle_read_serv(client_socket);
}

void Server::handle_read_serv(std::shared_ptr<asio::ip::tcp::socket> client_socket)
{
    std::array<char, sizeof(binaryMsgClient)> recvBuffer;

    asio::async_read(*client_socket, asio::buffer(recvBuffer), [this, client_socket, recvBuffer = std::ref(recvBuffer)](const asio::error_code& error, std::size_t bytes_read) {
        std::vector<std::string> temp;
        if (error == asio::error::eof || error == asio::error::connection_reset)
            handle_quit(client_socket, temp, 0);
        else if (error) {
            std::cerr << "ERROR while reading data: " << error.message() << std::endl;
            handle_read_serv(client_socket);
            return;
        } else {
            handle_read_serv_next(client_socket, recvBuffer, bytes_read);
        }
    });
}

/**
 * @brief Quit and remove informations from client
 * 
 * @param client_socket, socket of the client quitting
 */

void Server::connectToLobby(std::shared_ptr<asio::ip::tcp::socket> client_socket, std::vector<std::string> list_cmd, int clientId)
{
    int port = 0;

    if (list_cmd.size() == 1) {
        try {
            port = std::stoi(list_cmd[0]);
        } catch (const std::invalid_argument& e) {
            std::cerr << "ERROR port convertion : " << e.what() << std::endl;
        }
    }
    asio::io_service io_service;
    asio::ip::tcp::acceptor acceptor(io_service);
    try {
        acceptor.open(asio::ip::tcp::v4());
        acceptor.bind(asio::ip::tcp::endpoint(asio::ip::tcp::v4(), port));
    } catch (const std::exception& e) {
        acceptor.close();
        io_service.stop();
        for (const int& num : _portList) {
            if (num == port) {
                sendConnected(client_socket, port);
                return;
            }
        }
        sendError(client_socket, port);
        std::cerr << "Port " << port << " isn't accessible. (Already in use)" << std::endl;
        return;
    }
    std::cout << "Port " << port << " is accessible." << std::endl;
    _portList.push_back(port);
    acceptor.close();
    io_service.stop();
    pid_t child_pid = fork();
    if (child_pid == 0) {
        Lobby *data_serv = new Lobby(port);
        data_serv->waitForClient();
        exit(0);
    } else if (child_pid < 0) {
        std::cout << "error fork" << std::endl;
    }
    std::thread waitThread([this, child_pid, port] {
        int status;
        waitpid(child_pid, &status, 0);
        _portList.remove(port);
    });
    waitThread.detach();
    sendNewToClient(client_socket, port);
}

void Server::sendError(std::shared_ptr<asio::ip::tcp::socket> client_socket, int port)
{
    binaryMsgServer message = getFilledMsgServ(0, "ERROR " + std::to_string(port));
    std::array<char, sizeof(binaryMsgServer)> messageBuffer;
    std::memcpy(messageBuffer.data(), &message, sizeof(binaryMsgServer));
    asio::async_write(*client_socket, asio::buffer(messageBuffer), [this](const asio::error_code& error, std::size_t bytes_transferred) {
        if (error || bytes_transferred <= 0) {
            std::cerr << "Send error: " << error.message() << std::endl;
            return;
        }
    });
}

void Server::sendConnected(std::shared_ptr<asio::ip::tcp::socket> client_socket, int port)
{
    binaryMsgServer message = getFilledMsgServ(0, "CONNECTED " + std::to_string(port));
    std::array<char, sizeof(binaryMsgServer)> messageBuffer;
    std::memcpy(messageBuffer.data(), &message, sizeof(binaryMsgServer));
    asio::async_write(*client_socket, asio::buffer(messageBuffer), [this](const asio::error_code& error, std::size_t bytes_transferred) {
        if (error || bytes_transferred <= 0) {
            std::cerr << "Send error: " << error.message() << std::endl;
            return;
        }
    });
}

void Server::sendNewToClient(std::shared_ptr<asio::ip::tcp::socket> client_socket, int port)
{
    binaryMsgServer message = getFilledMsgServ(0, "NEW " + std::to_string(port));
    std::array<char, sizeof(binaryMsgServer)> messageBuffer;
    std::memcpy(messageBuffer.data(), &message, sizeof(binaryMsgServer));
    asio::async_write(*client_socket, asio::buffer(messageBuffer), [this](const asio::error_code& error, std::size_t bytes_transferred) {
        if (error || bytes_transferred <= 0) {
            std::cerr << "Send error: " << error.message() << std::endl;
            return;
        }
    });
}

void Server::handle_quit(std::shared_ptr<asio::ip::tcp::socket> client_socket, std::vector<std::string> list_cmd, int clientId)
{
    std::cout << "Client in Server disconnected" << std::endl;
}

binaryMsgServer Server::getFilledMsgServ(int error, std::string cmd)
{
    binaryMsgServer message;

    message.errorCode = error;
    strcpy(message.cmd, cmd.c_str());
    message.entityInfo.id = 0;
    message.entityInfo.x = 0;
    message.entityInfo.y = 0;
    strcpy(message.entityInfo.name, "temp");
    message.entityInfo.spriteType = 0;
    message.entityInfo.hp = 0;
    return message;
}

void Server::waitForClient(void)
{
    asio::io_service::work work(_context);
    _context.run();
}