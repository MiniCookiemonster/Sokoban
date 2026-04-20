#include "game.h"

namespace {
const char TARGET = '.';
const char BOX = '$';
const char BOX_ON_TARGET = '*';
const char PLAYER = '@';
const char PLAYER_ON_TARGET = '+';
const char FLOOR = ' ';
}

Game::Game() : playerX(0), playerY(0), moveCount(0) {
    startGame();
}

void Game::startGame() {
    currentLevel.loadLevel(1);
    moveHistory.clearHistory();
    moveCount = 0;
    statusMessage = "Use arrow keys or W/A/S/D to move. R resets the level.";
    refreshPlayerPosition();
}

bool Game::movePlayer(int dx, int dy) {
    const int nextX = playerX + dx;
    const int nextY = playerY + dy;
    const int boxNextX = nextX + dx;
    const int boxNextY = nextY + dy;
    const char nextTile = currentLevel.getTile(nextX, nextY);

    if (currentLevel.isWall(nextX, nextY)) {
        statusMessage = "Blocked by a wall.";
        return false;
    }

    bool pushedBox = false;
    if (currentLevel.isBox(nextX, nextY)) {
        if (currentLevel.isWall(boxNextX, boxNextY) || currentLevel.isBox(boxNextX, boxNextY)) {
            statusMessage = "The box is stuck and cannot be pushed.";
            return false;
        }

        currentLevel.setTile(boxNextX, boxNextY, currentLevel.isTarget(boxNextX, boxNextY) ? BOX_ON_TARGET : BOX);
        currentLevel.setTile(nextX, nextY, nextTile == BOX_ON_TARGET ? TARGET : FLOOR);
        pushedBox = true;
    }

    const char currentPlayerTile = currentLevel.getTile(playerX, playerY);
    currentLevel.setTile(playerX, playerY, currentPlayerTile == PLAYER_ON_TARGET ? TARGET : FLOOR);
    currentLevel.setTile(nextX, nextY, currentLevel.isTarget(nextX, nextY) ? PLAYER_ON_TARGET : PLAYER);

    playerX = nextX;
    playerY = nextY;
    ++moveCount;
    addHistoryEntry(directionName(dx, dy), pushedBox);
    if (pushedBox && isBoxInDeadCorner(boxNextX, boxNextY)) {
        statusMessage = "Warning: the box is stuck in a corner. Press R to reset.";
    } else {
        statusMessage = pushedBox ? "Box pushed." : "Player moved.";
    }

    if (checkWinCondition()) {
        statusMessage = "Congratulations, all boxes are on targets!";
    }

    return true;
}

void Game::resetGame() {
    currentLevel.resetLevel();
    moveHistory.clearHistory();
    moveCount = 0;
    statusMessage = "Level reset.";
    refreshPlayerPosition();
}

bool Game::checkWinCondition() const {
    return currentLevel.isLevelComplete();
}

const Level& Game::getCurrentLevel() const {
    return currentLevel;
}

const History& Game::getHistory() const {
    return moveHistory;
}

int Game::getMoveCount() const {
    return moveCount;
}

int Game::getPlayerX() const {
    return playerX;
}

int Game::getPlayerY() const {
    return playerY;
}

std::string Game::getStatusMessage() const {
    return statusMessage;
}

void Game::refreshPlayerPosition() {
    currentLevel.findPlayer(playerX, playerY);
}

void Game::addHistoryEntry(const std::string& direction, bool pushedBox) {
    moveHistory.recordMove(std::to_string(moveCount) + ". " + direction + (pushedBox ? " push" : " move"));
}

bool Game::isBoxInDeadCorner(int x, int y) const {
    if (currentLevel.isTarget(x, y)) {
        return false;
    }

    const bool wallUp = currentLevel.isWall(x, y - 1);
    const bool wallDown = currentLevel.isWall(x, y + 1);
    const bool wallLeft = currentLevel.isWall(x - 1, y);
    const bool wallRight = currentLevel.isWall(x + 1, y);

    return (wallUp || wallDown) && (wallLeft || wallRight);
}

std::string Game::directionName(int dx, int dy) {
    if (dx < 0) {
        return "Left";
    }
    if (dx > 0) {
        return "Right";
    }
    if (dy < 0) {
        return "Up";
    }
    return "Down";
}
