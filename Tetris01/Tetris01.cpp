// Tetris01.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <Windows.h>

using namespace std;

// The tetris pieces/shapes are called tetromino
wstring tetromino[7];

// The screen dimensions acting as the "game board"
int nFieldWidth = 12;
int nFieldHeight = 18;

// The actual field will be allocated with chars dynamically by the tetromino
unsigned char *pField = nullptr;

// The default value of windows command prompt
int nScreenWidth = 80;
int nScreenHeight = 30;

int Rotate(int px, int py, int r)
{
	switch (r % 4)
	{
		case 0: return py * 4 + px;				// 0 degree
		case 1: return 12 + py - (px * 4);		// 90 degrees
		case 2: return 15 - (py * 4) - px;		// 180 degrees
		case 3: return 3 - py + (px * 4);		// 270 degrees
	}
	return 0;
}

int main()
{
	// Create assets
	tetromino[0].append(L"..X.");
	tetromino[0].append(L"..X.");
	tetromino[0].append(L"..X.");
	tetromino[0].append(L"..X.");

	tetromino[1].append(L"..X.");
	tetromino[1].append(L".XX.");
	tetromino[1].append(L".X..");
	tetromino[1].append(L"....");

	tetromino[2].append(L".X..");
	tetromino[2].append(L".XX.");
	tetromino[2].append(L"..X.");
	tetromino[2].append(L"....");

	tetromino[3].append(L"....");
	tetromino[3].append(L".XX.");
	tetromino[3].append(L".XX.");
	tetromino[3].append(L"....");

	tetromino[4].append(L"..X.");
	tetromino[4].append(L".XX.");
	tetromino[4].append(L"..X.");
	tetromino[4].append(L"....");

	tetromino[5].append(L"....");
	tetromino[5].append(L".XX.");
	tetromino[5].append(L"..X.");
	tetromino[5].append(L"..X.");

	tetromino[6].append(L"....");
	tetromino[6].append(L".XX.");
	tetromino[6].append(L".X..");
	tetromino[6].append(L".X..");

	// Initialize the array for the playing field
	pField = new unsigned char[nFieldHeight * nFieldHeight];
	for (int i = 0; i < nFieldWidth; i++)
	{
		for (int j = 0; j < nFieldHeight; j++)
		{
			pField[j * nFieldWidth + i] = (i == 0 || i == nFieldWidth - 1 || j == nFieldHeight - 1) ? 9 : 0;		// 9 represents the border and 0 represents empty space
		}
	}

	wchar_t* screen = new wchar_t[nScreenWidth * nScreenHeight];
	for (int i = 0; i < nScreenWidth * nScreenHeight; i++)
		screen[i] = L' ';

	// Grab the handle to the console buffer
	HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	
	// Set the above handle as the active screen buffer
	// Now we need to use this instead of cout to print things to console
	// We have to use a separate command to draw to the buffer writeConsoleOutputCharacter
	SetConsoleActiveScreenBuffer(hConsole);
	DWORD dwBytesWritten = 0;

	bool bGameOver = false;

	// Main Game loop
	while (!bGameOver)
	{
		// GAME TIMING : not all processors are created equal. Manage game timing so it behaves the same on every computer

		// INPUT: handle the user input

		// GAME LOGIC: What happens at user input? Collision detection, shapes falling, scoring and so on

		// RENDER GAME OUTPUT: Display the game

		// Draw Field
		for (int i = 0; i < nFieldWidth; i++)
		{
			for (int j = 0; j < nFieldHeight; j++)
			{
				// Left side of assignment: offset the screen by 2 to make the boundry visible
				// Right side of assignment:
				// The string is an array. The 0th element is blank, and the following 7 will be used for tetromino.
				// Example: For tetromino 0, we will use A and tetromino 1 will use character B and so on.
				// = is for line and # for boundary.
				// pField[j * nFieldWidth + i] gives the value to be displayed on the screen array.
				screen[(j + 2) * nScreenWidth + (i + 2)] = L" ABCDEFG=#"[pField[j * nFieldWidth + i]];
			}
		}

		// Display Frame
		WriteConsoleOutputCharacter(hConsole, screen, nScreenWidth * nScreenHeight, { 0,0 }, &dwBytesWritten);
	}
	return 0;
}
