#ifndef PONG_SOUND_H
#define PONG_SOUND_H

#include "SFML/Audio.hpp"

class Sound {
public:
    static void initialize();
    static void paddle();
    static void wall();
    static void score();

private:
    static sf::SoundBuffer paddleBuffer;
    static sf::SoundBuffer wallBuffer;
    static sf::SoundBuffer scoreBuffer;
    static sf::Sound sound;
};


#endif //PONG_SOUND_H
