#pragma once

#include "raylib.h"
#include <stdlib.h>
#include <iostream>

struct SpriteAnimation
{
    Texture2D atlas;
    int fps;

    Rectangle* rectangles;
    int length;
};

SpriteAnimation CreateNew(Texture2D atlas, int fps, Rectangle rectangles[], int length)
{
    SpriteAnimation spriteAnim = 
    {
        .atlas = atlas,
        .fps = fps,
        .length = length
    };

    Rectangle* mem = (Rectangle*)malloc(sizeof(Rectangle) * length);

    if (mem == NULL)
    {
        TraceLog(LOG_FATAL, "No memory for creation");
        spriteAnim.length = 0;
        return spriteAnim;
    }

    spriteAnim.rectangles = mem;

    for (int i = 0; i < length; i++)
    {
        spriteAnim.rectangles[i] = rectangles[i];
    }

    return spriteAnim;
}

void DrawAnimation(SpriteAnimation anim, Rectangle dest, Vector2 origin)
{
    int index = (int)(GetTime() * anim.fps) % anim.length;
    Rectangle source = anim.rectangles[index];
    DrawTexturePro(anim.atlas, source, dest, origin, 0.f, WHITE);
}