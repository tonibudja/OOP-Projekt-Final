#include "Food.h"
#include "Utils.h"
#include <cstdlib>
#include <iostream>

Food::Food(const std::deque<Vector2>& snakeBody)
{
    Image image = LoadImage("apple.png");
    texture = LoadTextureFromImage(image);
    UnloadImage(image);

    position = RandomPosition(snakeBody);
}

Food::~Food()
{
    UnloadTexture(texture);
}

void Food::Draw()
{
    Rectangle dest = {
        offset + position.x * cellSize,
        offset + position.y * cellSize,
        (float)cellSize,
        (float)cellSize
    };

    DrawTexturePro(
        texture,
        { 0, 0, (float)texture.width, (float)texture.height },
        dest,
        { 0, 0 },
        0.0f,
        WHITE
    );
}

Vector2 Food::GenerateRandomCell()
{
    int x = rand() % cellCount;
    int y = rand() % cellCount;
    return { (float)x, (float)y };
}

Vector2 Food::RandomPosition(const std::deque<Vector2>& snakeBody)
{
    Vector2 pos = GenerateRandomCell();
    while (elementInDeque(pos, snakeBody))
        pos = GenerateRandomCell();

    return pos;
}
