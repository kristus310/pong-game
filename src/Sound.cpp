#include "Sound.h"
#include <iostream>

sf::SoundBuffer Sound::paddleBuffer;
sf::SoundBuffer Sound::wallBuffer;
sf::SoundBuffer Sound::scoreBuffer;

sf::Sound Sound::sound;

void Sound::initialize() {
    if (!paddleBuffer.loadFromFile("../assets/sounds/paddle_bounce.wav")) {
        std::cerr << "Failed to load paddle sound!" << std::endl;
    }
    if (!wallBuffer.loadFromFile("../assets/sounds/wall_bounce.wav")) {
        std::cerr << "Failed to load wall sound!" << std::endl;
    }
    if (!scoreBuffer.loadFromFile("../assets/sounds/score.wav")) {
        std::cerr << "Failed to load score sound!" << std::endl;
    }
}

void Sound::paddle() {
    sound.setBuffer(paddleBuffer);
    sound.play();
}

void Sound::wall() {
    sound.setBuffer(wallBuffer);
    sound.play();
}

void Sound::score() {
    sound.setBuffer(scoreBuffer);
    sound.play();
}