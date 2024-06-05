#ifndef BALL_HPP
#define BALL_HPP

#include <SFML/Graphics.hpp>
#include "Paddle.hpp"

class Ball {
    sf::RectangleShape _rect;
    float              _dx;
    float              _dy;

public:
    explicit Ball(const sf::RenderWindow& window);
    void move(float dt);
    void draw(sf::RenderWindow& window) const;
    bool collides(const Paddle& paddle);
    bool reset();
};

#endif //BALL_HPP