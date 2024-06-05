#include <SFML/Graphics.hpp>
#include <random>

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
    // window.setFramerateLimit(60);
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
    text1.setString("Pong From Wish");
    text1.setCharacterSize(40);
    text1.setFillColor(colorText);
    text1.setStyle(sf::Text::Bold);
    sf::FloatRect bounds1 = text1.getLocalBounds();
    text1.setOrigin(bounds1.left + bounds1.width / 2, bounds1.top);

    text1.setPosition(sf::Vector2f(window.getSize().x / 2.f, 20.f));

    // ball
    sf::RectangleShape ball(sf::Vector2f(15.f, 15.f));
    ball.setFillColor(colorEntities);
    sf::FloatRect bounds2 = ball.getLocalBounds();
    ball.setOrigin(bounds2.left + bounds2.width / 2, bounds2.top + bounds2.height / 2);

    ball.setPosition(sf::Vector2f(window.getSize().x / 2.f, window.getSize().y / 2.f));

    // paddle (left)
    sf::RectangleShape paddleLeft(sf::Vector2f(17.f, 120.f));
    paddleLeft.setFillColor(colorEntities);
    sf::FloatRect bounds3 = paddleLeft.getLocalBounds();
    paddleLeft.setOrigin(bounds3.left, bounds3.top + bounds3.height / 2);

    paddleLeft.setPosition(sf::Vector2f(20.f, window.getSize().y / 2.f));

    // paddle (right)
    sf::RectangleShape paddleRight(sf::Vector2f(17.f, 120.f));
    paddleRight.setFillColor(colorEntities);
    sf::FloatRect bounds4 = paddleRight.getLocalBounds();
    paddleRight.setOrigin(bounds4.left + bounds4.width, bounds4.top + bounds4.height / 2);

    paddleRight.setPosition(sf::Vector2f(window.getSize().x - 20.f, window.getSize().y / 2.f));

    while (window.isOpen()) {
        // EVENT HANDLER
        // -------------
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                window.close();
            }
        }
        // INPUT HANDLING
        // --------------
        // paddle (left)
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            if (paddleLeft.getGlobalBounds().top > 0)
                paddleLeft.move(0, -10.f);
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            if (paddleLeft.getGlobalBounds().top + paddleLeft.getGlobalBounds().height < window.getSize().y)
                paddleLeft.move(0, 10.f);
        }
        // paddle (right)
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            if (paddleRight.getGlobalBounds().top > 0)
                paddleRight.move(0, -10.f);
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            if (paddleRight.getGlobalBounds().top + paddleRight.getGlobalBounds().height < window.getSize().y)
                paddleRight.move(0, 10.f);
        }

        // RENDER
        // ------
        window.clear();

        window.draw(text1);
        window.draw(ball);
        window.draw(paddleLeft);
        window.draw(paddleRight);

        window.display();
    }

    return EXIT_SUCCESS;
}