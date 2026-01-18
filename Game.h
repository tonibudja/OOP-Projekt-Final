#pragma once
#include "Snake.h"
#include "Food.h"

enum class GameState
{
    MENU,
    PLAYING,
    GAME_OVER
};

class Game
{
public:
    Snake snake;
    Food food;

    int score;
    double speed;

    Game();

    void Update();
    void Draw();
    void Reset();

    GameState status;

private:
    void CheckCollisionWithFood();
    void CheckCollisionWithEdges();
    void CheckCollisionWithTail();
};
