#include "Paddle.h"
#include "Window.h"
#include "Settings.h"

//PUBLIC
Paddle::Paddle(bool isRight) {
    this->isRight = isRight;
    speed = Settings::PaddleSpeed();
    points = 0;

    windowSize = {static_cast<float>(Window::getSize().x), static_cast<float>(Window::getSize().y)};
    shape.setSize({Settings::PaddleWidth(), Settings::PaddleHeight()});
    shape.setFillColor(sf::Color::White);

    shape.setOrigin(shape.getSize().x / 2, shape.getSize().y / 2);
    float margin = Settings::PaddleWidth() * 10;
    if (isRight) {
        shape.setPosition(windowSize.x - margin, windowSize.y / 2.f);
    } else {
        shape.setPosition(margin, windowSize.y / 2.f);
    }
}

void Paddle::draw(sf::RenderWindow& window) {
    window.draw(shape);
}

void Paddle::checkCollision() {
    float halfHeight = shape.getSize().y / 2;

    if (shape.getPosition().y + halfHeight > windowSize.y) {
        shape.setPosition(shape.getPosition().x, windowSize.y - halfHeight);
    }
    if (shape.getPosition().y - halfHeight < 0) {
        shape.setPosition(shape.getPosition().x, halfHeight);
    }
}

void Paddle::checkMovement() {
    if (isRight) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            shape.move(0.0f, -speed);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            shape.move(0.0f, speed);
        }
    } else {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            shape.move(0.0f, -speed);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            shape.move(0.0f, speed);
        }
    }

}

const sf::RectangleShape& Paddle::getShape() const {
    return shape;
}