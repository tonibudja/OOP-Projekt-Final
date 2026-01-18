#pragma once
#include <deque>
#include <raylib.h>

extern int cellSize;
extern int offset;

class Snake
{
public:
    std::deque<Vector2> body;
    Vector2 direction;
    bool addSegment;

    Snake();

    void Draw();
    void Update();
    void Reset();
};
