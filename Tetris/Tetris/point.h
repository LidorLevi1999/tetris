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
	void draw(int backcolor, char symbol, char side);
	void move(GameConfig::eKeys key);
	char getSymbol() { return this->symbol; };
	void setSymbol(char symbol) { this->symbol = symbol; };
	int getX() { return this->x; };
	int getY() { return this->y; };
	void setCoordinates(int x, int y);
	Point setMoveDirectionAndGetNext(GameConfig::eKeys key);

private:
};
#endif
