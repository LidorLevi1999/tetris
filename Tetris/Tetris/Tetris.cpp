#include <iostream>
#include <windows.h>
#include <conio.h> 
#include "block.h"
using namespace std;
//int main()
//{
	//point1.draw(BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);
	//point2.draw(BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);
	//point3.draw(BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);
	//point4.draw(BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);
	//while (true)
	//{
	//	if (_kbhit())
	//	{
	//		char pressedChar = _getch();
	//		switch ((GameConfig::eKeys)pressedChar) {
	//		case GameConfig::eKeys::LEFT:
	//		case GameConfig::eKeys::RIGHT:
	//		case GameConfig::eKeys::DOWN:
	//			block.moveBlock((GameConfig::eKeys)pressedChar);
	//			break;
	//		case GameConfig::eKeys::ROTATE_CLOCKWISE:
	//			block.rotateClockwise();
	//			break;
	//		case GameConfig::eKeys::ROTATE_COUNTERCLOCKWISE:
	//			block.rotateCounterClockwise();
	//		}
	//	}
	//	Sleep(200);
	//}
//}


#define N 4
void rotate90Clockwise(int a[N][N]);
void rotate90Clockwise(char a[N][N]);

void printMatrix(int arr[N][N]);



// Driver code
int main()
{

	//Block b = Block(Block::eTetriminoShape::T);
	//Block b = Block(Block::eTetriminoShape::L);
	//Block b = Block(Block::eTetriminoShape::J);
	//Block b = Block(Block::eTetriminoShape::S);
	//Block b = Block(Block::eTetriminoShape::Z);
	Block b = Block(Block::eTetriminoShape::I);

	b.rotateClockwise();
	b.rotateClockwise();
	b.rotateClockwise();
	b.rotateClockwise();
	//return 0;
	//int arr[N][N] = { { 1, 2, 3, 4 },
	//			  { 5, 6, 7, 8 },
	//			  { 9, 10, 11, 12 },
	//			  { 13, 14, 15, 16 } };
	//printMatrix(arr);
	//cout << endl << endl;
	//rotate90Clockwise(arr);
	//printMatrix(arr);
	return 0;

}



// Function to rotate the matrix 90 degree clockwise
void rotate90Clockwise(int a[N][N])
{

	// Traverse each cycle
	for (char i = 0; i < N / 2; i++) {
		for (char j = i; j < N - i - 1; j++) {

			// Swap elements of each cycle
			// in clockwise direction
			char temp = a[i][j];
			a[i][j] = a[N - 1 - j][i];
			a[N - 1 - j][i] = a[N - 1 - i][N - 1 - j];
			a[N - 1 - i][N - 1 - j] = a[j][N - 1 - i];
			a[j][N - 1 - i] = temp;
		}
	}
}

void rotate90Clockwise(char a[N][N])
{

	// Traverse each cycle
	for (char i = 0; i < N / 2; i++) {
		for (char j = i; j < N - i - 1; j++) {

			// Swap elements of each cycle
			// in clockwise direction
			char temp = a[i][j];
			a[i][j] = a[N - 1 - j][i];
			a[N - 1 - j][i] = a[N - 1 - i][N - 1 - j];
			a[N - 1 - i][N - 1 - j] = a[j][N - 1 - i];
			a[j][N - 1 - i] = temp;
		}
	}
}


// Function for print matrix
void printMatrix(int arr[N][N])
{
	for (auto i = 0; i < N; i++) {
		for (auto j = 0; j < N; j++)
			cout << arr[i][j] << " ";
		cout << '\n';
	}
	cout << '\n';

}