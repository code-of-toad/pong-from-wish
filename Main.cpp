#include <SFML/Graphics.hpp>

#define SCREEN_W 1280
#define SCREEN_H 720


int main() {
    // VARIABLES
    // ---------
    sf::Color colorText(150, 150, 150, 200);
    sf::Color colorEntities(200, 200, 200, 200);

    // SETUP: SKELETON
    // ---------------
    sf::RenderWindow window(sf::VideoMode(SCREEN_W, SCREEN_H), "Pong From Wish",
                            sf::Style::Titlebar | sf::Style::Close);
    window.setVerticalSyncEnabled(true);

    sf::ContextSettings settings;
    settings.antialiasingLevel = 0;

    sf::Font mainFont;
    if (!mainFont.loadFromFile("./resources/fonts/font.ttf")) {
        return EXIT_FAILURE;
    }

    // SETUP: GAME ELEMENTS + ENTITIES
    // -------------------------------
    // text
    sf::Text text1;
    text1.setFont(mainFont);
    text1.setString("Welcome to Pong From Wish!");
    text1.setCharacterSize(40);
    text1.setFillColor(colorText);
    text1.setStyle(sf::Text::Bold);
    sf::FloatRect bounds1 = text1.getLocalBounds();
    text1.setOrigin(bounds1.left + bounds1.width / 2, bounds1.top);

    text1.setPosition(sf::Vector2f(window.getSize().x / 2.f, 20.f));

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

        window.draw(text1);

        window.display();
    }

    return EXIT_SUCCESS;
}