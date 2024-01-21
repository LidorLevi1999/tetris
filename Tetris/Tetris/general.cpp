#include "general.h"
#include <windows.h>
#include <process.h>
#include <iostream>
using namespace std;

// Function to set the console cursor position
void gotoxy(int x, int y){
	HANDLE hConsoleOutput;
	COORD dwCursorPosition;
	cout.flush();
	dwCursorPosition.X = x;
	dwCursorPosition.Y = y;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput, dwCursorPosition);
}

// Function to clear the console screen
void clearScreen(){
	system("cls");
}

// Function to dynamically allocate a character matrix
char** buildCharMatrix(int rowsAndCols) {
	char** matrix = new char* [rowsAndCols];
	for (int i = 0; i < rowsAndCols; ++i) {
		matrix[i] = new char[rowsAndCols];
		for (int j = 0; j < rowsAndCols; ++j)
			matrix[i][j] = ' ';
	}
	return matrix;
}