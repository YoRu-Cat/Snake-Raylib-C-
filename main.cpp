#include <iostream>
#include <raylib.h>
#include <deque>
#include <raymath.h>

using namespace std;

Color bgColor1 = {58, 90, 64, 255};
Color bgColor = {88, 129, 87, 255};
Color dark = {52, 78, 65, 255};
Color light = {163, 177, 138, 255};

int cellSize = 30;
int cellCountHor = 40;
int cellCountVer = 25;
int offset = 50;

double lastFrameTime = 0;
double speed = 0.15;

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

bool ElemInDeque(Vector2 elem, deque<Vector2> deq)
{
	for (unsigned int i = 0; i < deq.size(); i++)
	{
		if (Vector2Equals(elem, deq[i]))
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
			Rectangle rec = Rectangle{offset + x, offset + y, (float)cellSize, (float)cellSize};
			DrawRectangleRounded(rec, 0.5, 10, i % 2 == 0 ? dark : bgColor1);
		}
	}
	void Move()
	{
		body.pop_back();
		body.push_front(Vector2Add(body[0], direction));
	}
	void reset()
	{
		body = {Vector2{6, 9}, Vector2{5, 9}, Vector2{4, 9}};
		direction = {1, 0};
	}
};
class Food
{
public:
	Vector2 position;
	Texture2D texture;
	Food(deque<Vector2> snakeBody)
	{
		Image img = LoadImage("Graphics/Food.png");
		texture = LoadTextureFromImage(img);
		UnloadImage(img);
		position = GenRandomPos(snakeBody);
	}

	~Food()
	{
		UnloadTexture(texture);
	}
	void Draw()
	{
		DrawTexture(texture, position.x * cellSize + offset, position.y * cellSize + offset, WHITE);
	}
	Vector2 GenRandomCell()
	{
		float x = GetRandomValue(0, cellCountHor - 1);
		float y = GetRandomValue(0, cellCountVer - 1);
		Vector2 pos = {x, y};
		return pos;
	}
	Vector2 GenRandomPos(deque<Vector2> snakeBody)
	{
		Vector2 pos = GenRandomCell();
		while (ElemInDeque(pos, snakeBody))
		{
			pos = GenRandomCell();
		}
		return pos;
	}
};

class Game
{
public:
	Snake snake = Snake();
	Food food = Food(snake.body);
	bool running = true;
	int score = 0;
	void Draw()
	{
		ClearBackground(bgColor);
		food.Draw();
		snake.Draw();
	}

	void Move()
	{
		if (!running)
			return;
		snake.Move();
		Eat();
		GameOver();
		CollisionTail();
	}

	void UpdateDirection(Snake &snake)
	{
		if (IsKeyPressed(KEY_UP) && snake.direction.y != 1)
		{
			SetDirection(snake, {0, -1});
			running = true;
		}
		else if (IsKeyPressed(KEY_DOWN) && snake.direction.y != -1)
		{
			SetDirection(snake, {0, 1});
			running = true;
		}
		else if (IsKeyPressed(KEY_LEFT) && snake.direction.x != 1)
		{
			SetDirection(snake, {-1, 0});
			running = true;
		}
		else if (IsKeyPressed(KEY_RIGHT) && snake.direction.x != -1)
		{
			SetDirection(snake, {1, 0});
			running = true;
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

	void Eat()
	{
		if (Vector2Equals(snake.body[0], food.position))
		{
			snake.body.push_back(snake.body[snake.body.size() - 1]);
			if (speed > 0.05)
				speed /= 1.05;
			food.position = food.GenRandomPos(snake.body);
			score++;
		}
	}

	void GameOver()
	{
		if (snake.body[0].x < 0 || snake.body[0].x >= cellCountHor || snake.body[0].y < 0 || snake.body[0].y >= cellCountVer)
		{
			gameOver();
		}
	}

	void gameOver()
	{
		snake.reset();
		food.position = food.GenRandomPos(snake.body);
		speed = 0.15;
		running = false;
		score = 0;
	}

	void CollisionTail()
	{
		deque<Vector2> body = snake.body;
		body.pop_front();
		if (ElemInDeque(snake.body[0], body))
		{
			gameOver();
		}
	}
};
int main()
{
	// Initialization
	cout << "Starting the game.." << endl;
	InitWindow(2 * offset + cellSize * cellCountHor, 2 * offset + cellSize * cellCountVer, "Snake Game");
	SetTargetFPS(60);
	Game game = Game();
	while (!WindowShouldClose())
	{
		BeginDrawing();
		if (eventHappened(speed))
		{
			game.Move();
		}
		game.UpdateDirection(game.snake);
		DrawRectangleLinesEx(Rectangle{(float)offset - 5, (float)offset - 5, (float)cellSize * cellCountHor + 10, (float)cellSize * cellCountVer + 10}, 5, dark);
		DrawText("Snake Raylib By YoRu", offset - 5, 10, 30, light);
		DrawText(TextFormat("Score : %i", game.score), offset - 5, cellSize * cellCountVer + 10 + offset, 30, light);
		game.Draw();
		EndDrawing();
	}

	CloseWindow();
	return 0;
}
