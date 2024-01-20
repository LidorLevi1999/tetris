#include "general.h"
#include <windows.h> // for gotoxy
#include <process.h> // for system
#include <iostream>
using namespace std;


void gotoxy(int x, int y){
	HANDLE hConsoleOutput;
	COORD dwCursorPosition;
	cout.flush();
	dwCursorPosition.X = x;
	dwCursorPosition.Y = y;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput, dwCursorPosition);
}


void clearScreen(){
	system("cls");
}


char** buildCharMatrix(int rowsAndCols) {
	char** matrix = new char* [rowsAndCols];
	for (int i = 0; i < rowsAndCols; ++i) {
		matrix[i] = new char[rowsAndCols];
		for (int j = 0; j < rowsAndCols; ++j)
			matrix[i][j] = ' ';
	}
	return matrix;
}