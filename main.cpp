#include <raylib.h>
#include <ctime>
#include "Game.h"
#include "Utils.h"

Color lightGreen = { 170, 200, 90, 255 };
Color darkishGreen = { 150, 180, 80, 255 };

int cellSize = 30;
int cellCount = 25;
int offset = 58;

int main()
{
    InitWindow(2 * offset + cellSize * cellCount,
        2 * offset + cellSize * cellCount,
        "Snake - OOP");

    SetTargetFPS(60);
    srand((unsigned int)time(nullptr));

    Game game;

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(lightGreen);

        game.Update();

        if (IsKeyPressed(KEY_UP) && game.snake.direction.y != 1)
            game.snake.direction = { 0, -1 };
        if (IsKeyPressed(KEY_DOWN) && game.snake.direction.y != -1)
            game.snake.direction = { 0, 1 };
        if (IsKeyPressed(KEY_LEFT) && game.snake.direction.x != 1)
            game.snake.direction = { -1, 0 };
        if (IsKeyPressed(KEY_RIGHT) && game.snake.direction.x != -1)
            game.snake.direction = { 1, 0 };

        for (int y = 0; y < cellCount; y++)
            for (int x = 0; x < cellCount; x++)
                DrawRectangle(offset + x * cellSize,
                    offset + y * cellSize,
                    cellSize, cellSize,
                    ((x + y) % 2 == 0) ? lightGreen : darkishGreen);

        DrawRectangleLinesEx(
            { (float)offset - 5, (float)offset - 5,
             (float)cellSize * cellCount + 10,
             (float)cellSize * cellCount + 10 },
            5, DARKGREEN);

        DrawText("Snake", offset, offset - 40, 30, DARKGREEN);

        DrawText(TextFormat("Score: %i", game.score),
            offset, offset + cellSize * cellCount + 20,
            30, DARKGREEN);

        game.Draw();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
