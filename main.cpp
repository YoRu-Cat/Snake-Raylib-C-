#include <iostream>
#include <raylib.h>
#include <deque>
#include <raymath.h>

using namespace std;

Color bgColor1 = {58, 90, 64, 255};
Color bgColor = {88, 129, 87, 255};
Color dark = {52, 78, 65, 255};
Color light = {163, 177, 138, 255};

int cellSize = 25;
int cellCountHor = 64;
int cellCountVer = 36;

class Food
{
public:
	Vector2 position;
	Texture2D texture;
	Food()
	{
		Image img = LoadImage("Graphics/cherries.png");
		texture = LoadTextureFromImage(img);
		UnloadImage(img);
		position = GenRandomPos();
	}

	~Food()
	{
		UnloadTexture(texture);
	}
	void Draw()
	{
		DrawTexture(texture, position.x * cellSize, position.y * cellSize, WHITE);
	}
	Vector2 GenRandomPos()
	{
		float x = GetRandomValue(0, cellCountHor - 1);
		float y = GetRandomValue(0, cellCountVer - 1);
		return Vector2{x, y};
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