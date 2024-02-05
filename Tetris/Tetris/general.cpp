#include "general.h"
#include <windows.h>
#include <process.h>
#include <iostream>


// Function to set the console cursor position
void gotoxy(int x, int y){
	HANDLE hConsoleOutput;
	COORD dwCursorPosition;
	std::cout.flush();
	dwCursorPosition.X = x;
	dwCursorPosition.Y = y;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput, dwCursorPosition);
}

// Function to clear the console screen
void clearScreen(){
	system("cls");
}

