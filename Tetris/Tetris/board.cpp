// Implementation file for the Board class.

#include "board.h"
#include "general.h"
#include <iostream>
#include <Windows.h>

// Constructor
Board::Board(char side) {
	this->side = side;
	clearBoard();
}

// Clears the entire game board
void Board::clearBoard() {
	for (int row = 0; row < GameConfig::BOARD_HEIGHT; row++) {
		for (int col = 0; col < GameConfig::BOARD_WIDTH; col++) {
			this->board[col][row].setSymbol(EMPTY_SPACE);
			this->board[col][row].setColor(GameConfig::COLORS[0]);
			this->board[col][row].setCoordinates(col + (this->side == 'L' ? GameConfig::MIN_X : 2 * GameConfig::MIN_X) + (this->side == 'L' ? 0 : GameConfig::RIVAL_POS), row + GameConfig::MIN_Y, false);
		}
	}
}

// Draws the game board, including borders and current block positions
void Board::drawBoard(char side) {
	int startX = 0, startY = 0;
	if (side == 'R')
		startX = GameConfig::RIVAL_POS;

	// Print the top border
	gotoxy(startX, startY++);
	for (int i = 0; i < GameConfig::BOARD_WIDTH + 2; i++) {
		std::cout << "-";
	}

	// Print the board content
	gotoxy(startX, startY);
	for (int row = 0; row <= GameConfig::BOARD_HEIGHT - 1; row++) {
		std::cout << "|";  // Print the leftmost vertical bar
		for (int col = 0; col < GameConfig::BOARD_WIDTH; col++) {
			char symbol = this->board[col][row].getSymbol();
			if (symbol == TETRIMINO_SYMBOL)
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), this->board[col][row].getColor());
			std::cout << symbol;
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GameConfig::COLORS[0]);
		}
		std::cout << '|';  // Print the rightmost vertical bar for the last column
		gotoxy(startX, startY + row + 1);
	}

	// Print the bottom border
	for (int i = 0; i < GameConfig::BOARD_WIDTH + 2; i++) {
		std::cout << "-";
	}

	this->side = side;
}

// Updates the game board with the current block's points
void Board::updateBoardWithPoints(const Point* const& points) {
	// Determine the offset based on the side
	int xOffset = (this->side == 'L') ? 1 : GameConfig::RIVAL_POS + 1;

	// Iterate over the points and update the board
	for (int i = 0; i < 4; i++) {
		// Calculate the row and column for each point
		int row = points[i].getX() - xOffset;
		int col = points[i].getY() - 1;

	    // Update the board with the symbol and color of the point
		this->board[row][col].setSymbol(points[i].getSymbol());
		this->board[row][col].setColor(points[i].getColor());
	}
}

// Validates and clears full rows, updating the board and returning the score
int Board::validateBoard(bool isRealBoard) {
	int scoreReceived = 0;
	int multiplier = 1;
	bool redrawRequired = false;

	for (int i = GameConfig::BOARD_HEIGHT - 1; i >= 0; i--) {
		if (isAllRowFull(i)) {
			bombRowAndFixBoard(i);
			redrawRequired = true;
			scoreReceived += (5 * multiplier);
			multiplier *= 2;
		}
	}

	if (redrawRequired && isRealBoard)
		drawBoard(this->side);

	return scoreReceived;
}

// Checks if a given row is completely filled with blocks
bool Board::isAllRowFull(int row) const {
	for (int col = 0; col < GameConfig::BOARD_WIDTH; col++) {
		if (this->board[col][row].getSymbol() == EMPTY_SPACE)
			return false;
	}
	return true;
}

// Clears a filled row and shifts the above rows down
void Board::bombRowAndFixBoard(int row) {
	for (; row > 0; row--) {
		for (int col = 0; col < GameConfig::BOARD_WIDTH; col++) {
			this->board[col][row] = this->board[col][row - 1];
		}
	}
	for (int col = 0; col < GameConfig::BOARD_WIDTH; col++) {
		this->board[col][0].setSymbol(EMPTY_SPACE);
	}
}

// Performs the explosion of the bomb
void Board::performBombExplosion(const Point& bombPosition) {
	int xOffset = this->side == 'L' ? 1 : GameConfig::RIVAL_POS + 1;
	int yOffset = GameConfig::MIN_Y;
	int bombBoardYPosition = bombPosition.getY() - yOffset;
	int bombBoardXPosition = bombPosition.getX() - xOffset;
	int startX = bombBoardXPosition - 4 < 0 ? 0 : bombBoardXPosition -4 ;
	int endX = bombBoardXPosition + 4 >= GameConfig::BOARD_WIDTH ? GameConfig::BOARD_WIDTH - 1 : bombBoardXPosition + 4;
	int startY = bombBoardYPosition - 4 < 0 ? 0 : bombBoardYPosition - 4;
	int endY = (bombBoardYPosition + 4) > GameConfig::BOARD_HEIGHT - yOffset ? GameConfig::BOARD_HEIGHT - yOffset : bombBoardYPosition + 4;

	for (int i = startY; i <= endY; i++) {
		for (int j = startX; j <= endX; j++) {
			board[j][i].setSymbol(EMPTY_SPACE);
			board[j][i].setColor(GameConfig::COLORS[0]);
		}
	}

	gotoxy(bombPosition.getX(), bombPosition.getY());
	std::cout << " ";
	updateBoardPointsAfterExplosion();
}

// Update all board points afterh the explosion
void Board::updateBoardPointsAfterExplosion() {
	for (int col = 0; col < GameConfig::BOARD_WIDTH; col++) {
		dropPointsDown(col);
	}
}

// Drops all points down;
void Board::dropPointsDown(int col) {
	for (int i = GameConfig::BOARD_HEIGHT - 1; i > 0; i--) {
		if(this->board[col][i].getSymbol() == EMPTY_SPACE) {
			for (int j = i - 1; j > 0; j--) {
				if (this->board[col][j].getSymbol() == TETRIMINO_SYMBOL) {
					this->board[col][i].setColor(this->board[col][j].getColor());
					this->board[col][i].setSymbol(this->board[col][j].getSymbol());
					this->board[col][j].setColor(GameConfig::COLORS[0]);
					this->board[col][j].setSymbol(EMPTY_SPACE);
					break;
				}
			}
		}
	}
}