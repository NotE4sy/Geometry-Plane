#pragma once

#include <raylib.h>

class Player
{
public:
    float x, y;
    float size;
    float rotation;
    float speed;
    float deathSpeed;
    float deathX = 0, deathY = 0;

    bool canTurn = false;
    bool dead = false;
    Texture2D texture;

    Player(Texture2D _texture, float _x, float _y, float _size, float _speed, float _deathSpeed)
    {
        texture = _texture;
        x = _x;
        y = _y;
        size = _size;
        speed = _speed;
        deathSpeed = _deathSpeed;
    }

    void Draw();
    void parseMovement();
};

void Player::Draw()
{
    DrawTexturePro(this->texture, (Rectangle){0, 0, 256, 256}, (Rectangle){x, y, size, size}, (Vector2){size / 2, size / 2}, rotation, WHITE);
}

void Player::parseMovement()
{
    if (!dead)
    {
        if (rotation == 45 && y > 20)
        {
            //Move up
            y -= speed * GetFrameTime();
        }
        else if (rotation == 135)
        {
            //Move Down
            y += speed * GetFrameTime();
        }
    }
    else
    {
        if (deathX == 0 && deathY == 0)
        {
            deathX = x;
            deathY = y;
        }   

        if (y < 900)
        {
            y += deathSpeed * GetFrameTime();
        }

        if (rotation < 180)
        {
            rotation += 500 * GetFrameTime();
        }
        else
        {
            rotation = 180;
        }
    }
}