#ifndef PADDLE_HPP
#define PADDLE_HPP

#include <SFML/Graphics.hpp>

enum Side {
    LEFT,
    RIGHT
};

class Paddle {
    sf::RectangleShape _rect;
    Side               _side;
    float              _dy;
public:
    Paddle(Side side, const sf::RenderWindow& window);
    void moveUp(float dt);
    void moveDown(float dt);
    void draw(sf::RenderWindow& window) const;
};

#endif //PADDLE_HPP