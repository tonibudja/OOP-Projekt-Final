#include "Snake.h"
#include <raymath.h>

Snake::Snake()
{
    body = { {6,9}, {5,9}, {4,9} };
    direction = { 1,0 };
    addSegment = false;
}

void Snake::Draw()
{
    for (auto& part : body)
    {
        Rectangle segment = {
            offset + part.x * cellSize,
            offset + part.y * cellSize,
            (float)cellSize,
            (float)cellSize
        };
        DrawRectangleRounded(segment, 0.75f, 6, DARKBLUE);
    }
}

void Snake::Update()
{
    if (addSegment)
    {
        body.push_front(Vector2Add(body[0], direction));
        addSegment = false;
    }
    else
    {
        body.pop_back();
        body.push_front(Vector2Add(body[0], direction));
    }
}

void Snake::Reset()
{
    body = { {6,9}, {5,9}, {4,9} };
    direction = { 1,0 };
}
