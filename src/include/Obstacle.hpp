#pragma once

#include <raylib.h>

class Obstacle
{
public:
    Texture2D texture;
    float x, y;
    float speed;
    int index;

    bool canMove = true;

    void Draw();
};

void Obstacle::Draw()
{
    DrawTexturePro(this->texture, (Rectangle){0, 0, 128, 670}, (Rectangle){x, y, 128, 670}, (Vector2){128 / 2, 670 / 2}, 0.f, WHITE);
    DrawTexturePro(this->texture, (Rectangle){0, 0, 128, 670}, (Rectangle){x, y + 970, 128, 670}, (Vector2){128 / 2, 670 / 2}, 180.f, WHITE);
}