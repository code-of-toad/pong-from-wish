#include <SFML/Graphics.hpp>
#include "Paddle.hpp"
#include "Ball.hpp"

#define SCREEN_W 1280
#define SCREEN_H 720

int main() {
    sf::RenderWindow window(sf::VideoMode(SCREEN_W, SCREEN_H), "Pong From Wish",
                            sf::Style::Titlebar | sf::Style::Close);
    window.setVerticalSyncEnabled(true);
    //window.setFramerateLimit(60);

    sf::Event event{};
    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                window.close();
            }
        }
        window.clear();

        window.display();
    }

    return EXIT_SUCCESS;
}