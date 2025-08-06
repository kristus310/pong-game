#ifndef BALL_H
#define BALL_H

#include <SFML/Graphics.hpp>

class Ball {
public:
    struct Score {
        int points;
        bool isRight;
    };

    Ball();
    void draw(sf::RenderWindow& window);
    void move(sf::Vector2f velocity_);
    void reset(bool isRight);
    Score checkCollisions();
    void checkObjectCollisions(const sf::RectangleShape &paddle);
    sf::Vector2f getVelocity();

private:
    sf::Vector2f windowSize;
    sf::CircleShape shape;
    sf::Vector2f velocity;
    float maxSpeed;

};

#endif
