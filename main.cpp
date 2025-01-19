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

double lastFrameTime = 0;
bool eventHappened(double inter)
{
	double currentTime = GetTime();
	if (currentTime - lastFrameTime >= inter)
	{
		lastFrameTime = currentTime;
		return true;
	}
	return false;
}
class Snake
{
public:
	deque<Vector2> body = {Vector2{6, 9}, Vector2{5, 9}, Vector2{4, 9}};
	Vector2 direction = {1, 0};
	void Draw()
	{
		for (unsigned int i = 0; i < body.size(); i++)
		{
			float x = body[i].x * cellSize;
			float y = body[i].y * cellSize;
			Rectangle rec = Rectangle{x, y, (float)cellSize, (float)cellSize};
			DrawRectangleRounded(rec, 0.5, 10, i % 2 == 0 ? dark : light);
		}
	}
	void Move()
	{
		body.pop_back();
		body.push_front(Vector2Add(body[0], direction));
	}
};
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

class Game
{
public:
	Snake snake = Snake();
	Food food = Food();

	void Draw()
	{
		ClearBackground(bgColor);
		food.Draw();
		snake.Draw();
	}

	void Move()
	{
		snake.Move();
	}

	void UpdateDirection(Snake &snake)
	{
		if (IsKeyPressed(KEY_UP) && snake.direction.y != 1)
		{
			SetDirection(snake, {0, -1});
		}
		else if (IsKeyPressed(KEY_DOWN) && snake.direction.y != -1)
		{
			SetDirection(snake, {0, 1});
		}
		else if (IsKeyPressed(KEY_LEFT) && snake.direction.x != 1)
		{
			SetDirection(snake, {-1, 0});
		}
		else if (IsKeyPressed(KEY_RIGHT) && snake.direction.x != -1)
		{
			SetDirection(snake, {1, 0});
		}
	}

	void SetDirection(Snake &snake, Vector2 newDir)
	{
		Vector2 newHead = Vector2Add(snake.body[0], newDir);
		bool collision = false;
		for (unsigned int i = 1; i < snake.body.size(); i++)
		{
			if (Vector2Equals(newHead, snake.body[i]))
			{
				collision = true;
				break;
			}
		}
		if (!collision)
			snake.direction = newDir;
	}
};
int main()
{
	// Initialization
	cout << "Starting the game.." << endl;
	InitWindow(cellSize * cellCountHor, cellSize * cellCountVer, "Snake Game");
	SetTargetFPS(60);
	Game game = Game();
	while (!WindowShouldClose())
	{
		BeginDrawing();
		if (eventHappened(0.2))
		{
			game.Move();
		}
		game.UpdateDirection(game.snake);
		game.Draw();
		EndDrawing();
	}

	CloseWindow();
	return 0;
}
