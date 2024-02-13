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
    std::vector<std::pair<std::vector<GameConfig::eKeys>, Block>> mostPointsDownMovements = allMostPointsDownMovements(bestScoreMovements);
    if (mostPointsDownMovements.size() == 1) {
        bestMovement = mostPointsDownMovements[0].first;
        return;
    }
    std::vector<std::pair<std::vector<GameConfig::eKeys>, Block>> leastPointsUpMovments = allLeastPointsUpMovments(mostPointsDownMovements);
    if (leastPointsUpMovments.size() == 1) {
        bestMovement = leastPointsUpMovments[0].first;
        return;
    }
    int randomValue = rand() % leastPointsUpMovments.size();
    bestMovement = leastPointsUpMovments[randomValue].first;
}


std::vector<std::pair<std::vector<GameConfig::eKeys>, Block>> ComputerUser::allMostPointsDownMovements(const std::vector<std::pair<std::vector<GameConfig::eKeys>, Block>>& allPossibleMovements) {
    std::vector<std::pair<std::vector<GameConfig::eKeys>, Block>> allValidMovements;
    int lowestY = getLowestY(allPossibleMovements[0].second);
    int amountAtLowestY = 0;
    int temp;
    int yOffset = 1;
    for (const auto& movement : allPossibleMovements) {
        temp = getLowestY(movement.second);
        if (temp > lowestY)
            lowestY = temp;
;    }
    lowestY -= yOffset;
    for (const auto& movement : allPossibleMovements) {
        Board boardCopy = this->getBoard();
        boardCopy.updateBoardWithPoints(movement.second.getBlockPoints());
        temp = getAmountOfPointsAtY(boardCopy, lowestY);
        if (temp > amountAtLowestY)
            amountAtLowestY = temp;
    }
    for (const auto& movement : allPossibleMovements) {
        Board boardCopy = this->getBoard();
        boardCopy.updateBoardWithPoints(movement.second.getBlockPoints());
        if (getAmountOfPointsAtY(boardCopy, lowestY) == amountAtLowestY) {
            allValidMovements.push_back(movement);
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
        int pointsAtY = getAmountOfPointsAtY(boardCopy, yOffset);

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
    exploreAllPossibleMoves(getMovingBlock(), currentMove, allPossibleMovements);

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
        int score = boardCopy.validateBoard();

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
    if (allMoves.size() >= 20000)
        return;
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
