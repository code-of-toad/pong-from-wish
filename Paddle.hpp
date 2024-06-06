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
    int                _score;
    bool               _loser;
public:
    Paddle(Side side, const sf::RenderWindow& window);
    void               moveUp  (float dt);
    void               moveDown(float dt);
    void               draw    (sf::RenderWindow& window) const;
    Side               getSide () const;
    sf::RectangleShape getRect () const;
    void               setLoser(bool isLoser=true);
    bool               isLoser() const;
    int                scoreUp();
    int                getScore() const;
    void               reset(const sf::RenderWindow& window);
};

#endif //PADDLE_HPP