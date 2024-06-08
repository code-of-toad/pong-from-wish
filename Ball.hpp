#ifndef BALL_HPP
#define BALL_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Paddle.hpp"

class Ball {
    sf::RectangleShape _rect;
    float              _dx;
    float              _dy;
    sf::SoundBuffer    _soundBuffer;
    sf::Sound          _sound;

public:
    explicit Ball(const sf::RenderWindow& window);
    void               move(float dt, sf::Sound& sound);
    void               draw(sf::RenderWindow& window) const;
    void               reset(const sf::RenderWindow& window);
    bool               collides(const Paddle& paddle);
    sf::RectangleShape getRect() const;
    void               setDirection(Side side);
};

#endif //BALL_HPP