#include "Ball.hpp"

Ball::Ball(const sf::RenderWindow& window) {
    _dx = -350.f;
    _dy = -350.f;
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

bool Ball::collides(const Paddle& paddle) {
    if (_rect.getGlobalBounds().intersects(paddle.getRect().getGlobalBounds())) {
        if ((paddle.getSide() == LEFT && _dx < 0) || (paddle.getSide() == RIGHT && _dx > 0)) {
            _dx *= -1;
            return true;
        }
    }
    return false;
}
