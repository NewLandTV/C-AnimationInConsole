#include <stdio.h>
#include <Windows.h>

#define CONSOLE_WIDTH 32
#define CONSOLE_HEIGHT 9

int carXPosition;
int carYPosition;
const char* carSprite[3] = { " ┌───┐",
							 "┌┘   └┐",
							 "└●─●┘" };

void Init();
void Update();
void Gotoxy(int x, int y);

int main(void)
{
	Init();
	
	while (1)
	{
		Update();
	}
	
	return 0;
}

void Init()
{
	system("title Animation");
	system("mode con cols=32 lines=9");
	
	CONSOLE_CURSOR_INFO consoleCursorInfo;
	
	consoleCursorInfo.bVisible = 0;
	consoleCursorInfo.dwSize = 1;
	
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &consoleCursorInfo);
	
	carXPosition = 0;
	carYPosition = CONSOLE_HEIGHT >> 1;
}

void Update()
{
	int i;
	
	if (carXPosition + 6 < CONSOLE_WIDTH)
	{
		for (i = 0; i < 3; i++)
		{
			Gotoxy(carXPosition, carYPosition + i - 1);
			printf("     ");
			Gotoxy(carXPosition, carYPosition + i - 1);
			printf("%s", carSprite[i]);
		}
		
		carXPosition++;
	}
	else
	{
		for (i = 0; i < 3; i++)
		{
			Gotoxy(carXPosition, carYPosition + i - 1);
			printf("      ");
		}
		
		carXPosition = 0;
	}
	
	Sleep(200);
}

void Gotoxy(int x, int y)
{
	COORD position = { x, y };
	
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
}
