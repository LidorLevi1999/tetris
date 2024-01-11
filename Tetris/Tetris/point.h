#pragma once
#ifndef __POINT_H
#define __POINT_H
#include "gameConfig.h"

class Point
{
	int x;
	int y;
	char symbol;
	//Color color;
	int diff_x;
	int diff_y;

public:
	Point() = default;
	Point(int x, int y, char symbol);
	void draw(int backcolor);
	void draw(int backcolor, char symbol);
	void move(GameConfig::eKeys key);
	char getSymbol() { return this->symbol; };
	int getX() { return this->x; };
	int getY() { return this->y; };

private:
	bool setMoveDirection(GameConfig::eKeys key);
};
#endif
