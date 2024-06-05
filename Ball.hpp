#ifndef BALL_HPP
#define BALL_HPP

#include <SFML/Graphics.hpp>
#include "Paddle.hpp"

class Ball {
    float _x      = 0;
    float _y      = 0;
    int   _width  = 0;
    int   _height = 0;
public:
    Ball();
    bool collides(Paddle paddle);
    bool reset();
};

#endif //BALL_HPP