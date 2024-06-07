#include <iostream>
#include <SFML/Graphics.hpp>
#include "Paddle.hpp"
#include "Ball.hpp"
#include "GameState.hpp"

#define SCREEN_W 1280
#define SCREEN_H 720

#define MAX_SCORE 10

enum Position {
       TOP_LEFT,       TOP_CENTER,       TOP_RIGHT,
       MID_LEFT,       MID_CENTER,       MID_RIGHT,
    BOTTOM_LEFT,    BOTTOM_CENTER,    BOTTOM_RIGHT
};

void initText(sf::Text& text,
              const sf::Font& font,
              const int size,
              // const sf::Color color,
              const sf::Text::Style style,
              const Position origin) {
    text.setFont(font);
    text.setCharacterSize(size);
    // text.setFillColor(sf::Color(200, 200, 200, 200));
    text.setStyle(style);
    sf::FloatRect bounds = text.getLocalBounds();
    if (origin == TOP_CENTER) {
        text.setOrigin(bounds.left + bounds.width / 2, bounds.top);
    } else if (origin == MID_CENTER) {
        text.setOrigin(bounds.left + bounds.width / 2, bounds.top + bounds.height / 2);
    } else if (origin == BOTTOM_CENTER) {
        text.setOrigin(bounds.left + bounds.width / 2, bounds.top + bounds.height);
    } else if (origin == TOP_LEFT) {
        text.setOrigin(bounds.left, bounds.top);
    } else if (origin == MID_LEFT) {
        text.setOrigin(bounds.left, bounds.top + bounds.height / 2);
    } else if (origin == BOTTOM_LEFT) {
        text.setOrigin(bounds.left, bounds.top + bounds.height);
    } else if (origin == TOP_RIGHT) {
        text.setOrigin(bounds.left + bounds.width, bounds.top);
    } else if (origin == MID_RIGHT) {
        text.setOrigin(bounds.left + bounds.width, bounds.top + bounds.height / 2);
    } else if (origin == BOTTOM_RIGHT) {
        text.setOrigin(bounds.left + bounds.width, bounds.top + bounds.height);
    }
}

int main() {
    // WINDOW
    sf::RenderWindow window(sf::VideoMode(SCREEN_W, SCREEN_H), "Pong From Wish",
                            sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(60);
    // SETTINGS
    sf::ContextSettings settings;
    settings.antialiasingLevel = 0;
    // FONT
    sf::Font mainFont;
    if (!mainFont.loadFromFile("./resources/fonts/font.ttf")) {
        return EXIT_FAILURE;
    }
    // TEXT
    sf::Text titleText;
    titleText.setString("Pong From Wish");
    titleText.setOutlineThickness(2);
    titleText.setOutlineColor(sf::Color(200, 200, 200, 100));
    titleText.setFillColor(sf::Color(200, 200, 200, 200));
    initText(titleText, mainFont, 90, sf::Text::Bold, MID_CENTER);
    titleText.setPosition(sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2 - 35));

    sf::Text instrxnText;
    instrxnText.setString("Press ENTER");
    instrxnText.setFillColor(sf::Color(200, 200, 200, 200));
    initText(instrxnText, mainFont, 25, sf::Text::Bold, TOP_CENTER);
    instrxnText.setPosition(sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2 + 20));
    // OBJECTS
    Paddle paddleLeft(LEFT, window);
    Paddle paddleRight(RIGHT, window);
    Ball ball(window);
    // GAME STATE
    GameState gameState = START;
    // CLOCK
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

            window.draw(titleText);
            window.draw(instrxnText);

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