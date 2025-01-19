#include <iostream>
#include <raylib.h>
#include <deque>
#include <raymath.h>

using namespace std;

int main()
{
    // Initialization
    cout << "Starting the game.." << endl;
    InitWindow(1600, 900, "Snake Game");
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}