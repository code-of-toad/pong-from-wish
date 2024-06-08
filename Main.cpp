#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
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
    // AUDIO
    sf::SoundBuffer bufferPaddleHit;
    if (!bufferPaddleHit.loadFromFile("./resources/sounds/paddle_hit.wav")) {
        std::cerr << "Failed to load sound effect `paddle_hit.wav`" << std::endl;
        return EXIT_FAILURE;
    }
    sf::Sound soundPaddleHit;
    soundPaddleHit.setBuffer(bufferPaddleHit);

    sf::SoundBuffer bufferScore;
    if (!bufferScore.loadFromFile("./resources/sounds/score.wav")) {
        std::cerr << "Failed to load sound effect `score.wav`" << std::endl;
        return EXIT_FAILURE;
    }
    sf::Sound soundScore;
    soundScore.setBuffer(bufferScore);
    soundScore.setVolume(70);

    sf::SoundBuffer bufferWallHit;
    if (!bufferWallHit.loadFromFile("./resources/sounds/wall_hit.wav")) {
        std::cerr << "Failed to load sound effect `wall_hit.wav`" << std::endl;
        return EXIT_FAILURE;
    }
    sf::Sound soundWallHit;
    soundWallHit.setBuffer(bufferWallHit);

    // WINDOW
    sf::RenderWindow window(sf::VideoMode(SCREEN_W, SCREEN_H), "Pong From Wish",
                            sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);
    sf::RectangleShape virtualWindow(sf::Vector2f(SCREEN_W, SCREEN_H));
    virtualWindow.setFillColor(sf::Color(15, 15, 15));

    // SETTINGS
    sf::ContextSettings settings;
    // settings.antialiasingLevel = 0;

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

    sf::Text scoreTextLeft;
    scoreTextLeft.setFillColor(sf::Color(100, 100, 100, 100));
    initText(scoreTextLeft, mainFont, 125, sf::Text::Bold, MID_RIGHT);
    scoreTextLeft.setPosition(sf::Vector2f(window.getSize().x / 2 - 117, window.getSize().y / 2 - 85));

    sf::Text scoreTextRight;
    scoreTextRight.setFillColor(sf::Color(100, 100, 100, 100));
    initText(scoreTextRight, mainFont, 125, sf::Text::Bold, MID_LEFT);
    scoreTextRight.setPosition(sf::Vector2f(window.getSize().x / 2 + 53, window.getSize().y / 2 - 85));

    sf::Text turnText;
    turnText.setFillColor(sf::Color(200, 200, 200, 200));
    initText(turnText, mainFont, 45, sf::Text::Bold, TOP_CENTER);
    turnText.setPosition(sf::Vector2f(window.getSize().x / 2 - 173, 30));

    sf::Text serveText;
    serveText.setString("Press SPACE to serve");
    serveText.setFillColor(sf::Color(100, 100, 100, 100));
    initText(serveText, mainFont, 25, sf::Text::Bold, TOP_CENTER);
    serveText.setPosition(sf::Vector2f(window.getSize().x / 2,window.getSize().y / 2 + 80));

    sf::Text gameoverText;
    gameoverText.setString("Player # Wins!");
    gameoverText.setFillColor(sf::Color(200, 200, 200, 200));
    initText(gameoverText, mainFont, 95, sf::Text::Bold, TOP_CENTER);
    gameoverText.setPosition(sf::Vector2f(window.getSize().x / 2 + 8,window.getSize().y / 2 - 135));

    sf::Text restartText;
    restartText.setString("ENTER: Restart     ESC: Exit Game");
    restartText.setFillColor(sf::Color(200, 200, 200, 200));
    initText(restartText, mainFont, 25, sf::Text::Bold, TOP_CENTER);
    restartText.setPosition(sf::Vector2f(window.getSize().x / 2,window.getSize().y / 2 + 80));

    // OBJECTS
    Paddle paddleLeft(LEFT, window);
    Paddle paddleRight(RIGHT, window);
    Ball ball(window);

    // GAME STATE
    GameState gameState = START;

    // MAIN LOOP
    sf::Clock clock;
    while (window.isOpen()) {
        if (gameState == START) {
            // EVENT HANDLER
            // -------------
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                    window.close();
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
                    soundScore.play();
                    gameState = SERVE;
                }
            }
            clock.restart();

            window.clear();

            window.draw(virtualWindow);
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

            scoreTextLeft.setString(std::to_string(paddleLeft.getScore()));
            scoreTextRight.setString(std::to_string(paddleRight.getScore()));

            ball.reset(window);

            if (paddleLeft.isLoser()) {
                ball.setDirection(LEFT);
                turnText.setString("Player 1 serve");
            } else if (paddleRight.isLoser()) {
                ball.setDirection(RIGHT);
                turnText.setString("Player 2 serve");
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
                gameState = PLAY;

            clock.restart();

            window.clear();

            window.draw(virtualWindow);
            window.draw(turnText);
            window.draw(serveText);
            window.draw(scoreTextLeft);
            window.draw(scoreTextRight);

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
            ball.move(dt, soundWallHit);

            if (ball.collides(paddleLeft) || ball.collides(paddleRight))
                soundPaddleHit.play();

            if (ball.getRect().getGlobalBounds().left <= 0) {
                soundScore.play();
                paddleLeft.setLoser();
                paddleRight.setLoser(false);
                if (paddleRight.scoreUp() == MAX_SCORE) {
                    gameoverText.setString("Player 2 wins!");
                    scoreTextLeft.setString(std::to_string(paddleLeft.getScore()));
                    scoreTextRight.setString(std::to_string(paddleRight.getScore()));
                    gameState = DONE;
                } else {
                    gameState = SERVE;
                }

                std::cout << "Player 2 SCORES: " << std::endl;
                std::cout << "    p1: " << paddleLeft.getScore() << std::endl;
                std::cout << "    p2: " << paddleRight.getScore() << std::endl;
            } else if (ball.getRect().getGlobalBounds().left + ball.getRect().getGlobalBounds().width
                           >= window.getSize().x) {
                soundScore.play();
                paddleLeft.setLoser(false);
                paddleRight.setLoser();
                if (paddleLeft.scoreUp() == MAX_SCORE) {
                    gameoverText.setString("Player 1 wins!");
                    scoreTextLeft.setString(std::to_string(paddleLeft.getScore()));
                    scoreTextRight.setString(std::to_string(paddleRight.getScore()));
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

            window.draw(virtualWindow);
            window.draw(scoreTextLeft);
            window.draw(scoreTextRight);

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
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
                paddleLeft.reset(window);
                scoreTextLeft.setString("0");

                paddleRight.reset(window);
                scoreTextRight.setString("0");

                gameState = SERVE;
            }

            window.clear();

            window.draw(virtualWindow);
            window.draw(scoreTextLeft);
            window.draw(scoreTextRight);
            window.draw(gameoverText);
            window.draw(restartText);
            paddleLeft.draw(window);
            paddleRight.draw(window);

            window.display();
        }
    }

    return EXIT_SUCCESS;
}