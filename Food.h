#pragma once
#include <deque>
#include <raylib.h>

extern int cellSize;
extern int cellCount;
extern int offset;

class Food
{
public:
    Vector2 position;
    Texture2D texture;

    Food(const std::deque<Vector2>& snakeBody);
    ~Food();

    void Draw();
    Vector2 RandomPosition(const std::deque<Vector2>& snakeBody);

private:
    Vector2 GenerateRandomCell();
};
