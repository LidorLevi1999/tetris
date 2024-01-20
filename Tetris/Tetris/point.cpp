#include "point.h"
#include "general.h"

#include <iostream>
#include <Windows.h>
using namespace std;


//Constructor;
Point::Point(int x, int y, char symbol, int color) {
	this->x = x;
	this->y = y;
	this->symbol = symbol;
	this->color = color;
	diff_x = 0;
	diff_y = 1;

}


void Point::setCoordinates(int x, int y, bool shouldDraw) {
	if(shouldDraw)
		draw(GameConfig::COLORS[0], ' ');
	this->x = x;
	this->y = y;
	if (shouldDraw) {
		//TODO : change below to the point color
		draw(BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED, ' ');
	}

}


//Draw the point with the symbol assigned at the constructor;
void Point::draw(int backcolor) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GameConfig::COLORS[0]);
	gotoxy(this->x + GameConfig::MIN_X - 1, this->y + GameConfig::MIN_Y - 1);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), this->color);
	cout << this->symbol;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GameConfig::COLORS[0]);
}


//Draw the point with the symbol given, mainly used for whitespaces;
void Point::draw(int backcolor, char symbol)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GameConfig::COLORS[0]);
	gotoxy(this->x + GameConfig::MIN_X - 1, this->y + GameConfig::MIN_Y - 1);
	cout << symbol;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GameConfig::COLORS[0]);
}


//Set the move direction of the point to x, y axises based on the input, returns false if couldn't move.
//TODO : decide if validation should be here or on the BOARD class.
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
	//return (this->diff_x != 0 || this->diff_y != 0);
}


//Moves the point based on the setMoveDirection response, 
//Not moving out of bounds of the game width and height
//TODO : deciede if validation should be here or on the BOARD class.
void Point::move(GameConfig::eKeys key, bool shouldDraw)
{
	// Get the next position
	Point nextPos = this->setMoveDirectionAndGetNext(key);
	setCoordinates(nextPos.x,nextPos.y, shouldDraw);
}
