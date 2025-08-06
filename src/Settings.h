#ifndef SETTINGS_H
#define SETTINGS_H

#include "Window.h"

namespace Settings {
    //Font
    inline int FontSize()           {return Window::getSize().y * 0.12f; }  //12% of window size = 1080 * 0.12 = 129.6f
    //Ball
    inline float BallRadius()       { return static_cast<float>(Window::getSize().y) * 0.025f; } //2.5% of window size = 1080 * 0.025 = 27.0f
    inline float BallSpeedX()       { return static_cast<float>(Window::getSize().y) * 0.007f; } //1.2% of window size = 1080 * 0.012 = 12.96f
    inline float BallSpeedY()       { return static_cast<float>(Window::getSize().y) * 0.005f; } //0.8% of window size = 1080 * 0.008 = 8.64f
    //Game
    inline float NetSize()          { return static_cast<float>(Window::getSize().y) * 0.005f; } //0.5% of window size = 1080 * 0.005 = 5.4f
    //Paddle
    inline float PaddleSpeed()      { return static_cast<float>(Window::getSize().y) * 0.015f; } //1.5% of window size = 1080 * 0.015 = 16.2f
    inline float PaddleWidth()      { return static_cast<float>(Window::getSize().x) * 0.005f; } //0.5% of window size = 1080 * 0.005 = 5.4f
    inline float PaddleHeight()     { return static_cast<float>(Window::getSize().y) * 0.20f;  } //20% of window size = 1080 * 0.20 = 216.0f
}

#endif
