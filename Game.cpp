#include "Game.h"
#include "Utils.h"
#include <raymath.h>

Game::Game()
    : food(snake.body)
{
    score = 0;
    speed = 0.2;
    status = GameState::MENU;
}

void Game::Reset()
{
    snake.Reset();
    food.position = food.RandomPosition(snake.body);
    score = 0;
}

void Game::Update()
{
    if (status == GameState::MENU)
    {
        if (IsKeyPressed(KEY_UP))   speed -= 0.05;
        if (IsKeyPressed(KEY_DOWN)) speed += 0.05;

        if (speed < 0.05) speed = 0.05;
        if (speed > 0.5)  speed = 0.5;

        if (IsKeyPressed(KEY_SPACE))
        {
            Reset();
            status = GameState::PLAYING;
        }
        return;
    }

    if (status == GameState::GAME_OVER)
    {
        if (IsKeyPressed(KEY_SPACE))
        {
            status = GameState::MENU;
        }
        return;
    }

    if (eventTriggered(speed))
    {
        snake.Update();
        CheckCollisionWithFood();
        CheckCollisionWithEdges();
        CheckCollisionWithTail();
    }
}

void Game::Draw()
{
    int boardSize = cellSize * cellCount;
    int centerX = offset + boardSize / 2;


    if (status == GameState::MENU || status == GameState::GAME_OVER)
    {
        Rectangle panel = {
            (float)(offset + 80),
            (float)(offset + 80),
            (float)(boardSize - 160),
            (float)(boardSize - 160)
        };

        DrawRectangleRounded(
            { panel.x + 6, panel.y + 6, panel.width, panel.height },
            0.2f, 10, Fade(BLACK, 0.25f)
        );

        DrawRectangleRounded(panel, 0.2f, 10, RAYWHITE);
        DrawRectangleRoundedLines(panel, 0.2f, 10,DARKGREEN);

        int y = panel.y + 40;

        const char* title = "SNAKE";
        int titleSize = 48;
        int titleWidth = MeasureText(title, titleSize);
        DrawText(title, centerX - titleWidth / 2, y, titleSize, DARKGREEN);

        y += 70;

        if (status == GameState::GAME_OVER)
        {
            const char* go = "GAME OVER";
            int goSize = 32;
            int goWidth = MeasureText(go, goSize);
            DrawText(go, centerX - goWidth / 2, y, goSize, RED);
            y += 50;
        }

        DrawText("PRESS SPACE TO START",
            centerX - MeasureText("PRESS SPACE TO START", 22) / 2,
            y, 22, BLACK);
        y += 40;

        DrawText("UP    - INCREASE SPEED",
            centerX - MeasureText("UP    - INCREASE SPEED", 20) / 2,
            y, 20, DARKGRAY);
        y += 30;

        DrawText("DOWN  - DECREASE SPEED",
            centerX - MeasureText("DOWN  - DECREASE SPEED", 20) / 2,
            y, 20, DARKGRAY);
        y += 40;

        DrawText(TextFormat("SPEED: %.2f", speed),
            centerX - MeasureText("SPEED: 0.00", 20) / 2,
            y, 20, DARKGREEN);

        return;
    }

  
    food.Draw();
    snake.Draw();
}


void Game::CheckCollisionWithFood()
{
    if (Vector2Equals(snake.body[0], food.position))
    {
        food.position = food.RandomPosition(snake.body);
        snake.addSegment = true;
        score++;
    }
}

void Game::CheckCollisionWithEdges()
{
    if (snake.body[0].x < 0 || snake.body[0].x >= cellCount ||
        snake.body[0].y < 0 || snake.body[0].y >= cellCount)
    {
        status = GameState::GAME_OVER;
    }
}

void Game::CheckCollisionWithTail()
{
    auto body = snake.body;
    body.pop_front();
    if (elementInDeque(snake.body[0], body))
        status = GameState::GAME_OVER;
}
