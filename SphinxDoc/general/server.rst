.. _server:

Server
======

Introduction
------------

What is the server doing?

The server will create lobbies for the clients that try to connect with a port.
The exchange between the client and the server will be with a binary structure exchange.
When the server receives a command to create a new lobby with the port, the server will create it.
If the port is free to use, the server opens the port where the client can connect to.
If the port is already used, the server sends a command to the client informing them that the port is already in use.
The client can then decide if they want to connect to the port already in use or create a new one.
If the port is unavailable, the server will inform the client that the port is unusable.

.. _protocol:

The Asio Library
^^^^^^^^^^^^^^^^

Asio is a cross-platform C++ library for network and low-level I/O programming that provides developers with a consistent asynchronous model using a modern C++ approach.
The server uses the Asio library to enable smooth interaction with the client, where the server can send and receive commands without blocking.

Protocol
^^^^^^^^

The exchange between the client and the server is made using specific structures.

The struct that the server sends to the client is:

.. code-block:: c++

    struct binaryMsgServer {
        int64_t errorCode;
        s_entity entityInfo;
        char cmd[1024];
    }

The struct that the client sends to the server is:

.. code-block:: c++

    struct binaryMsgClient {
        int64_t errorCode;
        Inputs input;
        char cmd[1024];
    }

(More information can be found in the RFC.md)

Commands send
^^^^^^^^^^^^^

Reception

NEW
---
The server will send the "NEW" command when a client wants to connect to a lobby by sending "NEW port," where "port" is provided as a parameter.
The server will check if the port where the client tries to connect is available. If it is, the server will open it, and the client can then connect to the server using the new port.

CONNECTED
---------
The server will send the "CONNECTED" command to the client when the client tries to connect to an already used port.
The client can still join the game on this port.

ERROR
-----
This command is sent when the port chosen by the client is not available.

ACCEPT
------
The server sends the "ACCEPT" command when the client trying to connect is accepted.

GAME
----
This command is sent when the client is in a lobby. It provides the client with information about the "s_entity" structure mentioned earlier in "binaryMsgServer".

Commands Reception
^^^^^^^^^^^^^^^^^^

NEW
---
Send the "NEW" command with a port as argument, the receive the "NEW" command from the server.

INPUT
-----
The server will receive the input informations from the client by receiving the "INPUT" command.
The input informations are provided to the serverwith information about the "Inputs" structure mentioned earlier in "binaryMsgClient".