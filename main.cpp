#include <iostream>
#include <raylib.h>
#include <deque>
#include <raymath.h>

using namespace std;

Color bgColor = {58, 90, 64, 255};
Color dark = {52, 78, 65, 255};
Color light = {163, 177, 138, 255};

int cellSize = 25;
int cellCountHor = 64;
int cellCountVer = 36;

class Food
{
public:
	Vector2 position = {5, 6};
	void Draw()
	{
		DrawRectangle(position.x * cellSize, position.y * cellSize, cellSize, cellSize, light);
	}
};

int main()
{
	// Initialization
	cout << "Starting the game.." << endl;
	InitWindow(cellSize * cellCountHor, cellSize * cellCountVer, "Snake Game");
	SetTargetFPS(60);

	Food food = Food();

	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(bgColor);
		food.Draw();
		EndDrawing();
	}

	CloseWindow();
	return 0;
}