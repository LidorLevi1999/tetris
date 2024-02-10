// Implementation file for the User class.


#include "computerUser.h"
#include "gameConfig.h"
#include <algorithm> 
#include <random>

void ComputerUser::handleMovement(GameConfig::eKeys direction) {

}

void ComputerUser::createNewMovingBlock() {
	User::createNewMovingBlock();
	calculateBestMovement();
}

void ComputerUser::calculateBestMovement() {
    std::vector<std::pair<std::vector<GameConfig::eKeys>, Block>> allPossibleMovements = findAllPossibleMovements();
    std::vector<std::pair<std::vector<GameConfig::eKeys>, Block>> bestScoreMovements = allBestScoreMovement(allPossibleMovements);
    if (bestScoreMovements.size() == 1)
        bestMovement = bestScoreMovements[0].first;
    else {

    }
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
        if (score > maxScore)
            maxScore = score;
    }
    for (const auto& movement : allPossibleMovements) {
        Board boardCopy = this->getBoard();
        boardCopy.updateBoardWithPoints(movement.second.getBlockPoints());
        int score = boardCopy.validateBoard();
        if (score == maxScore) {
            bestScoreMovements.push_back(movement);
        }
    }
    return bestScoreMovements;
}



// Recursive function to explore all possible moves
void ComputerUser::exploreAllPossibleMoves(Block& block, std::vector<GameConfig::eKeys>& moves, std::vector<std::pair<std::vector<GameConfig::eKeys>, Block>>& allMoves)
{
    if (allMoves.size() > 2000)
        return;
    Block copyBlock = block;
    copyBlock.moveBlock(downMove);
    if (!checkCopiedBlockCollisionWithBoard(copyBlock)) {
        allMoves.push_back(std::make_pair(moves, block));
        return;
    }
    else {
        block.moveBlock(downMove);
        moves.push_back(downMove);
    }

    Block downBlock = block;
    std::vector<GameConfig::eKeys> downMoves = moves;
    downBlock.moveBlock(downMove);
    downMoves.push_back(downMove);

    if (checkCopiedBlockCollisionWithBoard(downBlock)) {
        exploreAllPossibleMoves(downBlock, downMoves, allMoves);
    }

    Block leftBlock = block;
    std::vector<GameConfig::eKeys> leftMoves = moves;
    leftBlock.moveBlock(leftMove);
    leftMoves.push_back(leftMove);
    if (checkCopiedBlockCollisionWithBoard(leftBlock)) {
        exploreAllPossibleMoves(leftBlock, leftMoves, allMoves);
    }

    Block rightBlock = block;
    std::vector<GameConfig::eKeys> rightMoves = moves;
    rightBlock.moveBlock(rightMove);
    rightMoves.push_back(rightMove);
    if (checkCopiedBlockCollisionWithBoard(rightBlock)) {
        exploreAllPossibleMoves(rightBlock, rightMoves, allMoves);
    }

    Block rotatedBlock = block;
    std::vector<GameConfig::eKeys> rotateMoves = moves;
    rotatedBlock.rotateClockwise();
    rotateMoves.push_back(rotateClockwise);
    if (checkCopiedBlockCollisionWithBoard(rotatedBlock)) {
        exploreAllPossibleMoves(rotatedBlock, rotateMoves, allMoves);
    }

    Block rotatedCounterBlock = block;
    std::vector<GameConfig::eKeys> rotateCounterMoves = moves;
    rotatedCounterBlock.rotateCounterClockwise();
    rotateCounterMoves.push_back(rotateCounterClockwise);
    if (checkCopiedBlockCollisionWithBoard(rotatedCounterBlock)) {
        exploreAllPossibleMoves(rotatedCounterBlock, rotateCounterMoves, allMoves);
    }
}
