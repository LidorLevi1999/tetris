#include "board.h"
#include "general.h"

#include <iostream>
using namespace std;

void Board::drawBordersAndScore()
{
	drawTPHBorders();
	drawLRVBorders();
	drawScore();
}

void Board::drawTPHBorders()
{
	//Top, bottom and horizontal borders
	for (int col = GameConfig::MIN_X; col < GameConfig::GAME_WIDTH + GameConfig::MIN_X; col++)
	{
		//Left player board top and then bottom border
		gotoxy(col, GameConfig::MIN_Y - 1);
		cout << "-";
		gotoxy(col, GameConfig::GAME_HEIGHT + GameConfig::MIN_Y);
		cout << "-";

		//Score board horizontal border
		gotoxy(col + GameConfig::GAME_WIDTH + 4, GameConfig::MIN_Y);
		cout << "-";
		if (col == GameConfig::GAME_WIDTH)
		{
			gotoxy(col + GameConfig::GAME_WIDTH + 5, GameConfig::MIN_Y);
			cout << "-";
		}

		//Right player board top and then bottom border
		gotoxy(col + GameConfig::RIVAL_MIN_X, GameConfig::MIN_Y - 1);
		cout << "-";
		gotoxy(col + GameConfig::RIVAL_MIN_X, GameConfig::GAME_HEIGHT + GameConfig::MIN_Y);
		cout << "-";
	}
}

void Board::drawLRVBorders()
{

	//Left, right and vertical borders
	for (int row = GameConfig::MIN_Y - 1; row <= GameConfig::GAME_HEIGHT + GameConfig::MIN_Y; row++)
	{
		//Left player board left and then right border
		gotoxy(GameConfig::MIN_X - 1, row);
		cout << "|";
		gotoxy(GameConfig::GAME_WIDTH + GameConfig::MIN_X, row);
		cout << "|";

		//Score board vertical border
		gotoxy(GameConfig::GAME_WIDTH + GameConfig::MIN_X + 10, row);
		cout << "|";

		//Right player board left and then right border
		gotoxy(GameConfig::RIVAL_MIN_X + GameConfig::MIN_X - 1, row);
		cout << "|";
		gotoxy(GameConfig::RIVAL_MIN_X + GameConfig::GAME_WIDTH + GameConfig::MIN_X, row);
		cout << "|";
	}
}

void Board::drawScore()
{
	//Players score
	gotoxy(GameConfig::GAME_WIDTH + 7, GameConfig::MIN_Y - 1);
	cout << "P1";
	gotoxy(GameConfig::GAME_WIDTH + 14, GameConfig::MIN_Y - 1);
	cout << "P2";
}