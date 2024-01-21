// Header file for the Point class.

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
    // Default constructor
    Point() = default;

    // Parameterized constructor
    Point(int x, int y, char symbol, int color);

    // Function to draw the point with a background color
    void draw(int backcolor);

    // Function to draw the point with a background color and a specific symbol
    void draw(int backcolor, char symbol);

    // Function to move the point based on the input key
    void move(GameConfig::eKeys key, bool shouldDraw = true);

    // Getter for the symbol
    char getSymbol() const { return this->symbol; };

    // Setter for the symbol
    void setSymbol(char symbol) { this->symbol = symbol; };

    // Getter for the color
    int getColor() const { return this->color; };

    // Setter for the color
    void setColor(int color) { this->color = color; };

    // Getter for the x-coordinate
    int getX() const { return this->x; };

    // Getter for the y-coordinate
    int getY() const { return this->y; };

    // Function to set the coordinates of the point and optionally draw it
    void setCoordinates(int x, int y, bool shouldDraw = false);

    // Function to set the move direction of the point based on the input key and get the next position
    Point setMoveDirectionAndGetNext(GameConfig::eKeys key);
};
#endif
