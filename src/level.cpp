#include "level.h"

#include <algorithm>
#include <fstream>
#include <string>

namespace {
const char WALL = '#';
const char TARGET = '.';
const char BOX = '$';
const char BOX_ON_TARGET = '*';
const char PLAYER = '@';
const char PLAYER_ON_TARGET = '+';
const char FLOOR = ' ';
}

Level::Level() : currentLevel(0) {
    loadDefaultLevel();
}

bool Level::loadLevel(int levelNumber) {
    std::ifstream levelFile("levels/level" + std::to_string(levelNumber) + ".txt");
    if (!levelFile.is_open()) {
        loadDefaultLevel();
        currentLevel = 0;
        return false;
    }

    levelData.layout.clear();
    std::string line;
    while (std::getline(levelFile, line)) {
        levelData.layout.push_back(line);
    }

    currentLevel = levelNumber;
    normalizeLayout();
    originalLevelData = levelData;
    return true;
}

void Level::resetLevel() {
    levelData = originalLevelData;
}

const LevelData& Level::getLevelData() const {
    return levelData;
}

char Level::getTile(int x, int y) const {
    if (!isInside(x, y)) {
        return WALL;
    }
    return levelData.layout[y][x];
}

void Level::setTile(int x, int y, char tile) {
    if (isInside(x, y)) {
        levelData.layout[y][x] = tile;
    }
}

bool Level::isWall(int x, int y) const {
    return getTile(x, y) == WALL;
}

bool Level::isBox(int x, int y) const {
    const char tile = getTile(x, y);
    return tile == BOX || tile == BOX_ON_TARGET;
}

bool Level::isTarget(int x, int y) const {
    const char tile = getTile(x, y);
    return tile == TARGET || tile == BOX_ON_TARGET || tile == PLAYER_ON_TARGET;
}

bool Level::isPlayer(int x, int y) const {
    const char tile = getTile(x, y);
    return tile == PLAYER || tile == PLAYER_ON_TARGET;
}

bool Level::isInside(int x, int y) const {
    return y >= 0 && y < levelData.height && x >= 0 && x < levelData.width;
}

bool Level::isLevelComplete() const {
    for (const std::string& row : levelData.layout) {
        if (row.find(BOX) != std::string::npos) {
            return false;
        }
    }
    return true;
}

bool Level::findPlayer(int& x, int& y) const {
    for (int row = 0; row < levelData.height; ++row) {
        for (int col = 0; col < levelData.width; ++col) {
            if (isPlayer(col, row)) {
                x = col;
                y = row;
                return true;
            }
        }
    }
    return false;
}

void Level::loadDefaultLevel() {
    levelData.layout = {
        "########",
        "#  .   #",
        "#  $   #",
        "#  @   #",
        "#      #",
        "########"
    };
    normalizeLayout();
    originalLevelData = levelData;
}

void Level::normalizeLayout() {
    levelData.height = static_cast<int>(levelData.layout.size());
    levelData.width = 0;
    for (const std::string& row : levelData.layout) {
        levelData.width = std::max(levelData.width, static_cast<int>(row.size()));
    }
    for (std::string& row : levelData.layout) {
        row.resize(levelData.width, FLOOR);
    }
}
