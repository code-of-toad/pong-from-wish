#include <SFML/Graphics.hpp>

#define SCREEN_W 1280
#define SCREEN_H 720

int main() {
    sf::RenderWindow window(sf::VideoMode(SCREEN_W, SCREEN_H), "Pong From Wish");
    // SETUP: GAME ELEMENTS + ENTITIES
    // -------------------------------

    while (window.isOpen()) {
        // EVENT HANDLER
        // -------------
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                window.close();
            }
        }
        // GAME LOGIC/UPDATE
        // -----------------


        // RENDER
        // ------
        window.clear();
    }

    return EXIT_SUCCESS;
}