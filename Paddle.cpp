#include "Paddle.hpp"

Paddle::Paddle(const Side side, const sf::RenderWindow& window) {
    _side  = side;
    _dy    = 480.f;
    _score = 0;
    _rect  = sf::RectangleShape(sf::Vector2f(18.f, 120.f));

    _rect.setFillColor(sf::Color(200, 200, 200, 200));
    sf::FloatRect bounds = _rect.getLocalBounds();
    if (side == LEFT) {
        _loser = true;
        _rect.setOrigin(bounds.left, bounds.top + bounds.height / 2);
        _rect.setPosition(sf::Vector2f(20.f, window.getSize().y / 2.f));
    } else if (side == RIGHT) {
        _loser = false;
        _rect.setOrigin(bounds.left + bounds.width, bounds.top + bounds.height / 2);
        _rect.setPosition(sf::Vector2f(window.getSize().x - 20.f, window.getSize().y / 2.f));
    }
}

void Paddle::moveUp(const float dt) {
    if (_rect.getGlobalBounds().top > 5)
        _rect.move(0, -_dy * dt);
    else
        if (_side == LEFT)
            _rect.setPosition(sf::Vector2f(20.f, 65.f));
        else if (_side == RIGHT)
            _rect.setPosition(sf::Vector2f(1280.f - 20.f, 65.f));
}

void Paddle::moveDown(const float dt) {
    if (_rect.getGlobalBounds().top + _rect.getGlobalBounds().height < 715.f)
        _rect.move(0, _dy * dt);
    else
        if (_side == LEFT)
            _rect.setPosition(sf::Vector2f(20.f, 720.f - 65.f));
        else if (_side == RIGHT)
            _rect.setPosition(sf::Vector2f(1280.f - 20.f, 720.f - 65.f));
}

void Paddle::draw(sf::RenderWindow& window) const {
    window.draw(_rect);
}

Side Paddle::getSide() const {
    return _side;
}

sf::RectangleShape Paddle::getRect() const {
    return _rect;
}

void Paddle::setLoser(const bool isLoser) {
    _loser = isLoser;
}

bool Paddle::isLoser() const {
    return _loser;
}

int Paddle::scoreUp() {
    return ++_score;
}

int Paddle::getScore() const {
    return _score;
}

void Paddle::reset(const sf::RenderWindow& window) {
    _score = 0;
    if (_side == LEFT)
        _rect.setPosition(sf::Vector2f(20.f, window.getSize().y / 2.f));
    else if (_side == RIGHT)
        _rect.setPosition(sf::Vector2f(window.getSize().x - 20.f, window.getSize().y / 2.f));
}