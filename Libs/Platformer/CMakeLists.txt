cmake_minimum_required(VERSION 3.13)
project(Platformer)

set(SOURCES
    Sources/main.cpp

    Sources/Broadcast.cpp
    Sources/Game.cpp
    Sources/Map.cpp
    Sources/Menu.cpp
    Sources/Player.cpp
    Sources/Options.cpp
    Sources/Systems/CollisionSystem.cpp
    Sources/Systems/MvmtSystem.cpp
    Sources/Systems/SpriteFrameSystem.cpp
)

set(HEADERS
    Headers/Components/Health.hpp
    Headers/Components/Name.hpp
    Headers/Components/Id.hpp
    Headers/Components/Position.hpp
    Headers/Components/SpriteFrame.hpp
    Headers/Components/Velocity.hpp
    Headers/Components/Collider.hpp
    Headers/Components/Damage.hpp
    Headers/Components/Input.hpp
    Headers/Components/Clock.hpp
    Headers/Components/Color.hpp
    Headers/Components/returnValue.hpp
    Headers/Components/Text.hpp
    Headers/Components/Clickable.hpp
    Headers/Components/RectangleShape.hpp
    Headers/Broadcast.hpp
    Headers/Game.hpp
    Headers/Map.hpp
    Headers/Menu.hpp
    Headers/Options.hpp
    Headers/Player.hpp
    Headers/Systems.hpp
    )

add_executable(Platformergame ${SOURCES} ${HEADERS})
target_link_libraries(Platformergame PRIVATE sfml-graphics sfml-window sfml-system)
target_link_libraries(Platformergame PRIVATE ECSlib)
target_include_directories(Platformergame PRIVATE Headers)
target_include_directories(Platformergame PRIVATE Headers/Systems)
target_include_directories(Platformergame PRIVATE Headers/Components)