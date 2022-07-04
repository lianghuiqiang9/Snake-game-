#include<Windows.h>
#include<stdio.h>
#include<time.h>
#include<conio.h>
#define Width 52//4的倍数
#define High 18
#define Snakesize 1922

int changeflag = 0, sorce = 0, key = 77;

struct {
	int x; int y;
}food;

class Snake{
public:
	int speed;
	int len;
	int x[Snakesize], y[Snakesize];
	Snake();
}snake;
Snake::Snake(void) {
	len = 3; speed = 200;
	x[0] = Width / 2; y[0] = High / 2;
//	gotoxy(x[0], y[0]);	printf("\033[34m■\033[0m");
}

void gotoxy(int x, int y);
void drawmap();
void keydown();
void createfood();
bool snakestatus();
void keydown() {
	gotoxy(food.x, food.y); printf("\033[31m■\033[0m");
	int pre_key = key;
	if (_kbhit()) {
		fflush(stdin);
		key = _getch(); //printf("%d", key);
		key = _getch(); //printf("%d", key);
	}
	//printf("%d", key);
	if (changeflag == 0) {
		gotoxy(snake.x[snake.len - 1], snake.y[snake.len - 1]); printf("  ");
		gotoxy(snake.x[0], snake.y[0]); printf("\033[34m■\033[0m");
	}
	for (int i = snake.len - 1; i > 0; i--) {
		snake.x[i] = snake.x[i - 1];
		snake.y[i] = snake.y[i - 1];
	}
	if (pre_key == 72 && key == 80)
		key = 72;
	if (pre_key == 80 && key == 72)
		key = 80;
	if (pre_key == 75 && key == 77)
		key = 75;
	if (pre_key == 77 && key == 75)
		key = 77;
	switch (key) {
	case 75: snake.x[0] -= 2; break;
	case 77: snake.x[0] += 2; break;
	case 72: snake.y[0]--; break;
	case 80: snake.y[0]++; break;
	}
	gotoxy(snake.x[0], snake.y[0]); printf("\033[33m■\033[0m");
	gotoxy(0, High+1);
	changeflag = 0;
}
void createfood() {
	if (snake.x[0] == food.x && snake.y[0] == food.y) {
		gotoxy(food.x, food.y); printf("\033[34m■\033[0m");
		while (1) {
			int flag = 1;
			srand((unsigned int)time(NULL));
			food.x = rand() * 2 % (Width - 4) + 2;
			food.y = rand() % (High - 2) + 1;
			for (int i = 0; i < snake.len; i++) {
				if (snake.x[i] == food.x && snake.y[i] == food.y) {
					flag = 0; break;
				}
			}
			if (flag && food.x % 2 == 0)
				break;
		}
	//	gotoxy(food.x, food.y); printf("\033[31m■\033[0m");
		snake.len++;
		sorce += 10;
		snake.speed -= 5;
		changeflag = 1;
	}
}
bool snakestatus() {
	if (snake.y[0] == 0 || snake.y[0] == High)
		return false;
	if (snake.x[0] == 0 || snake.x[0] == Width)
		return false;
	for (int i = 1; i < snake.len; i++) {
		if (snake.x[i] == snake.x[0] && snake.y[i] == snake.y[0])
			return false;
	}
	return true;
}
void gotoxy(int x, int y) {
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void drawmap() {
	for (int i = 0; i <= Width; i += 2) {
		gotoxy(i, 0); printf("■");
		gotoxy(i, High); printf("■");
	}
	for (int i = 1; i < High; i++) {
		gotoxy(0, i); printf("■");
		gotoxy(Width, i); printf("■");
	}
	srand((unsigned int)time(NULL));
	food.x = rand() * 2 % (Width - 4) + 2;
	food.y = rand() % (High - 2) + 1;
	
	gotoxy(snake.x[0], snake.y[0]); printf("\033[33m■\033[0m");
	for (int i = 1; i < snake.len; i++) {
		snake.x[i] = snake.x[i - 1] - 2;
		snake.y[i] = snake.y[i - 1];
		gotoxy(snake.x[i], snake.y[i]); printf("\033[34m■\033[0m");
	}
}
void main() {
	drawmap();
	while (1) {
		keydown();	Sleep(snake.speed);
		if (!snakestatus()||snake.len==Snakesize)
			break;
		createfood();
	}
	if (snake.len == Snakesize) {
		gotoxy(Width / 2-8, High / 2-1); printf("You Win!!!\n");
		gotoxy(Width / 2-8, High / 2); printf("本次游戏得分为：%d", sorce);
	}
	else {
		gotoxy(Width / 2-8, High / 2-1); printf("Game Over!\n");
		gotoxy(Width / 2-8, High / 2); printf("本次游戏得分为：%d", sorce);
	}
	gotoxy(0, High+1);
	Sleep(5000);
}
