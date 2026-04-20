#ifndef LEVEL_H
#define LEVEL_H

#include <string>
#include <vector>

struct LevelData {
    std::vector<std::string> layout;
    int width = 0;
    int height = 0;
};

class Level {
public:
    Level();

    bool loadLevel(int levelNumber);
    void resetLevel();

    const LevelData& getLevelData() const;
    char getTile(int x, int y) const;
    void setTile(int x, int y, char tile);
    bool isWall(int x, int y) const;
    bool isBox(int x, int y) const;
    bool isTarget(int x, int y) const;
    bool isPlayer(int x, int y) const;
    bool isInside(int x, int y) const;
    bool isLevelComplete() const;
    bool findPlayer(int& x, int& y) const;

private:
    void loadDefaultLevel();
    void normalizeLayout();

    LevelData levelData;
    LevelData originalLevelData;
    int currentLevel;
};

#endif
