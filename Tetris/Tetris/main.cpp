#include <iostream>
#include <windows.h>
#include <conio.h> 
#include "block.h"
#include "board.h"

using namespace std;

int main()
{
	Board board;
	board.drawBordersAndScore();


	Block::eTetriminoShape shapeP1 = Block::eTetriminoShape::I;
	Block blockP1(shapeP1, 'L');
	Block::eTetriminoShape shapeP2 = Block::eTetriminoShape::I;
	Block blockP2(shapeP2, 'R');

	blockP1.moveBlock(GameConfig::eKeys::DROP, true);
	blockP2.moveBlock(GameConfig::eKeys::DROP, true);
	Sleep(1000);

	while (true)
	{
		if (_kbhit()) {
			char pressedChar = _getch();
			switch ((GameConfig::eKeys)pressedChar) {
			// Need to considerate 'break' cases
			//Left cases
			case GameConfig::eKeys::LEFTP1:
				blockP1.moveBlock(GameConfig::eKeys::LEFTP1);
			case GameConfig::eKeys::LEFTP2:
				blockP2.moveBlock(GameConfig::eKeys::LEFTP2);

			//Right cases
			case GameConfig::eKeys::RIGHTP1:
				blockP1.moveBlock(GameConfig::eKeys::RIGHTP1);
			case GameConfig::eKeys::RIGHTP2:
				blockP2.moveBlock(GameConfig::eKeys::RIGHTP2);

			// I'm not sure the "DROP" case is needed as it drops each second anyways
			//case GameConfig::eKeys::DROP:
			//	block.moveBlock((GameConfig::eKeys)pressedChar);
			//	break;
			
			// Rotate Clockwise cases
			case GameConfig::eKeys::ROTATE_CLOCKWISE:
				blockP1.rotateClockwise();
				break;
			// Need to add RIGHT Clockwise

			// Rotate Counter Clockwise cases
			case GameConfig::eKeys::ROTATE_COUNTERCLOCKWISE:
				blockP1.rotateCounterClockwise();
			// Need to add RIGHT Counter Clockwise
			}
		}

		blockP1.moveBlock(GameConfig::eKeys::DROP);
		blockP2.moveBlock(GameConfig::eKeys::DROP);

		Sleep(1000);
	}
}