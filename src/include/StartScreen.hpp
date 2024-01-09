#pragma once

#include "raylib.h"
#include <iostream>

class StartScreen
{
public:
    int cooldown = 0;

    StartScreen(int _cooldown)
    {
        cooldown = _cooldown;
    }

    void writeText(Font font, string text, Vector2 pos, float fontSize, Color color);
    void SplashScreen(Font font, int width, int height, Vector2 textPos);
};

void StartScreen::SplashScreen(Font font, int width, int height, Vector2 textPos)
{
    DrawRectangle(0, 0, width, height, (Color){153, 133, 133, 255});
    writeText(font, "MADE BY EC", textPos, 64.f, BLACK);
}

void StartScreen::writeText(Font font, string text, Vector2 pos, float fontSize, Color color)
{
    DrawTextEx(font, text.c_str(), pos, fontSize, 0.f, color);
}