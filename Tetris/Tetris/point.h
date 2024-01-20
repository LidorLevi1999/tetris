#pragma once
#ifndef __POINT_H
#define __POINT_H
#include "gameConfig.h"

class Point
{
	int x;
	int y;
	char symbol;
	int diff_x;
	int diff_y;
	int color;

public:
	Point() = default;
	Point(int x, int y, char symbol, int color);
	void draw(int backcolor);
	void draw(int backcolor, char symbol);
	void move(GameConfig::eKeys key, bool shouldDraw = true);
	char getSymbol() const { return this->symbol; };
	void setSymbol(char symbol) { this->symbol = symbol; };
	int getX() const { return this->x; };
	int getY() const { return this->y; };
	void setCoordinates(int x, int y, bool shouldDraw = false);
	Point setMoveDirectionAndGetNext(GameConfig::eKeys key);
};
#endif
