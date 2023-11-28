/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-1-rtype-adam.bentaleb
** File description:
** Lobby
*/

/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-1-rtype-adam.bentaleb
** File description:
** Lobby
*/

#include "../Headers/Lobby.hpp"

/**
 * @brief Construct a new Server:: Server object with port parametre
 * 
 * @param port 
 */

Lobby::Lobby(int port) : _port(port), _nbPlayer(0), _context(), _acceptor(_context, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), _port)), _timer(_context, std::chrono::milliseconds(50))
{
    initRegistry();
    asio::error_code ec;

    try {
        for (int i = 0; i < MAX_PLAYER; i++) {
            _listClient[i].initClient();
        }

        startAsyncReceive();
        startSendLoop();
    } catch (const std::exception& e) {
        std::cerr << "ERROR: " << e.what() << std::endl;
    }
    this->score = 0;
}

void Lobby::ClientInLobby::initClient(void)
{
    char str[1024] = "default";
    _idEntity = _registry.spawnEntity();

    _registry.emplaceComponent<Id>(_idEntity, 0, _idEntity);
    _registry.emplaceComponent<Position>(_idEntity, 100, 500);
    _registry.emplaceComponent<Name>(_idEntity, str);
    _registry.emplaceComponent<Collider>(_idEntity, PLAYER_SIZE_X, PLAYER_SIZE_Y);
    _registry.emplaceComponent<InputInfo>(_idEntity, false, false, false, false, false);
    _registry.emplaceComponent<SpriteFrame>(_idEntity, 1);
    _registry.emplaceComponent<Health>(_idEntity, 3);
    _registry.emplaceComponent<Velocity>(_idEntity, 0, 0);
    _registry.emplaceComponent<Clock>(_idEntity, 1.5);
    _registry.emplaceComponent<Deleted>(_idEntity, -1);
}

void Lobby::initRegistry(void)
{
    _registry.registerComponent<Position>();
    _registry.registerComponent<Velocity>();
    _registry.registerComponent<Collider>();
    _registry.registerComponent<Health>();
    _registry.registerComponent<Name>();
    _registry.registerComponent<SpriteFrame>();
    _registry.registerComponent<Damage>();
    _registry.registerComponent<Id>();
    _registry.registerComponent<InputInfo>();
    _registry.registerComponent<Clock>();
    _registry.registerComponent<Deleted>();
    _registry.registerComponent<Projectile>();
}

void Lobby::gameSystems(void)
{
    std::function<void(Id &i, Position &pos, Velocity &v, InputInfo &input, Clock &clock, Deleted &d)> MvmtFunc = MvmtSystems; // _registry.exec(MvmtSystems)
    std::function<void(Id &id, Position &pos, Velocity &v, Damage &damage, Deleted &d, Projectile &p)> MvmtFuncBullets = MvmtSystemsBullets;
    std::function<void(Id &i, Position &pos, Velocity &Velocity, Damage &damage, Clock &clock, Deleted &d)> MvmtFuncMonsters = MvmtSystemsMonsters;
    // std::function<void(Position &p)> PlayerFireFunc = PlayerFireSimpleProjectile; 
    std::function<void(Id &i, Damage &d, Position &pos, Collider &col, SpriteFrame &sf)> CollisionFunc = CollisionSystems;

    if (_clock->canUpdate(0.05, _refreshMvmt)) {
        _registry.Exec(MvmtFunc);
        _registry.Exec(MvmtFuncBullets);
        _registry.Exec(MvmtFuncMonsters);
        _registry.Exec(CollisionFunc);
    }
    if (_clock->canUpdate(3, _refreshSpawnRate)) {
        MonsterSpawn();
        this->score += 1;
        std::cout << "score = " << score << std::endl;
    }
}

Lobby::ClientInLobby::ClientInLobby(Registry& registry) : _registry(registry)
{

}

bool Lobby::isPlayer(binaryMsgServer message)
{
    if (message.entityInfo.id != 1 || message.entityInfo.id != 2 || message.entityInfo.id != 3 || message.entityInfo.id != 4)
        return false;
    return true;
}

/**
 * @brief Send one entity informations to one of the connected client
 *
 * @param idx, idx of client to send the entity
 * @param id_entity, idx of entity
 */ 

void Lobby::sendInfoGame(int idx, int id_entity)
{
    binaryMsgServer message = getFilledMsg(0, "GAME", id_entity);
    std::array<char, sizeof(binaryMsgServer)> messageBuffer;
    std::memcpy(messageBuffer.data(), &message, sizeof(binaryMsgServer));

    if (message.entityInfo.id != idx)
        message.entityInfo.hp = -1;
    std::shared_ptr<asio::ip::tcp::socket> temp_socket = _listClient[idx].getSocket();
    if (temp_socket->is_open()) {
        asio::async_write(*temp_socket, asio::buffer(messageBuffer), [this, idx, id_entity, message](const asio::error_code& error, std::size_t bytes_transferred) {
            if (message.entityInfo.deleted == 1 && isPlayer(message)) {
                Deleted &temp = _registry.getComponents<Deleted>()[id_entity];
                _registry.killEntity(id_entity);
            }
            if (error || bytes_transferred <= 0) {
                std::vector<std::string> temp;
                std::cerr << "Send error: " << error.message() << std::endl;
                handle_quit(_listClient[idx].getSocket(), std::ref(temp), findClient(_listClient[idx].getSocket()));
            }
        });
    }
}

/**
 * @brief Send all entities informations to one of the connected client
 * 
 * @param idx, idx of client to send the entity
 */ 

void Lobby::sendInfoGameLoop(int idx)
{
    int nbEntities = _registry.getNbEntities();

    for (size_t entityId : _registry.getEntities()) {
        sendInfoGame(idx, entityId);
    }
}

/**
 * @brief this function will receive the data from the client
 * 
 */

void Lobby::startSendLoop()
{
    _timer.expires_after(std::chrono::milliseconds(50));

    auto sendAuto = [this](const asio::error_code& error) {
        if (!error) {
            for (int i = 0; i < MAX_PLAYER; i++) {
                if (_listClient[i].getId() > 0) {
                    sendInfoGameLoop(i);
                }
            }
            gameSystems();
            if (checkEnd() == -1) {
                callLoose();
                std::this_thread::sleep_for(std::chrono::seconds(8));
                exit(0);
            }
            if (checkEnd() == 1) {
                callWin();
                std::this_thread::sleep_for(std::chrono::seconds(8));
                exit(0);
            }
            startSendLoop();
        }
    };
    _timer.async_wait(sendAuto);
}

/**
 * @brief Receive information from clients
 * 
 */

void Lobby::startAsyncReceive(void)
{
    std::shared_ptr<asio::ip::tcp::socket> client_socket = std::make_shared<asio::ip::tcp::socket>(_context);

    _acceptor.async_accept(*client_socket, [this, client_socket](const asio::error_code& error) {
        if (error) {
            std::cerr << "accept error: " << error.message() << std::endl;
        }
        else {
            handle_accept(client_socket);
        }
        startAsyncReceive();
    });
}

Lobby::~Lobby()
{
}

/**
 * @brief call this function if more than MAX_PLAYER Ids trys to connect to the server
 * 
 */

void Lobby::sendTooManyPlayer(std::shared_ptr<asio::ip::tcp::socket> client_socket)
{
    binaryMsgServer message = getFilledMsg(1, "ERROR 4 Player already connected", 0);
    std::array<char, sizeof(binaryMsgServer)> messageBuffer;
    std::memcpy(messageBuffer.data(), &message, sizeof(binaryMsgServer));
    asio::async_write(*client_socket, asio::buffer(messageBuffer), [](const asio::error_code& error, std::size_t bytes_transferred) {
        if (error || bytes_transferred <= 0) {
            std::cerr << "Send error: " << error.message() << std::endl;
            return;
        }
    });
}

/**
 * @brief call this function if Id trying to connect is already connected
 * 
 */

void Lobby::sendAlreadyConnected(int clientId)
{
    binaryMsgServer message = getFilledMsg(1, "ERROR Id already connected", 0);
    std::array<char, sizeof(binaryMsgServer)> messageBuffer;
    std::memcpy(messageBuffer.data(), &message, sizeof(binaryMsgServer));
    std::shared_ptr<asio::ip::tcp::socket> client_socket = _listClient[clientId].getSocket();
    asio::async_write(*client_socket, asio::buffer(messageBuffer), [](const asio::error_code& error, std::size_t bytes_transferred) {
        if (error || bytes_transferred <= 0) {
            std::cerr << "Send error: " << error.message() << std::endl;
            return;
        }
    });
}

void Lobby::sendNewConnection(std::shared_ptr<asio::ip::tcp::socket> client_socket, int clientId, int i)
{
    binaryMsgServer message = getFilledMsg(0, "Client connected to the server : " + std::string(_listClient[i].getName()), 0);
    std::array<char, sizeof(binaryMsgServer)> messageBuffer;
    std::memcpy(messageBuffer.data(), &message, sizeof(binaryMsgServer));
    std::shared_ptr<asio::ip::tcp::socket> socket;
    for (int j = 0; j < MAX_PLAYER; j++) {
        if (i == j || _listClient[j].getId() == 0)
            continue;
        socket = _listClient[j].getSocket();
        asio::async_write(*socket, asio::buffer(messageBuffer), [this](const asio::error_code& error, std::size_t bytes_transferred) {
            if (error || bytes_transferred <= 0) {
                std::cerr << "Send error: " << error.message() << std::endl;
                return;
            }
        });
    }
}

/**
 * @brief this contion calls a new connection to the server and add it in the list of Ids
 * 
 * @param client
 */

void Lobby::connectToLobby(std::shared_ptr<asio::ip::tcp::socket> client_socket, int clientId)
{
    int i = 0;

    for (i = 0; i < MAX_PLAYER; i++) {
        std::shared_ptr<asio::ip::tcp::socket> temp_socket = _listClient[i].getSocket();
        if (temp_socket == nullptr)
            continue;
    }
    if (_nbPlayer >= MAX_PLAYER) {
        sendTooManyPlayer(client_socket);
        return;
    }
    for (i = 0; i < MAX_PLAYER; i++) {
        if (_listClient[i].getId() == 0) {
            _listClient[i].setSocket(client_socket);
            client_socket = _listClient[i].getSocket();
            _listClient[i].setId(i + 1);
            break;
        }
    } _nbPlayer += 1;
    std::array<char, sizeof(binaryMsgServer)> messageBuffer;
    binaryMsgServer message = getFilledMsg(0, "CONNECTED " + std::to_string(_listClient[i].getId()), 0);
    std::memcpy(messageBuffer.data(), &message, sizeof(binaryMsgServer));
    std::shared_ptr<asio::ip::tcp::socket> socket = _listClient[i].getSocket();
    asio::async_write(*socket, asio::buffer(messageBuffer), [this](const asio::error_code& error, std::size_t bytes_transferred) {
        if (error || bytes_transferred <= 0) {
            std::cerr << "Send error: " << error.message() << std::endl;
            return;
        }
    });
    clientId = findClient(client_socket);
    sendNewConnection(client_socket, clientId, i);
}

/**
 * @brief use the command that he received and find the right function
 * 
 */

void Lobby::findFunc(int clientId, std::shared_ptr<asio::ip::tcp::socket> client_socket)
{
    std::string cmd(_listClient[clientId].getRecvMsg().cmd);
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
                _functionList[i](client_socket, std::ref(list_cmd), clientId);
                return;
            }
        }
        if (_functionListStr[i].compare(list_cmd[0]) == 0) {
            list_cmd.erase(list_cmd.begin());
            _functionList[i](client_socket, std::ref(list_cmd), clientId);
            return;
        }
    }
    std::cout << "unknown command, " << cmd << ", received from : " << client_socket << std::endl;
    std::array<char, sizeof(binaryMsgServer)> messageBuffer;
    binaryMsgServer message = getFilledMsg(-1, "ERROR: unknown command", 0);
    std::memcpy(messageBuffer.data(), &message, sizeof(binaryMsgServer));
    asio::async_write(*client_socket, asio::buffer(messageBuffer), [this](const asio::error_code& error, std::size_t bytes_transferred) {
        if (error || bytes_transferred <= 0) {
            std::cerr << "Send error: " << error.message() << std::endl;
            return;
        }
    });
}

/**
 * @brief write buffer
 * 
 * @param bytes_received size of the message
 */

binaryMsgServer Lobby::getFilledMsg(int error, std::string cmd, int idx)
{
    binaryMsgServer message;

    message.errorCode = error;
    strcpy(message.cmd, cmd.c_str());
    message.entityInfo.id = _registry.getComponents<Id>()[idx]._Id;
    message.entityInfo.x = _registry.getComponents<Position>()[idx]._x;
    message.entityInfo.y = _registry.getComponents<Position>()[idx]._y;
    message.entityInfo.spriteType = _registry.getComponents<SpriteFrame>()[idx]._spriteFrame;
    message.entityInfo.hp = _registry.getComponents<Health>()[idx]._Health;
    message.entityInfo.velocity_x = _registry.getComponents<Velocity>()[idx]._xv;
    message.entityInfo.velocity_y = _registry.getComponents<Velocity>()[idx]._yv;
    message.entityInfo.deleted = _registry.getComponents<Deleted>()[idx]._Deleted;
    return message;
}

void Lobby::ClientInLobby::setId(int id)
{
    std::cout << "setId: " << id << std::endl;
    Id &p = _registry.getComponents<Id>()[_idEntity];
    p._Id = id;
}

int Lobby::ClientInLobby::getId()
{
    return _registry.getComponents<Id>()[_idEntity]._Id;
}

void Lobby::ClientInLobby::setDeleted(int deleted)
{
    Deleted &d = _registry.getComponents<Deleted>()[_idEntity];
    d._Deleted = deleted;
}

int Lobby::ClientInLobby::getDeleted()
{
    return _registry.getComponents<Deleted>()[_idEntity]._Deleted;
}

void Lobby::ClientInLobby::setX(int x)
{
    Position &pos = _registry.getComponents<Position>()[_idEntity];
    pos._x = x;
}

int Lobby::ClientInLobby::getX()
{
    return _registry.getComponents<Position>()[_idEntity]._x;
}

void Lobby::ClientInLobby::setY(int y)
{
    Position &pos = _registry.getComponents<Position>()[_idEntity];
    pos._y = y;
}

int Lobby::ClientInLobby::getY()
{
    return _registry.getComponents<Position>()[_idEntity]._y;
}

void Lobby::ClientInLobby::setName(char *name)
{
    _registry.emplaceComponent<Name>(_idEntity, name);
}

char *Lobby::ClientInLobby::getName()
{
    const char *str = _registry.getComponents<Name>()[_idEntity]._name.c_str();
    char* mutableStr = strdup(str);
    return mutableStr;
}

void Lobby::ClientInLobby::setSpriteFrame(int spriteFrame)
{
    SpriteFrame &sf = _registry.getComponents<SpriteFrame>()[_idEntity];
    sf._spriteFrame = spriteFrame;
}

int Lobby::ClientInLobby::getSpriteFrame()
{
    return _registry.getComponents<SpriteFrame>()[_idEntity]._spriteFrame;
}

void Lobby::ClientInLobby::setHp(int hp)
{
    Health &h = _registry.getComponents<Health>()[_idEntity];
    h._Health = hp;
}

int Lobby::ClientInLobby::getHp()
{
    return _registry.getComponents<Health>()[_idEntity]._Health;
}

void Lobby::ClientInLobby::setRecvMsg(binaryMsgClient recvdMsg)
{
    _recvdMsg = recvdMsg;
}

binaryMsgClient Lobby::ClientInLobby::getRecvMsg()
{
    return _recvdMsg;
}

size_t Lobby::ClientInLobby::getIdEntity()
{
    return _idEntity;
}

int Lobby::ClientInLobby::getVX()
{
    return _registry.getComponents<Velocity>()[_idEntity]._xv;
}

int Lobby::ClientInLobby::getVY()
{
    return _registry.getComponents<Velocity>()[_idEntity]._yv;
}

int Lobby::findClient(std::shared_ptr<asio::ip::tcp::socket> client_socket)
{
    for (int i = 0; i < MAX_PLAYER; i++) {
        if (_listClient[i].getSocket() == nullptr)
            continue;
        if (client_socket == _listClient[i].getSocket())
            return i;
    }
    return -1;
}

std::shared_ptr<asio::ip::tcp::socket> Lobby::ClientInLobby::getSocket()
{
    return _client_socket;
}

void Lobby::ClientInLobby::setSocket(std::shared_ptr<asio::ip::tcp::socket> socket)
{
    _client_socket = std::move(socket);
}

void Lobby::handle_accept(std::shared_ptr<asio::ip::tcp::socket> client_socket)
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
    connectToLobby(client_socket, 0);
    handle_read(client_socket);
}

void Lobby::handle_read_next(std::shared_ptr<asio::ip::tcp::socket> client_socket, std::array<char, sizeof(binaryMsgClient)> recvBuffer, std::size_t bytes_read)
{
    binaryMsgClient recvMsg;
    if (bytes_read >= sizeof(binaryMsgClient)) {
        std::memcpy(&recvMsg, recvBuffer.data(), sizeof(binaryMsgClient));
//        std::cout << "Client sent : " << recvMsg.cmd << std::endl;
    } else {
        std::cerr << "ERROR: invalid read" << std::endl;
        return;
    }
    int clientId = findClient(client_socket);
    _listClient[clientId].setRecvMsg(std::ref(recvMsg));
    findFunc(clientId, client_socket);
    handle_read(client_socket);
}

void Lobby::handle_read(std::shared_ptr<asio::ip::tcp::socket> client_socket)
{
    std::array<char, sizeof(binaryMsgClient)> recvBuffer;

    asio::async_read(*client_socket, asio::buffer(recvBuffer), [this, client_socket, recvBuffer = std::ref(recvBuffer)](const asio::error_code& error, std::size_t bytes_read) {
        std::vector<std::string> temp;
        if (error == asio::error::eof || error == asio::error::connection_reset) {
            handle_quit(client_socket, temp, findClient(client_socket));
        } else if (error) {
            std::cerr << "ERROR while reading data: " << error.message() << std::endl;
            handle_read(client_socket);
            return;
        } else {
            handle_read_next(client_socket, recvBuffer, bytes_read);
        }
    });
}

/**
 * @brief Quit and remove informations from client
 * 
 * @param client_socket, socket of the client quitting
 */

void Lobby::handle_quit(std::shared_ptr<asio::ip::tcp::socket> client_socket, std::vector<std::string> list_cmd, int clientId)
{
    std::cout << "Client in lobby << " << _port << " disconnected " << _listClient[clientId].getId() << std::endl;
    _listClient[clientId].setId(0);
    _listClient[clientId].setDeleted(-1);
    _nbPlayer--;
}

/**
 * @brief wait for client connection (the server doesn't stop for a connection)
 * 
 */

void Lobby::waitForClient(void)
{
    asio::io_service::work work(_context);
    _context.run();
}

void Lobby::handleInput(std::shared_ptr<asio::ip::tcp::socket> client_socket, std::vector<std::string> list_cmd, int clientId)
{
    binaryMsgClient recvMsg = _listClient[clientId].getRecvMsg();
    InputInfo &input = _registry.getComponents<InputInfo>()[_listClient[clientId].getIdEntity()];

    input._up = recvMsg._input.up;
    input._down = recvMsg._input.down;
    input._right = recvMsg._input.right;
    input._left = recvMsg._input.left;
}

void Lobby::callLoose()
{
    binaryMsgServer message = getFilledMsg(0, "LOSE", 0);
    std::array<char, sizeof(binaryMsgServer)> messageBuffer;
    std::memcpy(messageBuffer.data(), &message, sizeof(binaryMsgServer));
    std::shared_ptr<asio::ip::tcp::socket> socket;
    for (int j = 0; j < MAX_PLAYER; j++) {
        socket = _listClient[j].getSocket();
        asio::async_write(*socket, asio::buffer(messageBuffer), [this](const asio::error_code& error, std::size_t bytes_transferred) {
            if (error || bytes_transferred <= 0) {
                std::cerr << "Send error: " << error.message() << std::endl;
                return;
            }
        });
    }
}

void Lobby::callWin()
{
    binaryMsgServer message = getFilledMsg(0, "WIN", 0);
    std::array<char, sizeof(binaryMsgServer)> messageBuffer;
    std::memcpy(messageBuffer.data(), &message, sizeof(binaryMsgServer));
    std::shared_ptr<asio::ip::tcp::socket> socket;
    for (int j = 0; j < MAX_PLAYER; j++) {
        socket = _listClient[j].getSocket();
        asio::async_write(*socket, asio::buffer(messageBuffer), [this](const asio::error_code& error, std::size_t bytes_transferred) {
            if (error || bytes_transferred <= 0) {
                std::cerr << "Send error: " << error.message() << std::endl;
                return;
            }
        });
    }
}

int Lobby::checkEnd()
{
    Registry &registry = Registry::getCurrentRegitry();
    
    SparseArray<Id> &id = registry.getComponents<Id>();
    SparseArray<Collider> &colliders = registry.getComponents<Collider>();
    SparseArray<Position> &positions = registry.getComponents<Position>();
    SparseArray<Health> &health = registry.getComponents<Health>();
    SparseArray<SpriteFrame> &spriteFrame = registry.getComponents<SpriteFrame>();
    SparseArray<Deleted> &deleted = registry.getComponents<Deleted>();

    bool allPlayersDead = true;
    int count = 0;

    if (this->score >= 42) {
        std::cout << "GAME WIN" << std::endl;
        return 1;
    }
    for (int entityId = 0; entityId <= 3; entityId++) {
        Deleted &entityDeleted = deleted[entityId];
        if (entityDeleted._Deleted == -1)
            count += 1;
        if (count == 4)
            return 0;
    }
    for (int entityId = 0; entityId <= 3; entityId++) {
        Deleted &entityDeleted = deleted[entityId];
        if (entityDeleted._Deleted == 0) {
            std::cout << "ENTITY ID ALIVE " << entityDeleted._Deleted << std::endl;
            return 0;
        }
        else
            std::cout << "ENTITY ID DELETED " << entityDeleted._Deleted << std::endl;
    }
    if (allPlayersDead == true) {
        std::cout << "GAME OVER" << std::endl;
        return -1;
    }
    return 0;
}
