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
        std::vector<std::pair<std::vector<GameConfig::eKeys>, Block>> mostLeftMovements = allMostLeftMovements(leastPointsUpMovements);
        if (mostLeftMovements.empty()) {
            bestMovement.clear();
            return;
        }
        bestMovement = mostLeftMovements[0].first;
    }
    this->numOfMove++;
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
            // So it won't rotate outside the board
            if (currentBlock.getShape() == Block::eTetriminoShape::I)
            {
                currentBlock.moveBlock(downMove);
                leftMoves.push_back(downMove);
                rightMoves.push_back(downMove);
            }
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
            for (int i = 0; i <= col; ++i) {
                currentBlock.moveBlock(leftMove);
                leftMovesAfter.push_back(leftMove);
            }
            // Move the block down until it collides or reaches the bottom
            Block beforeBlockedBlock = currentBlock;
            while (checkCopiedBlockCollisionWithBoard(currentBlock)) {
                beforeBlockedBlock = currentBlock;
                currentBlock.moveBlock(downMove);
                leftMovesAfter.push_back(downMove);
            }
            // Add the movement sequence to the list of possible movements
            allPossibleMovements.push_back(std::make_pair(leftMovesAfter, beforeBlockedBlock));
        }

        // Evaluate all possible movements to the right
        for (int col = 0; col <= rightDistance; ++col) {
            currentBlock = afterRotate;
            rightMovesAfter = rightMoves;
            // Move the block to the right
            for (int i = 0; i <= col; ++i) {
                currentBlock.moveBlock(rightMove);
                rightMovesAfter.push_back(rightMove);
            }
            // Move the block down until it collides or reaches the bottom
            Block beforeBlockedBlock = currentBlock;
            while (checkCopiedBlockCollisionWithBoard(currentBlock)) {
                beforeBlockedBlock = currentBlock;
                currentBlock.moveBlock(downMove);
                rightMovesAfter.push_back(downMove);
            }
            // Add the movement sequence to the list of possible movements
            allPossibleMovements.push_back(std::make_pair(rightMovesAfter, beforeBlockedBlock));
        }

        // Rotation is not needed for bomb or for the shape O
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