// Implementation file for the Point class.

#include "point.h"
#include "general.h"
#include <iostream>
#include <Windows.h>
using namespace std;

// Constructor
Point::Point(int x, int y, char symbol, int color) {
	this->x = x;
	this->y = y;
	this->symbol = symbol;
	this->color = color;
	diff_x = 0;
	diff_y = 1;
}

// Function to set the coordinates of the point and optionally draw it
void Point::setCoordinates(int x, int y, bool shouldDraw) {
	if (shouldDraw) {
		draw(GameConfig::COLORS[0], ' ');
		this->x = x;
		this->y = y;
		//TODO : change below to the point color
		draw(BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED, ' ');
	}
	else {
		this->x = x;
		this->y = y;
	}
}

// Function to draw the point with a background color
void Point::draw(int backcolor) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GameConfig::COLORS[0]);
	gotoxy(this->x + GameConfig::MIN_X - 1, this->y + GameConfig::MIN_Y - 1);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), this->color);
	cout << this->symbol;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GameConfig::COLORS[0]);
}

// Function to draw the point with a background color and a specific symbol
void Point::draw(int backcolor, char symbol)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GameConfig::COLORS[0]);
	gotoxy(this->x + GameConfig::MIN_X - 1, this->y + GameConfig::MIN_Y - 1);
	cout << symbol;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GameConfig::COLORS[0]);
}

// Function to set the move direction of the point based on the input key and get the next position
Point Point::setMoveDirectionAndGetNext(GameConfig::eKeys key) {
	switch (key) {
	case GameConfig::eKeys::LEFTP1:
	case GameConfig::eKeys::LEFTP2:
		this->diff_x = -1;
		this->diff_y = 0;
		break;
	case GameConfig::eKeys::RIGHTP1:
	case GameConfig::eKeys::RIGHTP2:
		this->diff_x = 1;
		this->diff_y = 0;
		break;
	case GameConfig::eKeys::DROPP1:
	case GameConfig::eKeys::DROPP2:
		this->diff_x = 0;
		this->diff_y = 1;
		break;
	}
	// Return the next position
	return Point{ this->x + diff_x, this->y + diff_y, this->symbol, this->color };
}

// Function to move the point based on the setMoveDirection response
void Point::move(GameConfig::eKeys key, bool shouldDraw)
{
	Point nextPos = this->setMoveDirectionAndGetNext(key);
	setCoordinates(nextPos.x,nextPos.y, shouldDraw);
}
