#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>

#include "Ball.h"
#include "Paddle.h"

class Game {
public:
    Game();
    static void start();

private:
    enum class State {
        MENU,
        PLAYING,
        EXIT
    };
    State state;

    void run();
    void menu();
    void checkWin();
    void eventHandling();
    void update();
    void render();

    sf::RenderWindow& window;
    sf::Vector2f windowSize;
    sf::Texture texture;
    sf::RectangleShape net;

    sf::Font font;
    sf::Text textOne;
    sf::Text textTwo;

    Ball ball;
    Ball::Score score;

    Paddle playerOne;
    Paddle playerTwo;
};

#endif
