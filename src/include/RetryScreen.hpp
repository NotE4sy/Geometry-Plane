#pragma once

#include <raylib.h>
#include <iostream>

using namespace std;

class RetryScreen
{
public:
    float Width, Height;
    float x, y;
    Color background;

    RetryScreen(float width, float height, float _x, float _y, Color _background)
    {
        Width = width;
        Height = height;
        x = _x;
        y = _y;
        background = _background;
    }

    void Draw();
    void writeText(Font font, string text, Vector2 pos, float fontSize);
};

void RetryScreen::Draw()
{
    DrawRectanglePro((Rectangle){x, y, Width, Height}, (Vector2){Width / 2, Height / 2}, 0.f, background);
}

void RetryScreen::writeText(Font font, string text, Vector2 pos, float fontSize)
{
    DrawTextEx(font, text.c_str(), pos, fontSize, 0.f, WHITE);
}