#ifndef HISTORY_H
#define HISTORY_H

#include <vector>
#include <string>

class History {
public:
    void recordMove(const std::string& move);
    std::vector<std::string> getMoveHistory() const;
    void clearHistory();

private:
    std::vector<std::string> moveHistory;
};

#endif // HISTORY_H