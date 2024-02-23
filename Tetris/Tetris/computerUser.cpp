// Implementation file for the User class.


#include "computerUser.h"
#include "gameConfig.h"
#include <algorithm> 
#include <random>

// Handles the movement of the current block.
void ComputerUser::handleMovement(GameConfig::eKeys direction) {
    if (bestMovement.size() > 0) {
        GameConfig::eKeys movement = *(bestMovement.begin());
        if (movement == rotateClockwise)
            this->rotateMovingBlock();
        else if (movement == rotateCounterClockwise)
            this->rotateMovingBlock(false);
        else this->moveMovingBlock(movement);
        bestMovement.erase(bestMovement.begin());
    }
}

// Creates a new moving block and calculates the best movement sequence for it.
void ComputerUser::createNewMovingBlock() {
	User::createNewMovingBlock();
	calculateBestMovement();
}

// Calculates the best movement sequence for the current moving block.
void ComputerUser::calculateBestMovement() {
    std::vector<std::pair<std::vector<GameConfig::eKeys>, Block>> allPossibleMovements = findAllPossibleMovements();
    std::vector<std::pair<std::vector<GameConfig::eKeys>, Block>> bestScoreMovements = allBestScoreMovement(allPossibleMovements);
    if (bestScoreMovements.size() == 1) {
        bestMovement = bestScoreMovements[0].first;
        return;
    }    else if (bestScoreMovements.size() == 0) {
        bestMovement.clear();
        return;
    }
    std::vector<std::pair<std::vector<GameConfig::eKeys>, Block>> mostPointsDownMovements = allMostPointsDownMovements(bestScoreMovements);
    if (mostPointsDownMovements.size() == 1) {
        bestMovement = mostPointsDownMovements[0].first;
        return;
    }
    if (mostPointsDownMovements.size() == 0) {
        bestMovement.clear();
        return;
    }
    std::vector<std::pair<std::vector<GameConfig::eKeys>, Block>> leastPointsUpMovments = allLeastPointsUpMovments(mostPointsDownMovements);
    if (leastPointsUpMovments.size() == 1) {
        bestMovement = leastPointsUpMovments[0].first;
        return;
    }
    else if (leastPointsUpMovments.size() == 0) {
        bestMovement.clear();
        return;
    }
    int randomValue = rand() % leastPointsUpMovments.size();
    bestMovement = leastPointsUpMovments[randomValue].first;
}

// Finds all movements with the most downward points.
std::vector<std::pair<std::vector<GameConfig::eKeys>, Block>> ComputerUser::allMostPointsDownMovements(const std::vector<std::pair<std::vector<GameConfig::eKeys>, Block>>& allPossibleMovements) {
    std::vector<std::pair<std::vector<GameConfig::eKeys>, Block>> allValidMovements;
    int lowestY = getLowestY(allPossibleMovements[0].second);
    int yOffset = 1;
    lowestY -= yOffset;
    int amountAtLowestY = 0;
    for (const auto& movement : allPossibleMovements) {
        Board boardCopy = this->getBoard();
        boardCopy.updateBoardWithPoints(movement.second.getBlockPoints());
        int temp = getAmountOfPointsAtY(boardCopy, lowestY);
        int currentLowestY = getLowestY(movement.second);
        if (currentLowestY > lowestY) {
            lowestY = currentLowestY;
            allValidMovements.clear();
            allValidMovements.push_back(movement);
        }
        else if (currentLowestY == lowestY && temp > amountAtLowestY) {
            if (temp > amountAtLowestY) {
                amountAtLowestY = temp;
                allValidMovements.clear();
                allValidMovements.push_back(movement);
            }
            else if (temp == amountAtLowestY) {
                allValidMovements.push_back(movement);
            }
        }
    }

    return allValidMovements;
}

// Gets the amount of points at the given Y coordinate on the board.
int ComputerUser::getAmountOfPointsAtY(Board& b, const int y) {
    int res = 0;
    for (int i = 0; i < GameConfig::BOARD_WIDTH; i++) {
        if (b.getBoard()[i][y].getSymbol() != EMPTY_SPACE)
            res++;
    }
    return res;
}

// Gets the lowest Y coordinate of the given block.
int ComputerUser::getLowestY(const Block& b) {
    const Point* points = b.getBlockPoints();
    int lowest = points[0].getY();
    for (int i = 1; i < 4; i++) {
        if (points[i].getY() > lowest)
            lowest = points[i].getY();
    }
    return lowest;
}

// Gets the highest Y coordinate of the given block.
int ComputerUser::getHighestY(const Block& b) {
    const Point* points = b.getBlockPoints();
    int highest = points[0].getY();
    for (int i = 1; i < 4; i++) {
        if (points[i].getY() < highest)
            highest = points[i].getY();
    }
    return highest;
}

// Finds all movements with the least upward points.
std::vector<std::pair<std::vector<GameConfig::eKeys>, Block>>ComputerUser::allLeastPointsUpMovments(const std::vector<std::pair<std::vector<GameConfig::eKeys>, Block>>& allPossibleMovements) {
    std::vector<std::pair<std::vector<GameConfig::eKeys>, Block>> allValidMovements;
    
    if (allPossibleMovements.empty()) {
        return allValidMovements;
    }
    int highestY = getHighestY(allPossibleMovements[0].second);
    int amountAtHighestY = GameConfig::BOARD_WIDTH;
    int yOffset = 1;
    int temp;

    for (const auto& movement : allPossibleMovements) {
        temp = getHighestY(movement.second);
        if (temp < highestY)
            highestY = temp;

        Board boardCopy = this->getBoard();
        boardCopy.updateBoardWithPoints(movement.second.getBlockPoints());
        int pointsAtY = getAmountOfPointsAtY(boardCopy, highestY - yOffset);

        if (pointsAtY < amountAtHighestY) {
            amountAtHighestY = pointsAtY;
            allValidMovements.clear(); 
        }
        if (pointsAtY == amountAtHighestY) {
            allValidMovements.push_back(movement);
        }
    }

    return allValidMovements;
}

// Finds all possible movements for the current moving block.
std::vector<std::pair<std::vector<GameConfig::eKeys>, Block>> ComputerUser::findAllPossibleMovements() {
    std::vector<std::pair<std::vector<GameConfig::eKeys>, Block>> allPossibleMovements;
    std::vector<GameConfig::eKeys> currentMove;
    //TODO : Maybe prioritize here if should go for deeper check using exploreAllPossibleMoves
    //TODO : Or build another function that doesn't do left and than right movments (using for loops) and without rotations as well
    //TODO : As in the worst case, (first movement) there are 5^17 possibilities, and most of them identical
    //TODO : (It doesnt matter where lying I tetermino will be.)
    //TODO : And we can use more accurate calculation based on Computer level and Highest board y.
    int highestY = getHighestPointYAxisValueOnBoard();
    Block myBlock = getMovingBlock();
    int accurateStartPosition = mapComputerLevelToStartAccurateSearchYPosition();

    //exploreAllPossibleMoves(myBlock, currentMove, allPossibleMovements);
    //int numOfEmptyColumnts

    nonAccurateSearch(myBlock, allPossibleMovements);

    if (highestY <= accurateStartPosition && getAmountOfPointsAboveY(this->board, accurateStartPosition) >= 4) {
        exploreAllPossibleMoves(myBlock, currentMove, allPossibleMovements);
    }
    else {
        nonAccurateSearch(myBlock, allPossibleMovements);
    }
    return allPossibleMovements;
}

// Finds all movements with the best score.
std::vector<std::pair<std::vector<GameConfig::eKeys>, Block>> ComputerUser::allBestScoreMovement(const std::vector<std::pair<std::vector<GameConfig::eKeys>, Block>>& allPossibleMovements) {
    int maxScore = 0;
    std::vector<std::pair<std::vector<GameConfig::eKeys>, Block>> bestScoreMovements;

    for (const auto& movement : allPossibleMovements) {
        Board boardCopy = this->getBoard();
        boardCopy.updateBoardWithPoints(movement.second.getBlockPoints());
        int score = boardCopy.validateBoard(false);

        if (score > maxScore) {
            bestScoreMovements.clear();
            maxScore = score;
        }
        if (score == maxScore) {
            bestScoreMovements.push_back(movement);
        }
    }
    return bestScoreMovements;
}


// Recursive function to explore all possible moves
void ComputerUser::exploreAllPossibleMoves(Block& block, std::vector<GameConfig::eKeys>& moves, std::vector<std::pair<std::vector<GameConfig::eKeys>, Block>>& allMoves)
{
    if (!checkCopiedBlockCollisionWithBoard(block)) {
        return;
    }
    Block copyBlock = block;
    copyBlock.moveBlock(downMove);
    if (!checkCopiedBlockCollisionWithBoard(copyBlock)) {
        allMoves.push_back(std::make_pair(moves, block));
        return;
    }

    Block downBlock = copyBlock;
    std::vector<GameConfig::eKeys> downMoves = moves;
    downBlock.moveBlock(downMove);
    downMoves.push_back(downMove);
    exploreAllPossibleMoves(downBlock, downMoves, allMoves);

    Block leftBlock = copyBlock;
    std::vector<GameConfig::eKeys> leftMoves = moves;
    leftBlock.moveBlock(leftMove);
    leftMoves.push_back(leftMove);
    exploreAllPossibleMoves(leftBlock, leftMoves, allMoves);

    Block rightBlock = copyBlock;
    std::vector<GameConfig::eKeys> rightMoves = moves;
    rightBlock.moveBlock(rightMove);
    rightMoves.push_back(rightMove);
    exploreAllPossibleMoves(rightBlock, rightMoves, allMoves);

    Block rotatedBlock = copyBlock;
    std::vector<GameConfig::eKeys> rotateMoves = moves;
    rotatedBlock.rotateClockwise();
    rotateMoves.push_back(rotateClockwise);
    exploreAllPossibleMoves(rotatedBlock, rotateMoves, allMoves);

    Block rotatedCounterBlock = copyBlock;
    std::vector<GameConfig::eKeys> rotateCounterMoves = moves;
    rotatedCounterBlock.rotateCounterClockwise();
    rotateCounterMoves.push_back(rotateCounterClockwise);
    exploreAllPossibleMoves(rotatedCounterBlock, rotateCounterMoves, allMoves);
}

// Gets the highest Y axis value on the board.
int ComputerUser::getHighestPointYAxisValueOnBoard() {
    Board copyBoard = this->getBoard();
    int res = GameConfig::BOARD_HEIGHT;
    for (int i = GameConfig::BOARD_HEIGHT - 1; i >= 0; i--) {
        for (int j = 0; j < GameConfig::BOARD_WIDTH; j++) {
            if (copyBoard.getBoard()[j][i].getSymbol() == TETRIMINO_SYMBOL && res > i) {
                res = i;
            }
        }
    }
    return res;
}

// Maps the computer level to start an accurate search Y position.
int ComputerUser::mapComputerLevelToStartAccurateSearchYPosition() {
    switch (this->level) {
    case 0: return 6;
    case 1:return 8;
    case 2: return 9;
    }

    return 9;
}

// NEED TO BE DELETED IN CASE NOT IN USE
void ComputerUser::nonAccurateSearch(Block myBlock, std::vector<std::pair<std::vector<GameConfig::eKeys>, Block>>& allPossibleMovements) {
    this->board.drawBoard(this->getSide());
    this->getMovingBlock().drawBlock();
    int leftDistance = getBlockDistanceFromLeftBorder(myBlock);
    int rightDistance = getBlockDistanceFromRightBorder(myBlock);
    Block copyBlock;
    std::vector<GameConfig::eKeys> moves;

    // Perform rotations and movements to the left
    for (int rotateCount = 0; rotateCount < 4; rotateCount++) {
        for (int i = 0; i <= leftDistance; i++) { // Adjusted loop condition
            copyBlock = myBlock;
            moves.clear();
            // Rotate the block
            for (int j = 0; j <= rotateCount; j++) {
                copyBlock.rotateClockwise();
                moves.push_back(rotateClockwise);
            }
            // Move the block to the left
            for (int k = 0; k < i; k++) { // Adjusted loop condition
                copyBlock.moveBlock(leftMove);
                moves.push_back(leftMove);
            }
            // Move the block down until it collides or reaches the bottom
            while (checkCopiedBlockCollisionWithBoard(copyBlock)) { // Added condition to check if the block reached the bottom
                copyBlock.moveBlock(downMove);
                moves.push_back(downMove);
            }
            // Add the movement sequence to the list of possible movements
            allPossibleMovements.push_back(std::make_pair(moves, copyBlock));
        }
    }

    // Perform rotations and movements to the right
    for (int rotateCount = 0; rotateCount < 4; rotateCount++) {
        for (int i = 0; i <= rightDistance; i++) { // Adjusted loop condition
            copyBlock = myBlock;
            moves.clear();
            // Rotate the block
            for (int j = 0; j <= rotateCount; j++) {
                copyBlock.rotateClockwise();
                moves.push_back(rotateClockwise);
            }
            // Move the block to the right
            for (int k = 0; k < i; k++) { // Adjusted loop condition
                copyBlock.moveBlock(rightMove);
                moves.push_back(rightMove);
            }
            // Move the block down until it collides or reaches the bottom
            while (checkCopiedBlockCollisionWithBoard(copyBlock)) { // Added condition to check if the block reached the bottom
                copyBlock.moveBlock(downMove);
                moves.push_back(downMove);
            }
            // Add the movement sequence to the list of possible movements
            allPossibleMovements.push_back(std::make_pair(moves, copyBlock));
        }
    }
}

// LIDOR'S ORIGINAL NONACCURATESEARCTH
//void ComputerUser::nonAccurateSearch(Block myBlock, std::vector<std::pair<std::vector<GameConfig::eKeys>, Block>>& allPossibleMovements) {
//    this->board.drawBoard(this->getSide());
//    this->getMovingBlock().drawBlock();
//    int leftDistance = getBlockDistanceFromLeftBorder(myBlock);
//    int rightDistance = getBlockDistanceFromRightBorder(myBlock);
//    Block copyBlock;
//    std::vector<GameConfig::eKeys> moves;
//    copyBlock.moveBlock(downMove);
//    moves.push_back(downMove);
//    // Perform rotations and movements to the left
//    for (int rotateCount = 0; rotateCount < 4; rotateCount++) {
//        for (int i = leftDistance; i >= 0; i--) {
//            copyBlock = myBlock;
//            moves.clear();
//            for (int j = 0; j <= rotateCount; j++) {
//                copyBlock.rotateClockwise();
//                moves.push_back(rotateClockwise);
//                copyBlock.moveBlock(downMove);
//            }
//            for (int k = 0; k <= i; k++) {
//                copyBlock.moveBlock(leftMove);  // Move left
//                moves.push_back(leftMove);
//                copyBlock.moveBlock(downMove);
//            }
//            while (true) {
//                Block previousCopyBlock = copyBlock;  
//                copyBlock.moveBlock(downMove);
//
//                if (!checkCopiedBlockCollisionWithBoard(copyBlock)) {
//                    allPossibleMovements.push_back(std::make_pair(moves, previousCopyBlock));
//                    break;
//                }
//            }
//        }
//    }
//
//    // Perform rotations and movements to the right
//    for (int rotateCount = 0; rotateCount < 4; rotateCount++) {
//        for (int i = rightDistance; i >= 0; i--) {
//            copyBlock = myBlock;
//            moves.clear();
//
//            for (int j = 0; j <= rotateCount; j++) {
//                copyBlock.rotateClockwise();
//                moves.push_back(rotateClockwise);
//                copyBlock.moveBlock(downMove);
//            }
//            for (int k = 0; k <= i; k++) {
//                copyBlock.moveBlock(rightMove);  // Move left
//                moves.push_back(rightMove);
//                copyBlock.moveBlock(downMove);
//            }
//            while (true) {
//                Block previousCopyBlock = copyBlock;
//                copyBlock.moveBlock(downMove);
//                if (!checkCopiedBlockCollisionWithBoard(copyBlock)) {
//                    allPossibleMovements.push_back(std::make_pair(moves, previousCopyBlock));
//                    break;
//                }
//            }
//        }
//    }
//}

// Gets the distance of the given block from the left border.
int ComputerUser::getBlockDistanceFromLeftBorder(const Block& myBlock) {
    int xOffset = this->getSide() == 'R' ? GameConfig::RIVAL_POS + 1 : 1;
    const Point* points = myBlock.getBlockPoints();
    int lefterPointXPos = points[0].getX();
    for (int i = 1; i < 4; i++) {
        if (points[i].getX() < lefterPointXPos)
            lefterPointXPos = points[i].getX();
    }
    return lefterPointXPos - xOffset;
}

// Gets the distance of the given block from the right border.
int ComputerUser::getBlockDistanceFromRightBorder(const Block& myBlock) {
    int xOffset = this->getSide() == 'R' ? GameConfig::RIVAL_POS : 0;
    const Point* points = myBlock.getBlockPoints();
    int righterPointXPos = points[0].getX();
    for (int i = 1; i < 4; i++) {
        if (points[i].getX() > righterPointXPos)
            righterPointXPos = points[i].getX();
    }
    return xOffset + GameConfig::BOARD_WIDTH - righterPointXPos;
}

// Gets the total amount of points above the given Y coordinate on the board.
int ComputerUser::getAmountOfPointsAboveY(Board& b, const int y) {
    int totalPoints = 0;
    for (int currentY = y; currentY >= 0; --currentY) 
        totalPoints += getAmountOfPointsAtY(b, currentY);
    return totalPoints;
}
