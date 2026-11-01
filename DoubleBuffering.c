#include <string.h>
#include <Windows.h>

// Console defines
#define CONSOLE_WIDTH 238
#define CONSOLE_HEIGHT 66

#define USE_DOUBLE_BUFFERING 1

// Inputs
#define GetKeyDown(keyCode) GetAsyncKeyState(keyCode) & 0x8000
#define GetKey(keyCode) GetAsyncKeyState(keyCode) & 0x8001
#define GetKeyUp(keyCode) GetAsyncKeyState(keyCode) & 0x0001

// Global variables
unsigned char screenIndex;

HANDLE screen[2];

// Square positions
unsigned short x;
unsigned short y;

// Flags
unsigned char quitEvent;

// Functions
void Init();
void Update();
void Render();
void Quit();

void CheckQuitProcess();

void MoveSquare();

void ScreenFlipping();
void ScreenClear();
void ScreenPrint(unsigned short x, unsigned short y, char* message);

int main(void)
{
	Init();
	
	while (!quitEvent)
	{
		Update();
		Sleep(10);
	}
	
	Quit();
	
	return 0;
}

void Init()
{
	// Full screen
	SendMessage(GetConsoleWindow(), WM_SYSKEYDOWN, VK_RETURN, 0x20000000);
	
	// Setup console
	system("title Double Buffering");
	
	// Screen setup
	CONSOLE_CURSOR_INFO consoleCursorInfo;
		
	consoleCursorInfo.bVisible = 0;
	consoleCursorInfo.dwSize = 1;
		
	if (USE_DOUBLE_BUFFERING)
	{
		screen[0] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
		screen[1] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
		
		SetConsoleCursorInfo(screen[0], &consoleCursorInfo);
		SetConsoleCursorInfo(screen[1], &consoleCursorInfo);
	}
	else
	{
		SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &consoleCursorInfo);
	}
}

void Update()
{
	CheckQuitProcess();
	ScreenClear();
	MoveSquare();
	Render();
	ScreenFlipping();
}

void Render()
{
	ScreenPrint(x, y, "бс");
	ScreenPrint(x + 2, y, "бс");
	ScreenPrint(x, y + 1, "бс");
	ScreenPrint(x, y - 1, "бс");
	ScreenPrint(x - 2, y, "бс");
}

void Quit()
{
	CloseHandle(screen[0]);
	CloseHandle(screen[1]);
}

void CheckQuitProcess()
{
	if (GetKeyDown(27))
	{
		quitEvent = 1;
	}
}

void MoveSquare()
{
	if ((GetKeyDown(87) || GetKeyDown(199)) && y - 1 >= 0)
	{
		y--;
	}
	if ((GetKeyDown(65) || GetKeyDown(97)) && x - 2 >= 0)
	{
		x -= 2;
	}
	if ((GetKeyDown(83) || GetKeyDown(195)) && y + 1 <= CONSOLE_HEIGHT)
	{
		y++;
	}
	if ((GetKeyDown(68) || GetKeyDown(100)) && x + 2 <= CONSOLE_WIDTH)
	{
		x += 2;
	}
}

void ScreenFlipping()
{
	if (!USE_DOUBLE_BUFFERING)
	{
		return;
	}
	
	SetConsoleActiveScreenBuffer(screen[screenIndex]);
	
	screenIndex = !screenIndex;
}

void ScreenClear()
{
	COORD coord = { 0, 0 };
	DWORD dw;
	
	FillConsoleOutputCharacter(USE_DOUBLE_BUFFERING ? screen[screenIndex] : GetStdHandle(STD_OUTPUT_HANDLE), ' ', (CONSOLE_WIDTH + 2) * (CONSOLE_HEIGHT + 1), coord, &dw);
}

void ScreenPrint(unsigned short x, unsigned short y, char* message)
{
	COORD position = { x, y };
	DWORD dw;
	
	SetConsoleCursorPosition(USE_DOUBLE_BUFFERING ? screen[screenIndex] : GetStdHandle(STD_OUTPUT_HANDLE), position);
	WriteFile(USE_DOUBLE_BUFFERING ? screen[screenIndex] : GetStdHandle(STD_OUTPUT_HANDLE), message, strlen(message), &dw, NULL);
}
