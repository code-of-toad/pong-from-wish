cmake_minimum_required(VERSION 3.28)
project(pong-from-wish)

set(CMAKE_CXX_STANDARD 17)

add_executable(pong-from-wish
        Main.cpp
        Paddle.cpp
        Paddle.hpp
        Ball.cpp
        Ball.hpp
)

############# SFML #############
set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR C:/SFML-2.6.1/lib/cmake/SFML)
find_package(SFML COMPONENTS REQUIRED
        system
        window
        graphics
        audio
        network
)
target_link_libraries(pong-from-wish
        sfml-system
        sfml-window
        sfml-graphics
        sfml-audio
        sfml-network
)
################################