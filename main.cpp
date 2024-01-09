#include "raylib.h"
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <math.h>

#include "src/include/Player.hpp"
#include "src/include/Obstacle.hpp"
#include "src/include/Animation.hpp"
#include "src/include/RetryScreen.hpp"
#include "src/include/StartScreen.hpp"

#define WIDTH 1280
#define HEIGHT 720
#define obstacleMaxSpeed 1000

using namespace std;

vector<Obstacle*> obstacles{};

float yAdd = 128;
float prevY = -400;
int cooldown = 0;
int score = 0;
int prevChange = 0;
int currentSpeed = 400;

void CheckObstacleHeight(Obstacle* obs)
{
    if (obs->y > -27)
    {
        //Compulsory
        yAdd = -128;
    }
    else if (obs->y < -200)
    {
        //Compulsory
        yAdd = 128;
    }
    else
    {
        //Optional
        int flip = (rand() % (2 - 0 + 1)) + 0;
        
        if (flip == 0)
        {
            //flip
             yAdd = yAdd * -1;
        }
        //Else don't flip
    }
}

void LoadObstacles(Texture2D obstacleTexture)
{
    for (int i = 0; i < 12; i++)
    {
        Obstacle* obs = new Obstacle();
        obs->texture = obstacleTexture;
        obs->x = WIDTH + 100 + (i * 128);
        obs->y = prevY + yAdd;
        obs->speed = 400;
        obs->index = i;
        obstacles.push_back(obs);

        CheckObstacleHeight(obs);

        prevY = obs->y;
    }

    prevY = -400;
    yAdd = 128;
}

void MoveObstacles()
{
    for (Obstacle* obs : obstacles)
    {
        if (obs->canMove)
        {
            obs->x -= obs->speed * GetFrameTime();

            if (obs->x < -130)
            {
                int prevIndex = obs->index - 1;

                if (prevIndex < 0) prevIndex = 11;

                obs->x = obstacles[prevIndex]->x + 128;
                obs->y = obstacles[prevIndex]->y + yAdd;

                CheckObstacleHeight(obs);
            }
        }

        obs->Draw();
    }
}

bool CheckCollision(float ax, float ay, float aw, float ah, float bx, float by, float bw, float bh)
{
    //The sides of the rectangles
    float leftA, leftB;
    float rightA, rightB;
    float topA, topB;
    float bottomA, bottomB;

    //Calculate the sides of rect A
    leftA = ax;
    rightA = ax + aw;
    topA = ay;
    bottomA = ay + ah;

    //Calculate the sides of rect B
    leftB = bx;
    rightB = bx + bw;
    topB = by;
    bottomB = by + bh;

    //If any of the sides from A are outside of B
    if( bottomA <= topB || topA >= bottomB || rightA <= leftB || leftA >= rightB)
    {
        return false;
    }

    return true;
}

void updateScore(int duration)
{
    if (cooldown >= duration)
    {
        score++;
        cooldown = 0;
    }

    cooldown++;
}

void increaseObstacleSpeed()
{
    if (score % 15 == 0 && currentSpeed < obstacleMaxSpeed && prevChange != score)
    {
        prevChange = score;
        currentSpeed += 50;

        for (Obstacle* obs : obstacles)
        {
            obs->speed = currentSpeed;
        }
    }
}

int main(void)
{
    //Initialize window

    srand(0);

    InitAudioDevice();

    InitWindow(WIDTH, HEIGHT, "Game");

    SetTargetFPS(60);

    SetExitKey(0);

    //Loading textures

    Texture2D plrTexture = LoadTexture("src/Textures/Player.png");
    Texture2D obstacleTexture = LoadTexture("src/Textures/Obstacle.png");
    Texture2D explosionTexture = LoadTexture("src/Textures/ExplosionAtlas.png");
    Texture2D backgroundTexture = LoadTexture("src/Textures/Background.png");

    //Loading sound effects
    Sound explosionSFX = LoadSound("src/sfx/explosion.wav");    

    //Explosion animation frames

    Rectangle animationFrames[] = {
        (Rectangle){0, 0, 256, 256},
        (Rectangle){256, 0, 256, 256},
        (Rectangle){512, 0, 256, 256},
        (Rectangle){768, 0, 256, 256},
        (Rectangle){1024, 0, 256, 256},
        (Rectangle){1280, 0, 256, 256},
        (Rectangle){1536, 0, 256, 256},
        (Rectangle){1792, 0, 256, 256},
        (Rectangle){0, 256, 256, 256},
        (Rectangle){256, 256, 256, 256},
        (Rectangle){512, 256, 256, 256},
        (Rectangle){768, 256, 256, 256},
        (Rectangle){1024, 256, 256, 256},
        (Rectangle){1280, 256, 256, 256},
        (Rectangle){1536, 256, 256, 256},
        (Rectangle){1792, 256, 256, 256},
        (Rectangle){0, 512, 256, 256},
        (Rectangle){256, 512, 256, 256},
        (Rectangle){512, 512, 256, 256},
        (Rectangle){768, 512, 256, 256},
        (Rectangle){1024, 512, 256, 256},
        (Rectangle){1280, 512, 256, 256},
        (Rectangle){1536, 512, 256, 256},
        (Rectangle){1792, 512, 256, 256},
        (Rectangle){0, 768, 256, 256},
        (Rectangle){256, 768, 256, 256},
        (Rectangle){512, 768, 256, 256},
        (Rectangle){768, 768, 256, 256},
        (Rectangle){1024, 768, 256, 256},
        (Rectangle){1280, 768, 256, 256},
        (Rectangle){1536, 768, 256, 256},
        (Rectangle){1792, 768, 256, 256},
        (Rectangle){0, 1024, 256, 256},
        (Rectangle){256, 1024, 256, 256},
        (Rectangle){512, 1024, 256, 256},
        (Rectangle){768, 1024, 256, 256},
        (Rectangle){1024, 1024, 256, 256},
        (Rectangle){1280, 1024, 256, 256},
        (Rectangle){1536, 1024, 256, 256},
        (Rectangle){1792, 1024, 256, 256},
        (Rectangle){0, 1280, 256, 256},
        (Rectangle){256, 1280, 256, 256},
        (Rectangle){512, 1280, 256, 256},
        (Rectangle){768, 1280, 256, 256},
        (Rectangle){1024, 1280, 256, 256},
        (Rectangle){1280, 1280, 256, 256},
        (Rectangle){1536, 1280, 256, 256},
        (Rectangle){1792, 1280, 256, 256},
        (Rectangle){0, 1536, 256, 256},
        (Rectangle){256, 1536, 256, 256},
        (Rectangle){512, 1536, 256, 256},
        (Rectangle){768, 1536, 256, 256},
        (Rectangle){1024, 1536, 256, 256},
        (Rectangle){1280, 1536, 256, 256},
        (Rectangle){1536, 1536, 256, 256},
        (Rectangle){1792, 1536, 256, 256},
        (Rectangle){0, 1792, 256, 256},
        (Rectangle){256, 1792, 256, 256},
        (Rectangle){512, 1792, 256, 256},
        (Rectangle){768, 1792, 256, 256},
        (Rectangle){1024, 1792, 256, 256},
        (Rectangle){1280, 1792, 256, 256},
        (Rectangle){1536, 1792, 256, 256},
        (Rectangle){1792, 1792, 256, 256},
    };

    //Load font

    Font mainFont = LoadFontEx("src/Fonts/MainFont.ttf", 64.f, NULL, 0);
    Font splashScreenFont = LoadFontEx("src/Fonts/SplashScreenFont.otf", 64.f, NULL, 0);

    //Load obstacles
    LoadObstacles(obstacleTexture);

    //Instantiate Player, Retry Screen, start screen and explosion animation

    Player* plr = new Player(plrTexture, 100, obstacles[0]->y + 400, 64, 400, 800);

    RetryScreen* rScreen = new RetryScreen(WIDTH - 512, HEIGHT - 256, WIDTH / 2, HEIGHT * 2, (Color){20, 20, 20, 255});

    SpriteAnimation anim = CreateNew(explosionTexture, 60, animationFrames, 64);
    int animIndex = 0;

    StartScreen* sScreen = new StartScreen(0);

    int gamePhase = 0;

    while (!WindowShouldClose())
    {
        //Updating

        //If game has started (Which is gamePhase 2)

        if (gamePhase == 2)
        {
            //If player is alive

            if (!plr->dead)
            {
                //Player controls

                if (IsKeyDown(KEY_SPACE))
                {
                    plr->rotation = 45.f;
                    plr->canTurn = true;
                }
                else
                {
                    plr->rotation = 135.f;
                }

                if (!plr->canTurn)
                {
                    plr->rotation = 90.f;
                }

                if (plr->y > HEIGHT + 64)
                {
                    plr->dead = true;
                    plr->speed = 0;
                    plr->canTurn = false;
                }
            }
            //If player is dead
            else
            {
                //If player chooses to retry (by pressing any key)

                if (GetKeyPressed() != 0 && rScreen->y <= HEIGHT / 2)
                {
                    //Resetting screen

                    rScreen->y = HEIGHT * 2;

                    //Reseting obstacles

                    for (Obstacle* obs : obstacles)
                    {
                        obs->x = WIDTH + 100 + (obs->index * 128);
                        obs->y = prevY + yAdd;
                        obs->speed = 400;
                        obs->canMove = true;

                        CheckObstacleHeight(obs);

                        prevY = obs->y;
                    }

                    //Resetting score

                    score = 0;

                    //Resetting animation

                    animIndex = 0;
                
                    //Resetting player

                    plr->y = obstacles[0]->y + 400;
                    plr->speed = 400;
                    plr->rotation = 90;
                    plr->deathX = 0;
                    plr->deathY = 0;
                    plr->dead = false;
                }
            }

            //Loop through obstacles

            for (Obstacle* obs : obstacles)
            {
                //Freezes obstacles in place

                if (plr->dead)
                {
                    obs->canMove = false;
                }

                //If collision between player and obstacle

                if (CheckCollision(plr->x - 10, plr->y - 10, plr->size - 20, plr->size - 20, obs->x - 128 / 2 + 50, obs->y - 670 / 2, 128 - 100, 670) || CheckCollision(plr->x - 10, plr->y - 10, plr->size - 20, plr->size - 20, obs->x - 128 / 2 + 50, obs->y + 970 - 670 / 2, 128 - 100, 670))
                {
                    plr->speed = 0;
                    plr->canTurn = false;
                    plr->dead = true;
                }
            }

            //Score updater

            if (plr->speed != 0)
            {
                updateScore(60);
            }

            //Procedural difficulty increase

            increaseObstacleSpeed();
        }
        //Else if start screen is being shown (Which is gamePhase 1)
        else if (gamePhase == 1)
        {
            if (GetKeyPressed() != 0)
            {
                gamePhase = 2;
            }
        }

        //Drawing

        BeginDrawing();

            //Drawing main components (ClearBackground allows textures to move without having their previous position be rendered)

            ClearBackground((Color){30, 30, 30});
            
            //Draw Background after splash screen (Which is during gamePhase 0)

            if (gamePhase >= 1)
            {
                DrawTexture(backgroundTexture, 0, 0, WHITE);
            }

            //Draw Start text after splash screen (Which is during gamePhase 0)

            if (gamePhase == 1)
            {
                sScreen->writeText(mainFont, "Press any key to start", (Vector2){300, HEIGHT / 2 - 80 + (float)sin(GetTime() * 5) * 8}, 48.f, WHITE);
            }

            //Draw main components when game starts (WHich is during gamePhase 2)

            if (gamePhase == 2)
            {
                MoveObstacles();
                plr->Draw();
                plr->parseMovement();

                //If player is dead (For drawing)

                if (plr->dead)
                {
                    //Play explosion animation

                    if (animIndex == 1)
                    {
                        PlaySound(explosionSFX);
                    }

                    if (animIndex < 63)
                    {
                        Rectangle animDest = (Rectangle){plr->deathX, plr->deathY, 256, 256};
                        DrawAnimation(anim, animDest, (Vector2){128, 128});
                        animIndex++;
                    }
                    //Show retry screen once animation is done
                    else if (animIndex == 63 && rScreen->y > HEIGHT / 2)
                    {
                        rScreen->y -= 20;
                    }
                }

                //Drawing score counter onto the screen

                DrawTextEx(mainFont, to_string(score).c_str(), (Vector2){WIDTH / 2 - 20, 60.f + (float)(sin(GetTime() * 5) * 8)}, 64.f, 0.f, WHITE);
            }
            else if (gamePhase == 0)
            {
                if (sScreen->cooldown < 200)
                {
                    sScreen->SplashScreen(splashScreenFont, WIDTH, HEIGHT, (Vector2){WIDTH / 2 - 120, HEIGHT / 2 - 80 + (float)sin(GetTime() * 5) * 8});
                    sScreen->cooldown++;
                }
                else
                {
                    gamePhase = 1;
                }
            }

            //Drawing the retry screen (off screen at first)

            rScreen->Draw();
            rScreen->writeText(mainFont, "Game over!", (Vector2){rScreen->x - rScreen->Width / 2 + 170, rScreen->y - 200}, 64.f);
            rScreen->writeText(mainFont, "Score: ", (Vector2){rScreen->x - rScreen->Width / 2 + 170, rScreen->y - 50}, 64.f);
            rScreen->writeText(mainFont, to_string(score), (Vector2){rScreen->x - rScreen->Width / 2 + 450, rScreen->y - 50}, 64.f);
            rScreen->writeText(mainFont, "Press any key to retry", (Vector2){rScreen->x - rScreen->Width / 2 + 50, rScreen->y + 150}, 48.f);

        EndDrawing();
    }

    //Close window

    CloseWindow();

    return 0;
}