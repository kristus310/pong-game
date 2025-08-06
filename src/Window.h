#ifndef WINDOW_H
#define WINDOW_H

#include <SFML/Graphics.hpp>

class Window {
public:
    static sf::RenderWindow& initializeWindow();
    static sf::Vector2u getSize();

private:
    static sf::RenderWindow window;
    static sf::VideoMode desktopMode;
    static sf::Vector2u windowSize;

};

#endif
