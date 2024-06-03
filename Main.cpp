#include <SFML/Graphics.hpp>

#define SCREEN_W 1280
#define SCREEN_H 720

int main() {
    // SETUP: SKELETON
    // ---------------
    sf::RenderWindow window(sf::VideoMode(SCREEN_W, SCREEN_H),
                            "Pong From Wish",
                            sf::Style::Titlebar | sf::Style::Close);
    window.setVerticalSyncEnabled(true);

    sf::ContextSettings settings;
    settings.antialiasingLevel = 0;

    sf::Font font;
    if (!font.loadFromFile("./resources/fonts/font.ttf")) {
        return EXIT_FAILURE;
    }

    sf::Text text;
    text.setFont(font);
    text.setString("Pong From Wish");
    text.setCharacterSize(50);
    text.setFillColor(sf::Color(200, 200, 200, 200));
    text.setStyle(sf::Text::Bold);
    sf::FloatRect bounds = text.getLocalBounds();
    text.setOrigin(bounds.left + bounds.width / 2, bounds.top + bounds.height / 2);

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
        text.setPosition(sf::Vector2f(window.getSize().x / 2.f, window.getSize().y / 2.f));

        // RENDER
        // ------
        window.clear();

        window.draw(text);

        window.display();
    }

    return EXIT_SUCCESS;
}
