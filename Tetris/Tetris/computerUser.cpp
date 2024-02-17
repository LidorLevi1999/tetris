// Implementation file for the User class.


#include "computerUser.h"
#include "gameConfig.h"
#include <algorithm> 
#include <random>

void ComputerUser::handleMovement(GameConfig::eKeys direction) {
    if (bestMovement.size() > 0) {
        GameConfig::eKeys movment = *(bestMovement.begin());
        if (movment == rotateClockwise)
            this->rotateMovingBlock();
        else if (movment == rotateCounterClockwise)
            this->rotateMovingBlock(false);
        else this->moveMovingBlock(movment);
        bestMovement.erase(bestMovement.begin());
    }
}

void ComputerUser::createNewMovingBlock() {
	User::createNewMovingBlock();
	calculateBestMovement();
}

void ComputerUser::calculateBestMovement() {
    std::vector<std::pair<std::vector<GameConfig::eKeys>, Block>> allPossibleMovements = findAllPossibleMovements();
    std::vector<std::pair<std::vector<GameConfig::eKeys>, Block>> bestScoreMovements = allBestScoreMovement(allPossibleMovements);
    if (bestScoreMovements.size() == 1) {
        bestMovement = bestScoreMovements[0].first;
        return;
    }
    else if (bestScoreMovements.size() == 0) {
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


int ComputerUser::getAmountOfPointsAtY(Board& b, const int y) {
    int res = 0;
    for (int i = 0; i < GameConfig::BOARD_WIDTH; i++) {
        if (b.getBoard()[i][y].getSymbol() != ' ')
            res++;
    }
    return res;
}

int ComputerUser::getLowestY(const Block& b) {
    const Point* points = b.getBlockPoints();
    int lowest = points[0].getY();
    for (int i = 1; i < 4; i++) {
        if (points[i].getY() > lowest)
            lowest = points[i].getY();
    }
    return lowest;
}


int ComputerUser::getHighestY(const Block& b) {
    const Point* points = b.getBlockPoints();
    int highest = points[0].getY();
    for (int i = 1; i < 4; i++) {
        if (points[i].getY() < highest)
            highest = points[i].getY();
    }
    return highest;
}

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
    if (highestY <= accurateStartPosition && getAmountOfPointsAboveY(this->board , accurateStartPosition) >= 4) {
        exploreAllPossibleMoves(myBlock, currentMove, allPossibleMovements);
    }
    else {
        nonAccurateSearch(myBlock, allPossibleMovements);
    }
    return allPossibleMovements;
}

int ComputerUser::calculateMovingBlockDistanceFromLeftBorder() {
	const Point* points = this->movingBlock.getBlockPoints();
	int minX = points[0].getX();
	for (int i = 1; i < 4; i++) {
		if (points[i].getX() < minX)
			minX = points[i].getX();
	}
	int xOffset = this->getSide() == 'L' ? 1 : GameConfig::RIVAL_POS + 1;
	return minX - xOffset;
}


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


int ComputerUser::getHighestPointYAxisValueOnBoard() {
    Board copyBoard = this->getBoard();
    int res = GameConfig::BOARD_HEIGHT;
    for (int i = GameConfig::BOARD_HEIGHT - 1; i >= 0; i--) {
        for (int j = 0; j < GameConfig::BOARD_WIDTH; j++) {
            if (copyBoard.getBoard()[j][i].getSymbol() == '#' && res > i) {
                res = i;
            }
        }
    }
    return res;
}

int ComputerUser::mapComputerLevelToStartAccurateSearchYPosition() {
    switch (this->level) {
    case 0: return 6;
    case 1:return 8;
    case 2: return 9;
    }

    return 9;
}

void ComputerUser::nonAccurateSearch(Block myBlock, std::vector<std::pair<std::vector<GameConfig::eKeys>, Block>>& allPossibleMovements) {
    this->board.drawBoard(this->getSide());
    this->getMovingBlock().drawBlock();
    int leftDistance = getBlockDistanceFromLeftBorder(myBlock);
    int rightDistance = getBlockDistanceFromRightBorder(myBlock);
    Block copyBlock;
    std::vector<GameConfig::eKeys> moves;
    copyBlock.moveBlock(downMove);
    moves.push_back(downMove);
    // Perform rotations and movements to the left
    for (int rotateCount = 0; rotateCount < 4; rotateCount++) {
        for (int i = leftDistance; i >= 0; i--) {
            copyBlock = myBlock;
            moves.clear();
            for (int j = 0; j <= rotateCount; j++) {
                copyBlock.rotateClockwise();
                moves.push_back(rotateClockwise);
                copyBlock.moveBlock(downMove);
            }
            for (int k = 0; k <= i; k++) {
                copyBlock.moveBlock(leftMove);  // Move left
                moves.push_back(leftMove);
                copyBlock.moveBlock(downMove);
            }
            while (true) {
                Block previousCopyBlock = copyBlock;  
                copyBlock.moveBlock(downMove);

                if (!checkCopiedBlockCollisionWithBoard(copyBlock)) {
                    allPossibleMovements.push_back(std::make_pair(moves, previousCopyBlock));
                    break;
                }
            }
        }
    }

    // Perform rotations and movements to the right
    for (int rotateCount = 0; rotateCount < 4; rotateCount++) {
        for (int i = rightDistance; i >= 0; i--) {
            copyBlock = myBlock;
            moves.clear();

            for (int j = 0; j <= rotateCount; j++) {
                copyBlock.rotateClockwise();
                moves.push_back(rotateClockwise);
                copyBlock.moveBlock(downMove);
            }
            for (int k = 0; k <= i; k++) {
                copyBlock.moveBlock(rightMove);  // Move left
                moves.push_back(rightMove);
                copyBlock.moveBlock(downMove);
            }
            while (true) {
                Block previousCopyBlock = copyBlock;
                copyBlock.moveBlock(downMove);
                if (!checkCopiedBlockCollisionWithBoard(copyBlock)) {
                    allPossibleMovements.push_back(std::make_pair(moves, previousCopyBlock));
                    break;
                }
            }
        }
    }
}


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

int ComputerUser::getAmountOfPointsAboveY(Board& b, const int y) {
    int totalPoints = 0;
    for (int currentY = y; currentY >= 0; --currentY) 
        totalPoints += getAmountOfPointsAtY(b, currentY);
    return totalPoints;
}
