cmake_minimum_required(VERSION 3.13)
project(Client)

find_package(SFML 2.5.1 QUIET COMPONENTS graphics window system)
set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} ${CMAKE_BINARY_DIR}/_deps/asio-src/asio/include/asio.hpp)

if(NOT SFML_FOUND)
    include(FetchContent)

    FetchContent_Declare(
        sfml
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.5.1
    )

    FetchContent_MakeAvailable(sfml)
    message(STATUS "Add libsfml")
endif()

find_package(Asio 1.28.1 QUIET)

if(NOT Asio_FOUND)
    message(STATUS "add asio")

    include(FetchContent)

    FetchContent_Declare(
        asio
        GIT_REPOSITORY https://github.com/chriskohlhoff/asio.git
        GIT_TAG asio-1-28-1
    )

    FetchContent_MakeAvailable(asio)
endif()

set(SOURCES
    Sources/Client.cpp
    Sources/Lobby.cpp
    Sources/Game.cpp
    Sources/main.cpp
    Sources/Clock.cpp
    Sources/GraphicSystems/GraphicSystem.cpp
    Sources/GraphicSystems/SFML/Text.cpp
    Sources/GraphicSystems/SFML/Sprite.cpp
    Sources/GraphicSystems/SFML/SfmlSystem.cpp
)

set(HEADERS
    Headers/Client.hpp
    Headers/Lobby.hpp
    Headers/Components.hpp
    Headers/Game.hpp
    Headers/Clock.hpp
    Headers/Entity.hpp
    Headers/GameProperties.hpp
    Headers/KeysDetection/KeysCode.hpp
    Headers/GraphicSystems/SpritesProperties.hpp
    Headers/GraphicSystems/GraphicSystem.hpp
    Headers/GraphicSystems/Anchor.hpp
    Headers/GraphicSystems/GraphicComponents.hpp
    Headers/GraphicSystems/SFML/Text.hpp
    Headers/GraphicSystems/SFML/Sprite.hpp
    Headers/GraphicSystems/SFML/SfmlSystem.hpp
)

IF (WIN32)
    message(STATUS "Init WIND32 Client")
    add_executable(Client WIN32 ${SOURCES} ${HEADERS})
ELSEIF (UNIX AND NOT MINGW)
    message(STATUS "Init UNIX Client")
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g3")
    add_executable(Client ${SOURCES} ${HEADERS})
ENDIF()

target_include_directories(Client PRIVATE Headers)
target_include_directories(Client PRIVATE Headers/GraphicSystems)
target_include_directories(Client PRIVATE Headers/GraphicSystems/SFML)
target_include_directories(Client PRIVATE Headers/KeysDetection)
target_include_directories(Client PRIVATE ${CMAKE_BINARY_DIR}/_deps/asio-src/asio/include)
target_link_libraries(Client PRIVATE sfml-graphics sfml-window sfml-system)
target_link_libraries(Client PRIVATE ECSlib)

