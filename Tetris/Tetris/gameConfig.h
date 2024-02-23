// Header file for the GameConfig class.

#ifndef __GAME_CONFIG_H
#define __GAME_CONFIG_H

#define TETRIMINO_SYMBOL '#'
#define BOMB_SYMBOL '@'
#define EMPTY_SPACE ' '

class GameConfig
{
public:
    enum class eKeys {
        // Left player controls
        LEFTP1 = 'a', RIGHTP1 = 'd',
        DROPP1 = 'x', ROTATE_CLOCKP1 = 's', ROTATE_COUNTERP1 = 'w',

        // Right player controls
        LEFTP2 = 'j', RIGHTP2 = 'l',
        DROPP2 = 'm', ROTATE_CLOCKP2 = 'k', ROTATE_COUNTERP2 = 'i',

        ESC = 27,  // Escape key for pausing the game
        NONE = 9999,

        // Menu Selection
        HumanVsHuman = 1,
        HumanVsComputer = 2,
        ComputerVsComputer = 3,
        ContinuePausedGame = 4,
        HumanVsHumanColors = 5,
        HumanVsComputerColors = 6,
        ComputerVsComputerColors = 7,
        Instructions = 8,
        Quit = 9,

        // Shapes
        ShapeO = 0,
        ShapeI = 1,
        ShapeT = 2,
        ShapeL = 3,
        ShapeJ = 4,
        ShapeS = 5,
        // ShapeZ = 6 (currently as default)
    };

	// Board dimensions
	static constexpr int BOARD_HEIGHT = 18;
	static constexpr int BOARD_WIDTH = 12;

	// Left player board starting position
	static constexpr int MIN_X = 1;
	static constexpr int MIN_Y = 1;

	// Adjusted position for the right player
	static constexpr int RIVAL_POS = BOARD_WIDTH + 18 + 3;

	static const int COLORS[];
	static int NUM_OF_COLORS;  

	static void setColorSupport(bool isColorSupported);
};
#endif