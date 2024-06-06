#include <random>
#include "Ball.hpp"

float randVerticalSpeed() {
    // create a random device
    std::random_device rd;
    // seed a random number generator
    std::mt19937 gen(rd());
    // define a range for the numbers
    std::uniform_int_distribution dist(0, 500);
    // generate a random number
    return dist(gen);
}

Ball::Ball(const sf::RenderWindow& window) {
    _dx   = -500.f;
    _dy   = -randVerticalSpeed();
    _rect = sf::RectangleShape(sf::Vector2f(16.f, 16.f));
    _rect.setFillColor(sf::Color(200, 200, 200, 200));
    sf::FloatRect bounds = _rect.getLocalBounds();
    _rect.setOrigin(bounds.left + bounds.width / 2, bounds.top + bounds.height / 2);
    _rect.setPosition(sf::Vector2f(window.getSize().x / 2.f, window.getSize().y / 2.f));
}

void Ball::move(const float dt) {
    _rect.move(_dx * dt, _dy * dt);
    if (_rect.getGlobalBounds().top <= 0
            || _rect.getGlobalBounds().top + _rect.getGlobalBounds().height >= 720.f)
        _dy *= -1;
}

void Ball::draw(sf::RenderWindow& window) const {
    window.draw(_rect);
}

void Ball::reset(const sf::RenderWindow& window) {
    _dy = randVerticalSpeed();
    _rect.setPosition(sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2));
}

bool Ball::collides(const Paddle& paddle) {
    if (_rect.getGlobalBounds().intersects(paddle.getRect().getGlobalBounds())) {
        if (paddle.getSide() == LEFT && _dx < 0) {
            _dx *= -1;
            if (_rect.getGlobalBounds().top + _rect.getGlobalBounds().height / 2
                    < paddle.getRect().getGlobalBounds().top + paddle.getRect().getGlobalBounds().height / 2)
                _dy = -randVerticalSpeed();
            else
                _dy = randVerticalSpeed();
            return true;
        }
        if (paddle.getSide() == RIGHT && _dx > 0) {
            _dx *= -1;
            if (_rect.getGlobalBounds().top + _rect.getGlobalBounds().height / 2
                    < paddle.getRect().getGlobalBounds().top + paddle.getRect().getGlobalBounds().height / 2)
                _dy = -randVerticalSpeed();
            else
                _dy = randVerticalSpeed();
            return true;
        }
    }
    return false;
}

sf::RectangleShape Ball::getRect() const {
    return _rect;
}

void Ball::setDirection(const Side side) {
    if (side == LEFT) {
        _dx = -500.f;
        _dy = -randVerticalSpeed();
    } else {
        _dx = 500.f;
        _dy = randVerticalSpeed();
    }
}