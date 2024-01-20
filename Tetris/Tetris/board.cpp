#include "board.h"
#include "general.h"

#include <iostream>
using namespace std;
#include <Windows.h>

Board::Board(char side) {
	clearBoard();
	this->side = side;
}

void Board::clearBoard() {
	for (int row = 0; row < GameConfig::BOARD_HEIGHT; row++) {
		for (int col = 0; col < GameConfig::BOARD_WIDTH; col++) {
			this->board[col][row].setSymbol(' ');
		}
	}
}

void Board::drawBoard(char side) {
	int startX = 0, startY = 0;
	if (side == 'R')
		startX = GameConfig::RIVAL_POS;

	// Print the top border
	gotoxy(startX, startY++);
	for (int i = 0; i < GameConfig::BOARD_WIDTH + 2; i++) {
		cout << "-";
	}

	// Print the board content
	gotoxy(startX, startY);
	for (int row = 0; row <= GameConfig::BOARD_HEIGHT - 1; row++) {
		cout << "|";  // Print the leftmost vertical bar
		for (int col = 0; col < GameConfig::BOARD_WIDTH; col++) {
			char symbol = this->board[col][row].getSymbol();
			if (symbol == '#')
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), this->board[col][row].getColor());
			cout << symbol;
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GameConfig::COLORS[0]);
		}
		cout << '|';  // Print the rightmost vertical bar for the last column
		gotoxy(startX, startY + row + 1);
	}

	// Print the bottom border
	for (int i = 0; i < GameConfig::BOARD_WIDTH + 2; i++) {
		cout << "-";
	}

	this->side = side;
}

void Board::updateBoardWithPoints(Point* points) {
	int xOffset = this->side == 'L' ? 1 : GameConfig::RIVAL_POS + 1;
	int row, col;
	for (int i = 0; i < 4; i++) {
		row = points[i].getX() - xOffset;
		col = points[i].getY() - 1;
		this->board[row][col].setSymbol(points[i].getSymbol());
		this->board[row][col].setColor(points[i].getColor());
	}
}

int Board::validateBoard() {
	int scoreRecieved = 0;
	int multiplier = 1;
	for (int i = GameConfig::BOARD_HEIGHT - 1; i >= 0; i--) {
		if (isAllRowFull(i)) {
			bombRowAndFixBoard(i);
			drawBoard(this->side);
			i++;
			scoreRecieved += (5 * multiplier);
			multiplier *= 2;
		}
	}
	return scoreRecieved;
}

bool Board::isAllRowFull(int row) const {
	for (int col = 0; col < GameConfig::BOARD_WIDTH; col++) {
		if (this->board[col][row].getSymbol() == ' ')
			return false;
	}
	
	return true;
}

void Board::bombRowAndFixBoard(int row) {
	for (row; row > 0; row--) {
		for (int col = 0; col < GameConfig::BOARD_WIDTH; col++) {
			this->board[col][row] = this->board[col][row - 1];
		}
	}
	for (int col = 0; col < GameConfig::BOARD_WIDTH; col++) {
		this->board[col][0].setSymbol(' ');
	}
}