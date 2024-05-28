#include <SFML/Graphics.hpp>
// #include "GLOBALS.hpp"


#define SCREEN_W 1000
#define SCREEN_H 600

#define PADDLE_W 20
#define PADDLE_H 120

#define PONG_SIZE 20

void movementAI(sf::Vector2f& playerPos, float& playerVel) {
            if (playerPos.y < 5 || playerPos.y + PADDLE_H > SCREEN_H - 5)
                playerVel *= -1;
            playerPos.y += playerVel;
}

int main() {
    sf::RenderWindow window(sf::VideoMode(SCREEN_W, SCREEN_H), "Pong From Wish");

    // PLAYER 1 (User)
    sf::RectangleShape p1;
    sf::Vector2f p1Pos(5.f, SCREEN_H / 2.f - PADDLE_H / 2.f);
    p1.setPosition(p1Pos);
    p1.setSize(sf::Vector2f(PADDLE_W, PADDLE_H));
    p1.setFillColor(sf::Color::White);
    float p1Vel = 4.f;

    // PLAYER 2 (A.I.)
    sf::RectangleShape p2;
    sf::Vector2f p2Pos(SCREEN_W - (PADDLE_W + 5.f), SCREEN_H / 2.f - PADDLE_H / 2.f);
    p2.setPosition(p2Pos);
    p2.setSize(sf::Vector2f(PADDLE_W, PADDLE_H));
    p2.setFillColor(sf::Color::White);
    float p2Vel = 7.f;

    // PONG BALL
    sf::RectangleShape pong;
    sf::Vector2f pongPos(SCREEN_W / 2.f - PONG_SIZE / 2.f, SCREEN_H / 2.f - PONG_SIZE / 2.f);
    pong.setPosition(pongPos);
    pong.setSize(sf::Vector2f(PONG_SIZE, PONG_SIZE));
    pong.setFillColor(sf::Color::White);
    float pongVelX = 7.f;
    float pongVelY = 7.f;


    window.setFramerateLimit(60);
    // GAME LOOP
    // ---------
    while (window.isOpen()) {
        sf::Event event{};
        // EVENT HANDLER
        // -------------
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                window.close();
            if ((sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                    && p1Pos.y > 5)
                p1Pos.y -= p1Vel;
            if ((sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                    && p1Pos.y + PADDLE_H < SCREEN_H - 5)
                p1Pos.y += p1Vel;
        }
        // LOGIC
        // -----
        movementAI(p2Pos, p2Vel);
        // UPDATE
        // ------
        p1.setPosition(p1Pos);
        p2.setPosition(p2Pos);
        pong.setPosition(pongPos);
        // RENDER
        // ------
        window.clear();
        window.draw(p1);
        window.draw(p2);
        window.draw(pong);
        window.display();
    }


    return 0;
}
