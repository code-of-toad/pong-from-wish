#include <iostream>
#include <SFML/Graphics.hpp>
#include "Paddle.hpp"
#include "Ball.hpp"
#include "GameState.hpp"

#define SCREEN_W 1280
#define SCREEN_H 720

#define MAX_SCORE 10

int main() {
    sf::RenderWindow window(sf::VideoMode(SCREEN_W, SCREEN_H), "Pong From Wish",
                            sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(60);

    sf::ContextSettings settings;
    settings.antialiasingLevel = 0;

    Paddle paddleLeft(LEFT, window);
    Paddle paddleRight(RIGHT, window);
    Ball ball(window);

    GameState gameState = START;

    gameState = START;  // DEBUGGGGGGGGGGGGGGGGGGGGGGGGGG

    sf::Clock clock;
    while (window.isOpen()) {
        if (gameState == START) {
            // EVENT HANDLER
            // -------------
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                    window.close();
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
                    gameState = SERVE;
            }
            clock.restart();

            window.clear();


            window.display();
        }
        else if (gameState == SERVE) {
            // EVENT HANDLER
            // -------------
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                    window.close();
            }

            if (paddleLeft.isLoser())
                ball.setDirection(LEFT);
            else if (paddleRight.isLoser())
                ball.setDirection(RIGHT);

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
                gameState = PLAY;

            clock.restart();

            window.clear();

            paddleLeft.draw(window);
            paddleRight.draw(window);
            ball.draw(window);

            window.display();
        }
        else if (gameState == PLAY) {
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
            // GAME LOGIC + UPDATE
            // -------------------
            ball.move(dt);

            if (!ball.collides(paddleLeft))
                ball.collides(paddleRight);

            if (ball.getRect().getGlobalBounds().left <= 0) {
                paddleLeft.setLoser();
                paddleRight.setLoser(false);
                ball.reset(window);
                if (paddleLeft.scoreUp() == MAX_SCORE) {
                    paddleLeft.reset(window);
                    paddleRight.reset(window);
                    window.clear();
                    gameState = DONE;
                } else {
                    gameState = SERVE;
                }

                std::cout << "Player 2 SCORES: " << std::endl;
                std::cout << "    p1: " << paddleLeft.getScore() << std::endl;
                std::cout << "    p2: " << paddleRight.getScore() << std::endl;
            } else if (ball.getRect().getGlobalBounds().left + ball.getRect().getGlobalBounds().width
                           >= window.getSize().x) {
                paddleLeft.setLoser(false);
                paddleRight.setLoser();
                ball.reset(window);
                if (paddleRight.scoreUp() == MAX_SCORE) {
                    paddleRight.reset(window);
                    paddleLeft.reset(window);
                    window.clear();
                    gameState = DONE;
                } else {
                    gameState = SERVE;
                }

                std::cout << "Player 1 SCORES: " << std::endl;
                std::cout << "    p1: " << paddleLeft.getScore() << std::endl;
                std::cout << "    p2: " << paddleRight.getScore() << std::endl;
            }

            // RENDER
            // ------
            window.clear();

            paddleLeft.draw(window);
            paddleRight.draw(window);
            ball.draw(window);

            window.display();
        }
        else if (gameState == DONE) {
            // EVENT HANDLER
            // -------------
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                    window.close();
                }
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
                gameState = SERVE;

            window.clear();



            window.display();
        }
    }

    return EXIT_SUCCESS;
}