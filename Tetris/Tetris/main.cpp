#include "game.h"
#include <cstdlib>
#include <ctime>

int main() {
	srand(time(nullptr));
	GameManager().startGame();
}