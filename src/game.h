#ifndef GAME_H
#define GAME_H

#include "history.h"
#include "level.h"

#include <string>

class Game {
public:
    Game();

    void startGame();
    bool movePlayer(int dx, int dy);
    void resetGame();
    bool checkWinCondition() const;

    const Level& getCurrentLevel() const;
    const History& getHistory() const;
    int getMoveCount() const;
    int getPlayerX() const;
    int getPlayerY() const;
    std::string getStatusMessage() const;

private:
    void refreshPlayerPosition();
    void addHistoryEntry(const std::string& direction, bool pushedBox);
    static std::string directionName(int dx, int dy);

    Level currentLevel;
    History moveHistory;
    int playerX;
    int playerY;
    int moveCount;
    std::string statusMessage;
};

#endif
