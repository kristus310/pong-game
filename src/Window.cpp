#include "Window.h"

sf::VideoMode Window::desktopMode = sf::VideoMode::getDesktopMode();
sf::Vector2u Window::windowSize = {desktopMode.width, desktopMode.height};
sf::RenderWindow Window::window;

sf::RenderWindow& Window::initializeWindow() {
    if (!window.isOpen()) {
        window.create(sf::VideoMode(windowSize.x, windowSize.y), "Pong", sf::Style::Fullscreen);
        window.setFramerateLimit(60);
    }
    return window;
}

sf::Vector2u Window::getSize() {
    return windowSize;
}
