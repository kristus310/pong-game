#ifndef PADDLE_H
#define PADDLE_H

#include <SFML/Graphics.hpp>

class Paddle {
public:
    Paddle(bool isRight);
    void draw(sf::RenderWindow& window);
    void checkCollision();
    void checkMovement();
    const sf::RectangleShape& getShape() const;
    int points;

private:
    sf::Vector2f windowSize;
    sf::RectangleShape shape;
    bool isRight;
    float speed;

};

#endif
