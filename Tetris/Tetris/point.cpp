#include "point.h"
#include "general.h"

#include <iostream>
#include <Windows.h>
using namespace std;

//Constructor;
Point::Point(int x, int y, char symbol)
{
	this->x = x;
	this->y = y;
	this->symbol = symbol;
	diff_x = 0;
	diff_y = 1;
}


//Draw the point with the symbol assigned at the constructor;
void Point::draw(int backcolor)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), backcolor);
	gotoxy(x + GameConfig::MIN_X - 1, y + GameConfig::MIN_Y - 1);
	cout << this->symbol;
}


//Draw the point with the symbol given, mainly used for whitespaces;
void Point::draw(int backcolor, char symbol)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), backcolor);
	gotoxy(x + GameConfig::MIN_X - 1, y + GameConfig::MIN_Y - 1);
	cout << symbol;
}


//Set the move direction of the point to x, y axises based on the input, returns false if couldn't move.
//TODO : decide if validation should be here or on the BOARD class.
bool Point::setMoveDirection(GameConfig::eKeys key) {
	switch (key){
	case GameConfig::eKeys::LEFTP1:
		this->diff_x = this->x == 1 ? 0 : -1;
		this->diff_y = 0;
		break;
	case GameConfig::eKeys::RIGHTP1:
		this->diff_x = this->x == GameConfig::GAME_WIDTH ? 0 : 1;
		this->diff_y = 0;
		break;
	case GameConfig::eKeys::DROP:
	default:
		this->diff_x = 0;
		this->diff_y = this->y == GameConfig::GAME_HEIGHT ? 0 : 1;
		break;
	}
	return (this->diff_x != 0 || this->diff_y != 0);

}

//Moves the point based on the setMoveDirection response, 
//Not moving out of bounds of the game width and height
//TODO : deciede if validation should be here or on the BOARD class.
void Point::move(GameConfig::eKeys key)
{
	if (this->setMoveDirection(key)) { // Why bool?, the shape will always move, isn't it?
		//this->draw(GameConfig::COLORS[0], ' ');

		if (this->x < GameConfig::GAME_WIDTH)
			this->x += this->diff_x;
		if (this->y < GameConfig::GAME_HEIGHT)
			this->y += this->diff_y;
	}
	else
		cout.flush();
}

