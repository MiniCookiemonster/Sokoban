#include "history.h"

void History::recordMove(const std::string& move) {
    moveHistory.push_back(move);
}

std::vector<std::string> History::getMoveHistory() const {
    return moveHistory;
}

void History::clearHistory() {
    moveHistory.clear();
}
