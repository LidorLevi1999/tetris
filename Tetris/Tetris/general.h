#ifndef __GENERAL_H
#define __GENERAL_H

// Function to set the console cursor position
void gotoxy(int x, int y);

// Function to clear the console screen
void clearScreen();

// Function to dynamically allocate a character matrix
char** buildCharMatrix(int rowsAndCols);

#endif