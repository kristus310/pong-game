#include "Ball.h"
#include "Window.h"
#include "Settings.h"
#include "Sound.h"

#include <random>

static std::random_device rd;
static std::mt19937 gen(rd());
static std::uniform_real_distribution<float> x(Settings::BallSpeedX(), Settings::BallSpeedX() * 1.5f);
static std::uniform_real_distribution<float> y(Settings::BallSpeedY(), Settings::BallSpeedY() * 1.5f);
static std::bernoulli_distribution sign(0.5);

//PUBLIC
Ball::Ball() {
    windowSize = {static_cast<float>(Window::getSize().x), static_cast<float>(Window::getSize().y)};
    maxSpeed = 32.0f; //MAX SPEED BEFORE IT STARTS TUNNELLING

    shape.setRadius(Settings::BallRadius());
    shape.setPointCount(100);
    shape.setFillColor(sf::Color::White);

    reset(false);
}

void Ball::draw(sf::RenderWindow &window) {
    window.draw(shape);
}

void Ball::move(sf::Vector2f velocity_) {
    shape.move(velocity_);
}

void Ball::reset(bool isRight) {
    shape.setPosition(windowSize.x / 2.f, windowSize.y / 2.f);
    float velX = x(gen);
    float velY = y(gen);

    velX *= (isRight ? 1.f : -1.f);
    if (sign(gen)) velY = -velY;

    velocity = {velX, velY};
}

Ball::Score Ball::checkCollisions() {
    if (shape.getPosition().y <= 0) {
        shape.setPosition(shape.getPosition().x, 0);
        velocity.y = -velocity.y;
        Sound::wall();
    }

    if (shape.getPosition().y + shape.getRadius() * 2 >= windowSize.y) {
        shape.setPosition(shape.getPosition().x, windowSize.y - shape.getRadius() * 2);
        velocity.y = -velocity.y;
        Sound::wall();
    }

    if (shape.getPosition().x < 0) {
        reset(true);
        Sound::score();
        return Score{
            1,
            true
        };
    }

    if (shape.getPosition().x + shape.getRadius() * 2 > windowSize.x) {
        reset(false);
        Sound::score();
        return Score{
            1,
            false
        };
    }
    return Score{
        0,
        false
    };
}

void Ball::checkObjectCollisions(const sf::RectangleShape& paddle) {
    if (shape.getGlobalBounds().intersects(paddle.getGlobalBounds())) {
        float ballCenter = shape.getPosition().x + shape.getRadius();
        float paddleCenter = paddle.getPosition().x;

        if (ballCenter < paddleCenter) {
            shape.setPosition(paddle.getPosition().x - paddle.getSize().x/2 - shape.getRadius()*2, shape.getPosition().y);
            Sound::paddle();
        } else {
            shape.setPosition(paddle.getPosition().x + paddle.getSize().x/2, shape.getPosition().y);
            Sound::paddle();
        }

        velocity.x = -velocity.x;
        if (velocity.x >= 0) {
            velocity.x += Settings::BallSpeedX() / 5;
        } else {
            velocity.x -= Settings::BallSpeedX() / 5;
        }

        if (std::abs(velocity.x) > maxSpeed) {
            if (velocity.x > 0) {
                velocity.x = maxSpeed;
            } else {
                velocity.x = -maxSpeed;
            }
        }

        float ballCenterY = shape.getPosition().y + shape.getRadius();
        float hitOffset = ballCenterY - paddle.getPosition().y;
        velocity.y += hitOffset * 0.1f;


        if (velocity.y > 8.0f) {
            velocity.y = 8.0f;
        }

        if (velocity.y < -8.0f) {
            velocity.y = -8.0f;
        }
    }
}

//Setters

//Getters
sf::Vector2f Ball::getVelocity() {
    return velocity;
}
