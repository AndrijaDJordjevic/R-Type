# Documentation of the Protocole Client-Server

This document describe the protocole of communication between the client and the server in the game R-Type.

## Data Structures

### Binary message of the Server (`binaryMsgServer`)

Structure that the server sends to the client, providing information about all entities.

| Champ         | Bytes     | Description                 |
|---------------|-----------|-----------------------------|
| errorCode     | 64        | Error Code                  |
| entityInfo    | s_entity  | List entity                 |
| cmd           | 1024      | Command sended              |

#### Entity Structures (`s_entity`)

| Field         | Bytes  | Description                 |
|---------------|--------|-----------------------------|
| id            | 8      | Identity of the entity      |
| x             | 8      | X coordinate of the entity |
| y             | 8      | X coordinate of the entity |
| name          | 1024   | Name of the entity          |
| spriteFrame   | 8      | Sprite of the entity        |
| hp            | 8      | Health bare of the entity   |

### Binary Message of the Client (`binaryMsgClient`)

Structure that the client sends to the server, specifying the actions of the client.

| Field         | Bytes     | Description                  |
|---------------|-----------|------------------------------|
| errorCode     | 64        | Error Code                   |
| input         | Inputs    | Inputs of the client         |
| cmd           | 1024      | Command sended               |

#### `Inputs`

| Field   | Bytes | Description   |
|---------|-------|---------------|
| left    | bool  | Left Input    |
| right   | bool  | Right Input   |
| up      | bool  | Up Input      |
| down    | bool  | Down Input    |
