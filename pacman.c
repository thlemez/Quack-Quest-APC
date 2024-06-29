#include "raylib.h"
#include <stdbool.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define GRID_SIZE 25
#define NUM_GHOSTS 4
#define MAP_WIDTH (SCREEN_WIDTH / GRID_SIZE)
#define MAP_HEIGHT (SCREEN_HEIGHT / GRID_SIZE)

typedef enum { UP, DOWN, LEFT, RIGHT } Direction;

typedef struct {
    Vector2 position;
    Direction direction;
    float speed;
} Entity;

Entity pacman;
Entity ghosts[NUM_GHOSTS];
bool map[MAP_HEIGHT][MAP_WIDTH];
bool points[MAP_HEIGHT][MAP_WIDTH];
bool gameOver = false;
int score = 0;

void InitGame();
void UpdateGame();
void DrawGame();
bool CheckCollision(Vector2 position);
bool CheckCollisionWithGhosts(Vector2 position);
void MoveEntity(Entity *entity);
Direction GetRandomDirection();

int main(void)
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Pac-Man");
    InitGame();
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        if (!gameOver)
        {
            UpdateGame();
        }
        DrawGame();
    }

    CloseWindow();

    return 0;
}

void InitGame()
{
    pacman.position = (Vector2){ SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };
    pacman.direction = RIGHT;
    pacman.speed = 2.0f;

    for (int i = 0; i < NUM_GHOSTS; i++)
    {
        ghosts[i].position = (Vector2){ GetRandomValue(0, MAP_WIDTH - 1) * GRID_SIZE, GetRandomValue(0, MAP_HEIGHT - 1) * GRID_SIZE };
        ghosts[i].direction = GetRandomDirection();
        ghosts[i].speed = 1.5f;
    }

    // Initialize the map and points
    int labyrinth[MAP_HEIGHT][MAP_WIDTH] = {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1},
        {1, 0, 1, 1, 0, 1, 0, 0, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 0, 0, 1, 0, 1, 1, 1, 1, 0, 1, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1},
        {1, 0, 1, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 1, 1, 1, 1, 0, 1, 0, 0, 1, 0, 1, 1, 1, 1, 0, 1, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1},
        {1, 0, 1, 1, 0, 1, 0, 0, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 0, 0, 1, 0, 1, 1, 1, 1, 0, 1, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1},
        {1, 0, 1, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 1, 1, 1, 1, 0, 1, 0, 0, 1, 0, 1, 1, 1, 1, 0, 1, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1},
        {1, 0, 1, 1, 0, 1, 0, 0, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 0, 0, 1, 0, 1, 1, 1, 1, 0, 1, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1},
        {1, 0, 1, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 1, 1, 1, 1, 0, 1, 0, 0, 1, 0, 1, 1, 1, 1, 0, 1, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        
    };

    for (int y = 0; y < MAP_HEIGHT; y++)
    {
        for (int x = 0; x < MAP_WIDTH; x++)
        {
            map[y][x] = labyrinth[y][x] == 1;
            points[y][x] = labyrinth[y][x] == 0;
        }
    }
}

void UpdateGame()
{
    if (IsKeyDown(KEY_RIGHT)) pacman.direction = RIGHT;
    if (IsKeyDown(KEY_LEFT)) pacman.direction = LEFT;
    if (IsKeyDown(KEY_UP)) pacman.direction = UP;
    if (IsKeyDown(KEY_DOWN)) pacman.direction = DOWN;

    MoveEntity(&pacman);

    for (int i = 0; i < NUM_GHOSTS; i++)
    {
        if (GetRandomValue(0, 100) < 5) ghosts[i].direction = GetRandomDirection();
        MoveEntity(&ghosts[i]);
    }

    // Collect points
    int gridX = (int)(pacman.position.x / GRID_SIZE);
    int gridY = (int)(pacman.position.y / GRID_SIZE);
    if (points[gridY][gridX]) {
        points[gridY][gridX] = false;
        score++; // Incrementa a pontuação
    }

    // Check collision with ghosts
    if (CheckCollisionWithGhosts(pacman.position))
    {
        gameOver = true;
    }
}

void DrawGame()
{
    BeginDrawing();

    ClearBackground(BLACK);

    for (int y = 0; y < MAP_HEIGHT; y++)
    {
        for (int x = 0; x < MAP_WIDTH; x++)
        {
            if (map[y][x]) DrawRectangle(x * GRID_SIZE, y * GRID_SIZE, GRID_SIZE, GRID_SIZE, DARKBLUE);
            if (points[y][x]) DrawCircle(x * GRID_SIZE + GRID_SIZE / 2, y * GRID_SIZE + GRID_SIZE / 2, GRID_SIZE / 4, YELLOW);
        }
    }

    DrawCircleV(pacman.position, GRID_SIZE / 2, YELLOW);

    for (int i = 0; i < NUM_GHOSTS; i++)
    {
        DrawCircleV(ghosts[i].position, GRID_SIZE / 2, RED);
    }

    // Display score
    DrawText(TextFormat("Score: %04i", score), 10, 10, 20, WHITE);

    if (gameOver)
    {
        DrawText("GAME OVER", SCREEN_WIDTH / 2 - MeasureText("GAME OVER", 40) / 2, SCREEN_HEIGHT / 2 - 20, 40, RED);
    }

    EndDrawing();
}

bool CheckCollision(Vector2 position)
{
    int gridX = (int)(position.x / GRID_SIZE);
    int gridY = (int)(position.y / GRID_SIZE);
    if (gridX < 0 || gridX >= MAP_WIDTH || gridY < 0 || gridY >= MAP_HEIGHT) return true;
    return map[gridY][gridX];
}

bool CheckCollisionWithGhosts(Vector2 position)
{
    for (int i = 0; i < NUM_GHOSTS; i++)
    {
        if (CheckCollisionRecs((Rectangle){ position.x - GRID_SIZE / 2, position.y - GRID_SIZE / 2, GRID_SIZE, GRID_SIZE },
                               (Rectangle){ ghosts[i].position.x - GRID_SIZE / 2, ghosts[i].position.y - GRID_SIZE / 2, GRID_SIZE, GRID_SIZE }))
        {
            return true;
        }
    }
    return false;
}

void MoveEntity(Entity *entity)
{
    Vector2 newPos = entity->position;
    switch (entity->direction)
    {
        case RIGHT: newPos.x += entity->speed; break;
        case LEFT: newPos.x -= entity->speed; break;
        case UP: newPos.y -= entity->speed; break;
        case DOWN: newPos.y += entity->speed; break;
    }

    // Wrap around the screen edges
    if (newPos.x < 0) newPos.x = SCREEN_WIDTH - GRID_SIZE;
    if (newPos.x >= SCREEN_WIDTH) newPos.x = 0;
    if (newPos.y < 0) newPos.y = SCREEN_HEIGHT - GRID_SIZE;
    if (newPos.y >= SCREEN_HEIGHT) newPos.y = 0;

    if (!CheckCollision(newPos))
    {
        entity->position = newPos;
    }
}

Direction GetRandomDirection()
{
    return (Direction)GetRandomValue(0, 3);
}
