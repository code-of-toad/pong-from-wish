#ifndef PADDLE_HPP
#define PADDLE_HPP

#include <SFML/Graphics.hpp>

class Paddle {
    float _x;
    float _y;
    int   _width;
    int   _height;
    float _dy;
public:
    Paddle();
    void update(float dt);
    void draw();
};

#endif //PADDLE_HPP
