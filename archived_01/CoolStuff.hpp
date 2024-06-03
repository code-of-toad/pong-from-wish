#ifndef COOLSTUFF_HPP
#define COOLSTUFF_HPP

#include <SFML/Graphics.hpp>
#include "GLOBALS.hpp"


namespace CoolStuff {

    inline void classicScreenSaver() {
        sf::RenderWindow window(sf::VideoMode(SCREEN_W, SCREEN_H), "My Program");

        sf::RectangleShape rect;
        sf::Vector2f rectPosition(640, 360);
        rect.setPosition(rectPosition);
        rect.setSize(sf::Vector2f(100, 100));
        rect.setFillColor(sf::Color::Red);

        float xVel = 7;
        float yVel = 7;

        window.setFramerateLimit(60);
        while (window.isOpen()) {
            sf::Event event{};
            while (window.pollEvent(event)) {  // `pollEvent` returns `true` if it modifies `event`
                if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                    window.close();
            }
            // PHYSICS
            // -------
            // logic
            if (rectPosition.x <= 0 || rectPosition.x >= SCREEN_W - 100)
                xVel *= -1;
            if (rectPosition.y <= 0 || rectPosition.y >= SCREEN_H - 100)
                yVel *= -1;
            // increment
            rectPosition.x += xVel;
            rectPosition.y += yVel;
            // update
            rect.setPosition(rectPosition);
            // RENDER
            // ------
            window.clear();
            window.draw(rect);
            window.display();
        }
    }

}


#endif //COOLSTUFF_HPP
