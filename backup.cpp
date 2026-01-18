#include <iostream>
#include <raylib.h>
#include <ctime>
#include <cstdlib>
#include <deque>
#include <raymath.h>


Color lightGreen = { 170, 200, 90, 255 };
Color darkishGreen = { 150, 180, 80, 255 };


int cellSize = 30;
int cellCount = 25;

int offset = 58;

double lastUpdateTime = 0;

bool elementInDeque(Vector2 element, std::deque<Vector2> deque)
{
    for (unsigned int i = 0; i < deque.size(); i++)
    {
        if (Vector2Equals(deque[i], element))
        {
            return true;
        }
    }

    return false;
}

bool eventTriggered(double interval)
{
    double currentTime = GetTime();
    if (currentTime - lastUpdateTime >= interval)
    {
        lastUpdateTime = currentTime;
        return 1;
    }
    else
        return 0;

}

class Snake
{
public:
    std::deque<Vector2> body = {
        Vector2{6,9},
        Vector2{5,9},
        Vector2{4,9}
    };

    Vector2 direction = { 1,0 }; //desno

    bool addSegment = false;

    void Draw()
    {
        for (unsigned i = 0; i < body.size(); i++)
        {
            float x = body[i].x;
            float y = body[i].y;

            Rectangle segment = Rectangle{ offset + x * cellSize,offset + y * cellSize,static_cast<float>(cellSize),static_cast<float>(cellSize) };

            DrawRectangleRounded(segment, 0.75, 6, DARKBLUE);
        }
    }

    void Update()
    {
        if (addSegment == true)
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

    void Reset()
    {
        body = { Vector2{6,9},Vector2{5,9},Vector2{4,9} };
        direction = { 1,0 };
    }
};

class Food {
public:
    Vector2 position;
    Texture2D texture;

    Food(std::deque<Vector2> snakeBody) {
        Image image = LoadImage("apple.png");
        texture = LoadTextureFromImage(image);
        if (!IsImageValid(image))
        {
            std::cout << "Nije ucitana";
        }
        UnloadImage(image);

        position = RandomPosition(snakeBody);

    }

    void Draw() {
        Rectangle source = {
            0,0,
            (float)texture.width,
            (float)texture.height
        };

        Rectangle dest = {
            offset + position.x * cellSize,
            offset + position.y * cellSize,
            (float)cellSize,
            (float)cellSize
        };

        Vector2 origin = { 0,0 };

        DrawTexturePro(texture, source, dest, origin, 0.0f, WHITE);
    }

    Vector2 GenerateRandomCell()
    {
        int x = rand() % cellCount;
        int y = rand() % cellCount;

        return Vector2{ (float)x,(float)y };
    }

    Vector2 RandomPosition(std::deque<Vector2> snakeBody)
    {
        int x = rand() % cellCount;
        int y = rand() % cellCount;

        Vector2 position = GenerateRandomCell();

        while (elementInDeque(position, snakeBody))
        {
            position = GenerateRandomCell();
        }

        return position;

    }

    ~Food() {
        UnloadTexture(texture);
    }
private:
};

class Game
{
public:
    Snake snake = Snake();
    Food food = Food(snake.body);

    bool GameRunning = true;

    int score = 0;

    void Draw()
    {
        food.Draw();
        snake.Draw();
    }

    void Update()
    {
        if (GameRunning)
        {
            snake.Update();
            CheckCollisionWithFood();
            CheckCollisionWithEdges();
            CheckCollisionWithTail();
        }
    }



    void CheckCollisionWithFood()
    {
        if (Vector2Equals(snake.body[0], food.position))
        {
            food.position = food.RandomPosition(snake.body);
            snake.addSegment = true;
            score++;
        }
    }

    void CheckCollisionWithEdges()
    {
        if (snake.body[0].x == cellCount || snake.body[0].x == -1)
        {
            GameOver();
        }

        if (snake.body[0].y == cellCount || snake.body[0].y == -1)
        {
            GameOver();
        }
    }

    void GameOver()
    {
        snake.Reset();
        food.position = food.RandomPosition(snake.body);
        GameRunning = false;
        score = 0;
    }

    void CheckCollisionWithTail()
    {
        std::deque<Vector2> headlessBody = snake.body;
        headlessBody.pop_front();

        if (elementInDeque(snake.body[0], headlessBody))
        {
            GameOver();
        }
    }
};

int main()
{
    std::cout << "Pokretanje igre..." << '\n';
    InitWindow(2 * offset + cellSize * cellCount, 2 * offset + cellSize * cellCount, "Snake - OOP");

    SetTargetFPS(60);

    srand((unsigned int)time(NULL));

    Game game = Game();

    while (!WindowShouldClose())
    {
        BeginDrawing();

        if (eventTriggered(0.2))
        {
            game.Update();
        }

        if (IsKeyPressed(KEY_UP) && game.snake.direction.y != 1)
        {
            game.snake.direction = { 0,-1 };
            game.GameRunning = true;
        }

        if (IsKeyPressed(KEY_DOWN) && game.snake.direction.y != -1)
        {
            game.snake.direction = { 0,1 };
            game.GameRunning = true;
        }

        if (IsKeyPressed(KEY_LEFT) && game.snake.direction.x != 1)
        {
            game.snake.direction = { -1,0 };
            game.GameRunning = true;
        }

        if (IsKeyPressed(KEY_RIGHT) && game.snake.direction.x != -1)
        {
            game.snake.direction = { 1,0 };
            game.GameRunning = true;
        }



        for (int y = 0; y < cellCount; y++)
        {
            for (int x = 0; x < cellCount; x++)
            {
                Color cellColor = ((x + y) % 2 == 0) ? lightGreen : darkishGreen;

                DrawRectangle(
                    offset + x * cellSize,
                    offset + y * cellSize,
                    cellSize,
                    cellSize,
                    cellColor
                );
            }
        }
        ClearBackground(lightGreen);
        DrawRectangleLinesEx(Rectangle{ (float)offset - 5,(float)offset - 5,(float)cellSize * cellCount + 10,(float)cellSize * cellCount + 10 }, 5, DARKGREEN);
        DrawText("Snake", offset - 5, 20, 35, DARKGREEN);
        DrawText(TextFormat("%i", game.score), offset - 5, offset + cellSize * cellCount + 10, 35, DARKGREEN);
        game.Draw();

        EndDrawing();
    }
    CloseWindow();

    return 0;
}