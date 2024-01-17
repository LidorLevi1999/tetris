#include "board.h"
#include "general.h"

#include <iostream>
using namespace std;

Board::Board() {
	for (int row = 0; row <= GameConfig::BOARD_HEIGHT; row++) {
		for (int col = 0; col <= GameConfig::BOARD_WIDTH; col++) {
			if (row == 0 || row == GameConfig::BOARD_HEIGHT)
				this->board[col][row] = '-';
			else if (col == 0 || col == GameConfig::BOARD_WIDTH)
				this->board[col][row] = '|';
			else
				this->board[col][row] = ' ';
		}
	}
}

void Board::drawBoard(char side) {
	int startX = 0, startY = 0;
	if (side == 'R')
		startX = GameConfig::RIVAL_POS;

	gotoxy(startX, startY);

	for (int row = 0; row <= GameConfig::BOARD_HEIGHT; row++) {
		for (int col = 0; col <= GameConfig::BOARD_WIDTH; col++) {
			cout << this->board[col][row];
		}
		gotoxy(startX, startY + row + 1);
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