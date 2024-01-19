#include "board.h"
#include "general.h"

#include <iostream>
using namespace std;

Board::Board(char side) {
	clearBoard();
	this->side = side;
}

void Board::clearBoard() {
	for (int row = 0; row <= GameConfig::BOARD_HEIGHT; row++) {
		for (int col = 0; col <= GameConfig::BOARD_WIDTH; col++) {
			this->board[col][row] = ' ';
		}
	}
}

void Board::drawBoard(char side) {
	int startX = 0, startY = 0;
	if (side == 'R')
		startX = GameConfig::RIVAL_POS;

	gotoxy(startX, startY++);
	// Print the top border
	for (int i = 0; i < GameConfig::BOARD_WIDTH + 2; i++) {
		cout << "-";
	}
	gotoxy(startX, startY);

	// Print the board content
	for (int row = 0; row <= GameConfig::BOARD_HEIGHT - 1; row++) {
		cout << "|";  // Print the leftmost vertical bar
		for (int col = 0; col < GameConfig::BOARD_WIDTH; col++) {
			cout << this->board[col][row];
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


//void Board::drawScore()
//{
//	//Players score
//	gotoxy(GameConfig::GAME_WIDTH + 7, GameConfig::MIN_Y - 1);
//	cout << "P1";
//	gotoxy(GameConfig::GAME_WIDTH + 14, GameConfig::MIN_Y - 1);
//	cout << "P2";
//}


void Board::updateBoardWithPoints(Point* points) {
	int xOffset = this->side == 'L' ? 1 : GameConfig::RIVAL_POS;
	int row, col;
	for (int i = 0; i < 4; i++) {
		row = points[i].getX() - xOffset;
		col = points[i].getY() - 1;
		this->board[row][col] = points[i].getSymbol();
	}
}


void Board::validateBoard() {
	for (int i = GameConfig::BOARD_HEIGHT - 1; i >= 0; i--) {
		if (isAllRowFull(i)) {
			bombRowAndFixBoard(i);
			drawBoard(this->side);
			i++;
		}
	}
}

bool Board::isAllRowFull(int row) const {
	for (int col = 0; col < GameConfig::BOARD_WIDTH; col++) {
		if (this->board[col][row] == ' ')
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
		this->board[col][0] = ' ';
	}
}