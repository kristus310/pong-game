#include "Game.h"
#include "Paddle.h"
#include "Window.h"
#include "Settings.h"
#include "Sound.h"


//PUBLIC
Game::Game() : state(State::MENU), window(Window::initializeWindow()), score(), playerOne(false), playerTwo(true)  {
    Sound::initialize();
    windowSize = {static_cast<float>(Window::getSize().x), static_cast<float>(Window::getSize().y)};

    if (!texture.loadFromFile("../assets/images/blackandwhite.jpg")) {
        if (!texture.loadFromFile("./assets/images/blackandwhite.jpg")) {
            if (!texture.loadFromFile("assets/images/blackandwhite.jpg")) {
                //Create fallback texture that is just a gray color
                sf::Image fallbackImage;
                fallbackImage.create(2, 2, sf::Color(64, 64, 64, 255));
                texture.loadFromImage(fallbackImage);
            }
        }
    }

    //If not it will use SFML, default font, so no error handling is needed.
    font.loadFromFile("../assets/fonts/font.ttf");

    net.setSize({Settings::NetSize(), windowSize.y});
    net.setPosition({windowSize.x / 2, 0});
    net.setTexture(&texture);

    textOne.setFont(font);
    textOne.setString("0");
    textOne.setCharacterSize(Settings::FontSize());

    sf::FloatRect boundsOne = textOne.getLocalBounds();
    textOne.setOrigin(boundsOne.left + boundsOne.width / 2.f, boundsOne.top + boundsOne.height / 2.f);
    textOne.setFillColor(sf::Color::White);
    textOne.setPosition(windowSize.x / 4.f, windowSize.y / 10.f);

    textTwo.setFont(font);
    textTwo.setString("0");
    textTwo.setCharacterSize(Settings::FontSize());

    sf::FloatRect boundsTwo = textTwo.getLocalBounds();
    textTwo.setOrigin(boundsTwo.left + boundsTwo.width / 2.f, boundsTwo.top + boundsTwo.height / 2.f);
    textTwo.setFillColor(sf::Color::White);
    textTwo.setPosition(windowSize.x - windowSize.x / 4.f, windowSize.y / 10.f);
}

void Game::start() {
    Game game;
    game.run();
}

//PRIVATE
void Game::run() {
    while (window.isOpen()) {
        eventHandling();
        if (state == State::MENU) {
            menu();
        } else if (state == State::PLAYING) {
            update();
            render();
            checkWin();
        } else {
            window.close();
        }
    }
}

void Game::menu() {
    sf::Text titleText;
    sf::Text descriptionText1;
    sf::Text descriptionText2;
    sf::Text playText;
    sf::Text exitText;

    titleText.setFont(font);
    titleText.setString("PONG");
    sf::FloatRect titleBounds = titleText.getLocalBounds();
    titleText.setOrigin(titleBounds.left + titleBounds.width / 2.f, titleBounds.top + titleBounds.height / 2.f);
    titleText.setPosition(windowSize.x / 2.f, windowSize.y / 4.f);
    titleText.setScale(2.f, 2.f); // Scale up the title for visibility

    descriptionText1.setFont(font);
    descriptionText1.setString("The 1st player to get 5 points wins!");
    sf::FloatRect desc1Bounds = descriptionText1.getLocalBounds();
    descriptionText1.setOrigin(desc1Bounds.left + desc1Bounds.width / 2.f, desc1Bounds.top + desc1Bounds.height / 2.f);
    descriptionText1.setPosition(windowSize.x / 2.f, windowSize.y / 3.f);

    descriptionText2.setFont(font);
    descriptionText2.setString("The ball's speed increases with every bounce.");
    sf::FloatRect desc2Bounds = descriptionText2.getLocalBounds();
    descriptionText2.setOrigin(desc2Bounds.left + desc2Bounds.width / 2.f, desc2Bounds.top + desc2Bounds.height / 2.f);
    descriptionText2.setPosition(windowSize.x / 2.f, windowSize.y / 3.f + 40.f); // 40px below the first description

    playText.setFont(font);
    playText.setString("Press SPACE to play");
    sf::FloatRect playBounds = playText.getLocalBounds();
    playText.setOrigin(playBounds.left + playBounds.width / 2.f, playBounds.top + playBounds.height / 2.f);
    playText.setPosition(windowSize.x / 2.f, windowSize.y / 2.f);

    exitText.setFont(font);
    exitText.setString("Press ESC to exit");
    sf::FloatRect exitBounds = exitText.getLocalBounds();
    exitText.setOrigin(exitBounds.left + exitBounds.width / 2.f, exitBounds.top + exitBounds.height / 2.f);
    exitText.setPosition(windowSize.x / 2.f, windowSize.y / 1.8f);

    window.clear(sf::Color::Black);
    window.draw(titleText);
    window.draw(descriptionText1);
    window.draw(descriptionText2);
    window.draw(playText);
    window.draw(exitText);
    window.display();
}

void Game::checkWin() {
    if (playerOne.points >= 5 || playerTwo.points >= 5) {
        sf::Text text;
        text.setFont(font);
        std::string winner = (playerOne.points >= 5) ? "Player one has won!" : "Player two has won!";
        text.setString(winner);

        sf::FloatRect textBounds = text.getLocalBounds();
        text.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
        text.setPosition(windowSize.x / 2, windowSize.y / 2);

        window.clear();
        window.draw(text);
        window.display();

        sf::sleep(sf::seconds(3));
        state = State::MENU;
    }
}


void Game::eventHandling() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed ||
            (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
            state = State::EXIT;
        }
        if (event.key.code == sf::Keyboard::Space && state == State::MENU) {
            state = State::PLAYING;
        }
    }
}

void Game::update() {
    ball.move(ball.getVelocity());

    playerOne.checkMovement();
    playerTwo.checkMovement();
    playerOne.checkCollision();
    playerTwo.checkCollision();

    score = ball.checkCollisions();
    if (score.points != 0) {
        if (score.isRight) {
            playerTwo.points++;
        } else {
            playerOne.points++;
        }
    }
    textOne.setString(std::to_string(playerOne.points));
    textTwo.setString(std::to_string(playerTwo.points));

    ball.checkObjectCollisions(playerOne.getShape());
    ball.checkObjectCollisions(playerTwo.getShape());
}

void Game::render() {
    window.clear(sf::Color::Black);
    window.draw(net);
    window.draw(textOne);
    window.draw(textTwo);

    playerOne.draw(window);
    playerTwo.draw(window);
    ball.draw(window);
    window.display();
}


