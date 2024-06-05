#include <iostream>
#include <SFML/Graphics.hpp>
#include "GameState.hpp"
#include "Paddle.hpp"
#include "Ball.hpp"

#define SCREEN_W 1280
#define SCREEN_H 720

int main() {
    sf::RenderWindow window(sf::VideoMode(SCREEN_W, SCREEN_H), "Pong From Wish",
                            sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(60);

    Paddle paddleLeft(LEFT, window);
    Paddle paddleRight(RIGHT, window);

    sf::Clock clock;
    while (window.isOpen()) {
        // EVENT HANDLER
        // -------------
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                window.close();
            }
        }
        // INPUT HANDLER
        // -------------
        float dt = clock.restart().asSeconds();
        // float dt = 1.f;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            paddleLeft.moveUp(dt);
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            paddleLeft.moveDown(dt);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            paddleRight.moveUp(dt);
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            paddleRight.moveDown(dt);
        }

        window.clear();

        paddleLeft.draw(window);
        paddleRight.draw(window);

        window.display();
    }

    return EXIT_SUCCESS;
}