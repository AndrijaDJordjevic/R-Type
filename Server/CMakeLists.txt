cmake_minimum_required(VERSION 3.13)
project(Server)

set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} ${CMAKE_BINARY_DIR}/_deps/asio-src/asio/include/asio.hpp)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

find_package(Asio 1.28.1 QUIET)

if(NOT Asio_FOUND)
    message(STATUS "Asio not found, using FetchContent")

    include(FetchContent)

    FetchContent_Declare(
        asio
        GIT_REPOSITORY https://github.com/chriskohlhoff/asio.git
        GIT_TAG asio-1-28-1
    )

    FetchContent_MakeAvailable(asio)
endif()

set(SOURCES
    Sources/CheckArgs.cpp
    Sources/Server.cpp
    Sources/Clock.cpp
    Sources/Lobby.cpp
    Sources/Systems/MvmtSystem.cpp
    Sources/Systems/MvmtSystemBullets.cpp
    Sources/Systems/MvmtSystemMonsters.cpp
    Sources/Systems/CollisionSystem.cpp
    Sources/Systems/FireSystem.cpp
    Sources/Systems/LoseCondition.cpp

    main.cpp
)

set(HEADERS
    Headers/Server.hpp
    Headers/Lobby.hpp
    Headers/Systems.hpp

    Headers/Components/Health.hpp
    Headers/Components/Name.hpp
    Headers/Components/Id.hpp
    Headers/Components/Position.hpp
    Headers/Components/SpriteFrame.hpp
    Headers/Components/Velocity.hpp
    Headers/Components/Collider.hpp
    Headers/Components/Damage.hpp
    Headers/Components/InputInfo.hpp
    Headers/Components/Clock.hpp
    Headers/Components/Deleted.hpp
    Headers/Components/Projectile.hpp
)

IF (WIN32)
    message(STATUS "Init WIND32 server")
    add_executable(Server WIN32 ${SOURCES} ${HEADERS})
ELSEIF (UNIX AND NOT MINGW)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
    message(STATUS "Init UNIX server")
    add_executable(Server ${SOURCES} ${HEADERS})
ENDIF()

target_include_directories(Server PRIVATE Headers)
target_include_directories(Server PRIVATE ${CMAKE_BINARY_DIR}/_deps/asio-src/asio/include)
target_link_libraries(Server PRIVATE ECSlib)

