// Implementation file for the User class.


#include "computerUser.h"
#include "gameConfig.h"
#include <algorithm> 
#include <random>
#include <iostream>
#include "general.h"


// Handles the movement of the current block.
void ComputerUser::handleMovement(GameConfig::eKeys direction) {
    if (bestMovement.size() > 0) {
        GameConfig::eKeys movement = *(bestMovement.begin());
        if (movement == rotateClockwise)
            this->rotateMovingBlock();
        //else if (movement == rotateCounterClockwise)
        //    this->rotateMovingBlock(false);
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
    if (this->level == 1 && (this->numOfMove % 50) == 49) {
        int randomValue = rand() % allPossibleMovements.size();
        bestMovement = allPossibleMovements[randomValue].first;
    }
    else if (this->level == 2 && (this->numOfMove % 20) == 19) {
        int randomValue = rand() % allPossibleMovements.size();
        bestMovement = allPossibleMovements[randomValue].first;
    }
     else if (this->level == 3 && (this->numOfMove % 10) == 9) {
        int randomValue = rand() % allPossibleMovements.size();
        bestMovement = allPossibleMovements[randomValue].first;
    }
    else {
        std::vector<std::pair<std::vector<GameConfig::eKeys>, Block>> bestScoreMovements = allBestScoreMovement(allPossibleMovements);
        if (bestScoreMovements.size() == 1) {
            bestMovement = bestScoreMovements[0].first;
            return;
        }
        else if (bestScoreMovements.empty()) {
            bestMovement.clear();
            return;
        }
        std::vector<std::pair<std::vector<GameConfig::eKeys>, Block>> mostPointsDownMovements = allMostPointsDownMovements(bestScoreMovements);
        if (mostPointsDownMovements.size() == 1) {
            bestMovement = mostPointsDownMovements[0].first;
            return;
        }
        if (mostPointsDownMovements.empty()) {
            bestMovement.clear();
            return;
        }
        std::vector<std::pair<std::vector<GameConfig::eKeys>, Block>> leastPointsUpMovements = allLeastPointsUpMovements(mostPointsDownMovements);
        if (leastPointsUpMovements.size() == 1) {
            bestMovement = leastPointsUpMovements[0].first;
            return;
        }
        if (leastPointsUpMovements.empty()) {
            bestMovement.clear();
            return;
        }
        //std::vector<std::pair<std::vector<GameConfig::eKeys>, Block>> leastPointsUpMovments = allLeastPointsUpMovements(mostPointsDownMovements);
        //if (leastPointsUpMovments.size() == 1) {
        //    bestMovement = leastPointsUpMovments[0].first;
        //    return;
        //}
        //else if (leastPointsUpMovments.size() == 0) {
        //    bestMovement.clear();
        //    return;
        //}
        //int randomValue = rand() % leastPointsUpMovments.size();
        //bestMovement = leastPointsUpMovments[randomValue].first;
        std::vector<std::pair<std::vector<GameConfig::eKeys>, Block>> mostLeftMovements = allMostLeftMovements(leastPointsUpMovements);
        if (mostLeftMovements.empty()) {
            bestMovement.clear();
            return;
        }
        bestMovement = mostLeftMovements[0].first;
    }
    this->numOfMove++;
}

//// Finds all movements with the most downward points.
//std::vector<std::pair<std::vector<GameConfig::eKeys>, Block>> ComputerUser::allMostPointsDownMovements(const std::vector<std::pair<std::vector<GameConfig::eKeys>, Block>>& allPossibleMovements) {
//    std::vector<std::pair<std::vector<GameConfig::eKeys>, Block>> allValidMovements;
//    int lowestY = getLowestY(allPossibleMovements[0].second);
//    int yOffset = 1;
//    //lowestY -= yOffset;
//    int amountAtLowestY = 0;
//    for (const auto& movement : allPossibleMovements) {
//        Board boardCopy = this->getBoard();
//        boardCopy.updateBoardWithPoints(movement.second.getBlockPoints());
//        int temp = getAmountOfPointsAtY(boardCopy, lowestY);
//        int currentLowestY = getLowestY(movement.second);
//        if (currentLowestY > lowestY) {
//            lowestY = currentLowestY;
//            allValidMovements.clear();
//            allValidMovements.push_back(movement);
//        }
//        else if (currentLowestY == lowestY && temp > amountAtLowestY) {
//            if (temp > amountAtLowestY) {
//                amountAtLowestY = temp;
//                allValidMovements.clear();
//                allValidMovements.push_back(movement);
//            }
//            else if (temp == amountAtLowestY) {
//                allValidMovements.push_back(movement);
//            }
//        }
//    }
//
//    return allValidMovements;
//}

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

// Gets the lowest Y coordinate of the given block and how much there are.
int ComputerUser::getNumOfHighestY(const Block& b, int* numOfHighest) {
    *numOfHighest = 1;
    const Point* points = b.getBlockPoints();
    int highest = points[0].getY();
    for (int i = 1; i < 4; i++) {
        if (points[i].getY() > highest) {
            highest = points[i].getY();
            *numOfHighest = 1;
        }
        else if (points[i].getY() == highest)
            (*numOfHighest)++;
    }
    return highest;
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

// Gets the highest Y coordinate of the given block and how much there are.
int ComputerUser::getNumOfLowestY(const Block& b, int* numOfLowest) {
    *numOfLowest = 1;
    const Point* points = b.getBlockPoints();
    int lowest = points[0].getY();
    for (int i = 1; i < 4; i++) {
        if (points[i].getY() > lowest) {
            lowest = points[i].getY();
            *numOfLowest = 1;
        }
        else if (points[i].getY() == lowest)
            (*numOfLowest)++;
    }
    return lowest;
}

//// Finds all movements with the least upward points.
//std::vector<std::pair<std::vector<GameConfig::eKeys>, Block>>ComputerUser::allLeastPointsUpMovements(const std::vector<std::pair<std::vector<GameConfig::eKeys>, Block>>& allPossibleMovements) {
//    std::vector<std::pair<std::vector<GameConfig::eKeys>, Block>> allValidMovements;
//    
//    if (allPossibleMovements.empty()) {
//        return allValidMovements;
//    }
//    int highestY = getHighestY(allPossibleMovements[0].second);
//    int amountAtHighestY = GameConfig::BOARD_WIDTH;
//    int yOffset = 1;
//    int temp;
//
//    for (const auto& movement : allPossibleMovements) {
//        temp = getHighestY(movement.second);
//        if (temp < highestY)
//            highestY = temp;
//
//        Board boardCopy = this->getBoard();
//        boardCopy.updateBoardWithPoints(movement.second.getBlockPoints());
//        int pointsAtY = getAmountOfPointsAtY(boardCopy, highestY - yOffset);
//
//        if (pointsAtY < amountAtHighestY) {
//            amountAtHighestY = pointsAtY;
//            allValidMovements.clear(); 
//        }
//        if (pointsAtY == amountAtHighestY) {
//            allValidMovements.push_back(movement);
//        }
//    }
//
//    return allValidMovements;
//}

// Finds all possible movements for the current moving block.
//std::vector<std::pair<std::vector<GameConfig::eKeys>, Block>> ComputerUser::findAllPossibleMovements() {
//    std::vector<std::pair<std::vector<GameConfig::eKeys>, Block>> allPossibleMovements;
//    std::vector<GameConfig::eKeys> currentMove;
//    //TODO : Maybe prioritize here if should go for deeper check using exploreAllPossibleMoves
//    //TODO : Or build another function that doesn't do left and than right movments (using for loops) and without rotations as well
//    //TODO : As in the worst case, (first movement) there are 5^17 possibilities, and most of them identical
//    //TODO : (It doesnt matter where lying I tetermino will be.)
//    //TODO : And we can use more accurate calculation based on Computer level and Highest board y.
//    int highestY = getHighestPointYAxisValueOnBoard();
//    Block myBlock = getMovingBlock();
//    int accurateStartPosition = mapComputerLevelToStartAccurateSearchYPosition();
//
//    //exploreAllPossibleMoves(myBlock, currentMove, allPossibleMovements);
//    int numOfEmptyColumnts = getAmountOfEmptyColumns();
//
//    //nonAccurateSearch(myBlock, allPossibleMovements);
//    
//    if (highestY <= accurateStartPosition && numOfEmptyColumnts <= myBlock.getIsBomb() ? 1 : 2 && getAmountOfPointsAboveY(this->board, accurateStartPosition) >= 4) {
//        exploreAllPossibleMoves(myBlock, currentMove, allPossibleMovements);
//    }
//    else {
//        nonAccurateSearch(myBlock, allPossibleMovements);
//    }
//    return allPossibleMovements;
//}

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

//SHOULD BE DELETED
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

//SHOULD BE DELETED
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

//SHOULD BE DELETED
// Maps the computer level to start an accurate search Y position.
int ComputerUser::mapComputerLevelToStartAccurateSearchYPosition() {
    switch (this->level) {
    case 0: return 6;
    case 1:return 8;
    case 2: return 9;
    }

    return 9;
}

//// NEED TO BE DELETED IN CASE NOT IN USE
//void ComputerUser::nonAccurateSearch(Block myBlock, std::vector<std::pair<std::vector<GameConfig::eKeys>, Block>>& allPossibleMovements) {
//    this->board.drawBoard(this->getSide());
//    this->getMovingBlock().drawBlock();
//    int leftDistance = getBlockDistanceFromLeftBorder(myBlock);
//    int rightDistance = getBlockDistanceFromRightBorder(myBlock);
//    Block copyBlock;
//    std::vector<GameConfig::eKeys> moves;
//
//    // Perform rotations and movements to the left
//    for (int rotateCount = 0; rotateCount < 4; rotateCount++) {
//        for (int i = 0; i <= leftDistance; i++) { // Adjusted loop condition
//            copyBlock = myBlock;
//            moves.clear();
//            // Rotate the block
//            for (int j = 0; j <= rotateCount; j++) {
//                copyBlock.rotateClockwise();
//                moves.push_back(rotateClockwise);
//            }
//            // Move the block to the left
//            for (int k = 0; k < i; k++) { // Adjusted loop condition
//                copyBlock.moveBlock(leftMove);
//                moves.push_back(leftMove);
//            }
//            // Move the block down until it collides or reaches the bottom
//            while (checkCopiedBlockCollisionWithBoard(copyBlock)) { // Added condition to check if the block reached the bottom
//                copyBlock.moveBlock(downMove);
//                moves.push_back(downMove);
//            }
//            // Add the movement sequence to the list of possible movements
//            allPossibleMovements.push_back(std::make_pair(moves, copyBlock));
//        }
//    }
//    moves.clear();
//    // Perform rotations and movements to the right
//    for (int rotateCount = 0; rotateCount < 4; rotateCount++) {
//        for (int i = 0; i <= rightDistance; i++) { // Adjusted loop condition
//            copyBlock = myBlock;
//            moves.clear();
//            // Rotate the block
//            for (int j = 0; j <= rotateCount; j++) {
//                copyBlock.rotateClockwise();
//                moves.push_back(rotateClockwise);
//            }
//            // Move the block to the right
//            for (int k = 0; k < i; k++) { // Adjusted loop condition
//                copyBlock.moveBlock(rightMove);
//                moves.push_back(rightMove);
//            }
//            // Move the block down until it collides or reaches the bottom
//            while (checkCopiedBlockCollisionWithBoard(copyBlock)) { // Added condition to check if the block reached the bottom
//                copyBlock.moveBlock(downMove);
//                moves.push_back(downMove);
//            }
//            // Add the movement sequence to the list of possible movements
//            allPossibleMovements.push_back(std::make_pair(moves, copyBlock));
//        }
//    }
//}
void ComputerUser::nonAccurateSearch(Block myBlock, std::vector<std::pair<std::vector<GameConfig::eKeys>, Block>>& allPossibleMovements) {
    this->board.drawBoard(this->getSide());
    this->getMovingBlock().drawBlock();
    int leftDistance = getBlockDistanceFromLeftBorder(myBlock);
    int rightDistance = getBlockDistanceFromRightBorder(myBlock);
    std::vector<GameConfig::eKeys> moves;

    // Evaluate all possible movements to the left
    for (int i = 0; i <= leftDistance; ++i) {
        Block copyBlock = myBlock;
        moves.clear();
        // Move the block to the left
        for (int k = 0; k < i; ++k) {
            copyBlock.moveBlock(leftMove);
            moves.push_back(leftMove);
        }
        // Rotate the block
        for (int rotation = 0; rotation < 4; ++rotation) {
            Block rotatedBlock = copyBlock;
            for (int j = 0; j < rotation; ++j) {
                rotatedBlock.rotateClockwise();
                moves.push_back(rotateClockwise);
            }
            // Move the block down until it collides or reaches the bottom
            while (checkCopiedBlockCollisionWithBoard(rotatedBlock)) {
                rotatedBlock.moveBlock(downMove);
                moves.push_back(downMove);
            }
            // Add the movement sequence to the list of possible movements
            allPossibleMovements.push_back(std::make_pair(moves, rotatedBlock));
        }
    }

    // Evaluate all possible movements to the right
    for (int i = 0; i <= rightDistance; ++i) {
        Block copyBlock = myBlock;
        moves.clear();
        // Move the block to the right
        for (int k = 0; k < i; ++k) {
            copyBlock.moveBlock(rightMove);
            moves.push_back(rightMove);
        }
        // Rotate the block
        for (int rotation = 0; rotation < 4; ++rotation) {
            Block rotatedBlock = copyBlock;
            for (int j = 0; j < rotation; ++j) {
                rotatedBlock.rotateClockwise();
                moves.push_back(rotateClockwise);
            }
            // Move the block down until it collides or reaches the bottom
            while (checkCopiedBlockCollisionWithBoard(rotatedBlock)) {
                rotatedBlock.moveBlock(downMove);
                moves.push_back(downMove);
            }
            // Add the movement sequence to the list of possible movements
            allPossibleMovements.push_back(std::make_pair(moves, rotatedBlock));
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
//
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
//    moves.clear();
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

int ComputerUser::getAmountOfEmptyColumns()  {
    int res = 0;
    bool isColumnEmpty = true;
    for (int i = 0; i < GameConfig::BOARD_WIDTH; i++) {
        for (int j = 0; j < GameConfig::BOARD_HEIGHT; j++) {
            if (this->board.getBoard()[i][j].getSymbol() != EMPTY_SPACE) {
                isColumnEmpty = false;
                break;
            }
        }
        if (isColumnEmpty)
            res++;
        isColumnEmpty = true;
    }
    return res;
}

// Finds all possible movements for the current moving block.
std::vector<std::pair<std::vector<GameConfig::eKeys>, Block>> ComputerUser::findAllPossibleMovements() {
    std::vector<std::pair<std::vector<GameConfig::eKeys>, Block>> allPossibleMovements;
    Block blockCopy = getMovingBlock();
    int leftDistance = getBlockDistanceFromLeftBorder(blockCopy);
    int rightDistance = getBlockDistanceFromRightBorder(blockCopy);
    std::vector<GameConfig::eKeys> leftMoves;
    std::vector<GameConfig::eKeys> rightMoves;
    std::vector<GameConfig::eKeys> leftMovesAfter;
    std::vector<GameConfig::eKeys> rightMovesAfter;

    for (int rotation = 0; rotation < 4; ++rotation) {
        leftMoves.clear();
        rightMoves.clear();

        Block currentBlock = blockCopy;

        for (int k = 0; k < rotation; k++) {
            currentBlock.rotateClockwise();
            leftMoves.push_back(rotateClockwise);
            rightMoves.push_back(rotateClockwise);
        }

        Block afterRotate = currentBlock;

        // Evaluate all possible movements to the left
        for (int col = 0; col <= leftDistance; ++col) {
            currentBlock = afterRotate;
            leftMovesAfter = leftMoves;
            // Move the block to the left
            for (int i = 0; i < col; ++i) {
                currentBlock.moveBlock(leftMove);
                leftMovesAfter.push_back(leftMove);
            }
            // Move the block down until it collides or reaches the bottom
            while (checkCopiedBlockCollisionWithBoard(currentBlock)) {
                currentBlock.moveBlock(downMove);
                leftMovesAfter.push_back(downMove);
            }
            // Add the movement sequence to the list of possible movements
            allPossibleMovements.push_back(std::make_pair(leftMovesAfter, currentBlock));
        }

        // Evaluate all possible movements to the right
        for (int col = 0; col <= rightDistance; ++col) {
            currentBlock = afterRotate;
            rightMovesAfter = rightMoves;
            // Move the block to the right
            for (int i = 0; i < col; ++i) {
                if (i == 4)
                {
                    continue;
                }
                currentBlock.moveBlock(rightMove);
                rightMovesAfter.push_back(rightMove);
            }
            // Move the block down until it collides or reaches the bottom
            while (checkCopiedBlockCollisionWithBoard(currentBlock)) {
                currentBlock.moveBlock(downMove);
                rightMovesAfter.push_back(downMove);
            }
            // Add the movement sequence to the list of possible movements
            allPossibleMovements.push_back(std::make_pair(rightMovesAfter, currentBlock));
        }

        if (currentBlock.getIsBomb() || currentBlock.getShape() == Block::eTetriminoShape::O)
            break;
    }
    return allPossibleMovements;
}

// Finds all movements with the most downward points.
std::vector<std::pair<std::vector<GameConfig::eKeys>, Block>> ComputerUser::allMostPointsDownMovements(const std::vector<std::pair<std::vector<GameConfig::eKeys>, Block>>& allPossibleMovements) {
    std::vector<std::pair<std::vector<GameConfig::eKeys>, Block>> allValidMovements;
    int numOfLowestY;
    int currNumOfLowestY;
    int lowestY = getNumOfLowestY(allPossibleMovements[0].second, &numOfLowestY);

    for (const auto& movement : allPossibleMovements) {
        int currLowestY = getNumOfLowestY(movement.second, &currNumOfLowestY);
        if (currLowestY > lowestY) {
            allValidMovements.clear();
            allValidMovements.push_back(movement);
            lowestY = currLowestY;
            numOfLowestY = currNumOfLowestY;
        }
        else if (currLowestY == lowestY) {
            if (currNumOfLowestY > numOfLowestY)
            {
                allValidMovements.clear();
                allValidMovements.push_back(movement);
                numOfLowestY = currNumOfLowestY;
            }
            else if (currNumOfLowestY == numOfLowestY)
                allValidMovements.push_back(movement);
        }
    }
    return allValidMovements;
}

// Finds all movements with the most downward points.
std::vector<std::pair<std::vector<GameConfig::eKeys>, Block>> ComputerUser::allLeastPointsUpMovements(const std::vector<std::pair<std::vector<GameConfig::eKeys>, Block>>& allPossibleMovements) {
    std::vector<std::pair<std::vector<GameConfig::eKeys>, Block>> allValidMovements;
    int numOfHighestY;
    int currNumOfHighestY;
    int highestY = getNumOfHighestY(allPossibleMovements[0].second, &numOfHighestY);

    for (const auto& movement : allPossibleMovements) {
        int currHighestY = getNumOfHighestY(movement.second, &currNumOfHighestY);
        if (currHighestY < highestY) {
            allValidMovements.clear();
            allValidMovements.push_back(movement);
            highestY = currHighestY;
            numOfHighestY = currNumOfHighestY;
        }
        else if (currHighestY == highestY) {
            if (currNumOfHighestY < numOfHighestY)
            {
                allValidMovements.clear();
                allValidMovements.push_back(movement);
                numOfHighestY = currNumOfHighestY;
            }
            else if (currNumOfHighestY == numOfHighestY)
                allValidMovements.push_back(movement);
        }
    }
    return allValidMovements;
}

// Finds all movements with the most left moves.
std::vector<std::pair<std::vector<GameConfig::eKeys>, Block>> ComputerUser::allMostLeftMovements(const std::vector<std::pair<std::vector<GameConfig::eKeys>, Block>>& allPossibleMovements) {
    std::vector<std::pair<std::vector<GameConfig::eKeys>, Block>> allValidMovements;
    int maxLeftMoves = 0;

    for (const auto& movement : allPossibleMovements) {
        int currLeftMoves = 0;
        for (const auto& key : movement.first) {
            if (key == leftMove)
                currLeftMoves++;
        }
        if (currLeftMoves > maxLeftMoves) {
            allValidMovements.clear();
            allValidMovements.push_back(movement);
            maxLeftMoves = currLeftMoves;
        }
        else if (currLeftMoves == maxLeftMoves) {
            allValidMovements.push_back(movement);
        }
    }
    return allValidMovements;
}