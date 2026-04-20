#include "renderer.h"

#include <algorithm>
#include <string>
#include <vector>

namespace {
const char WALL = '#';
const char TARGET = '.';
const char BOX = '$';
const char BOX_ON_TARGET = '*';
const char PLAYER = '@';
const char PLAYER_ON_TARGET = '+';
const int SIDE_PANEL_WIDTH = 230;
const int TILE_SIZE = 44;

COLORREF rgb(int r, int g, int b) {
    return RGB(r, g, b);
}

void fillRect(HDC hdc, const RECT& rect, COLORREF color) {
    HBRUSH brush = CreateSolidBrush(color);
    FillRect(hdc, &rect, brush);
    DeleteObject(brush);
}
}

Renderer::Renderer() = default;

void Renderer::renderGame(HDC hdc, const Game& game, const RECT& clientRect) const {
    fillRect(hdc, clientRect, rgb(242, 235, 219));

    const LevelData& data = game.getCurrentLevel().getLevelData();
    const int boardWidth = data.width * TILE_SIZE;
    const int boardHeight = data.height * TILE_SIZE;
    const int boardX = 24;
    const int boardY = 24;

    RECT boardShadow = {boardX + 5, boardY + 5, boardX + boardWidth + 5, boardY + boardHeight + 5};
    fillRect(hdc, boardShadow, rgb(198, 184, 157));

    for (int y = 0; y < data.height; ++y) {
        for (int x = 0; x < data.width; ++x) {
            RECT tileRect = {
                boardX + x * TILE_SIZE,
                boardY + y * TILE_SIZE,
                boardX + (x + 1) * TILE_SIZE,
                boardY + (y + 1) * TILE_SIZE
            };
            drawTile(hdc, tileRect, data.layout[y][x]);
        }
    }

    const int panelX = std::max(boardX + boardWidth + 30, clientRect.right - SIDE_PANEL_WIDTH);
    RECT titleRect = {panelX, 24, clientRect.right - 24, 58};
    HFONT titleFont = CreateFontA(28, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET,
                                  OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY,
                                  DEFAULT_PITCH | FF_SWISS, "Segoe UI");
    HFONT oldFont = static_cast<HFONT>(SelectObject(hdc, titleFont));
    SetBkMode(hdc, TRANSPARENT);
    SetTextColor(hdc, rgb(58, 46, 35));
    DrawTextA(hdc, "Sokoban", -1, &titleRect, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
    SelectObject(hdc, oldFont);
    DeleteObject(titleFont);

    RECT infoRect = {panelX, 75, clientRect.right - 24, 112};
    std::string moves = "Steps: " + std::to_string(game.getMoveCount());
    drawCenteredText(hdc, infoRect, moves.c_str());

    RECT statusRect = {panelX, 124, clientRect.right - 24, 178};
    DrawTextA(hdc, game.getStatusMessage().c_str(), -1, &statusRect, DT_LEFT | DT_WORDBREAK);

    RECT helpRect = {panelX, 188, clientRect.right - 24, 250};
    DrawTextA(hdc, "Move: Arrow keys / W A S D\nReset: R", -1, &helpRect, DT_LEFT | DT_WORDBREAK);

    RECT historyTitle = {panelX, 268, clientRect.right - 24, 296};
    DrawTextA(hdc, "History", -1, &historyTitle, DT_LEFT | DT_SINGLELINE);

    const std::vector<std::string> history = game.getHistory().getMoveHistory();
    const int first = std::max(0, static_cast<int>(history.size()) - 12);
    int y = 300;
    for (int i = first; i < static_cast<int>(history.size()); ++i) {
        RECT row = {panelX, y, clientRect.right - 24, y + 22};
        DrawTextA(hdc, history[i].c_str(), -1, &row, DT_LEFT | DT_SINGLELINE | DT_END_ELLIPSIS);
        y += 22;
    }
}

void Renderer::drawTile(HDC hdc, const RECT& rect, char tile) const {
    COLORREF fill = rgb(229, 215, 190);
    COLORREF border = rgb(191, 171, 139);
    const char* label = "";

    switch (tile) {
    case WALL:
        fill = rgb(102, 81, 59);
        border = rgb(74, 56, 40);
        break;
    case TARGET:
        fill = rgb(232, 206, 143);
        label = ".";
        break;
    case BOX:
        fill = rgb(188, 121, 65);
        border = rgb(130, 80, 42);
        label = "B";
        break;
    case BOX_ON_TARGET:
        fill = rgb(92, 157, 96);
        border = rgb(58, 112, 63);
        label = "B";
        break;
    case PLAYER:
        fill = rgb(79, 133, 178);
        border = rgb(45, 88, 126);
        label = "P";
        break;
    case PLAYER_ON_TARGET:
        fill = rgb(95, 157, 178);
        border = rgb(48, 101, 119);
        label = "P";
        break;
    default:
        break;
    }

    fillRect(hdc, rect, fill);

    HPEN pen = CreatePen(PS_SOLID, 1, border);
    HGDIOBJ oldPen = SelectObject(hdc, pen);
    HGDIOBJ oldBrush = SelectObject(hdc, GetStockObject(NULL_BRUSH));
    Rectangle(hdc, rect.left, rect.top, rect.right, rect.bottom);
    SelectObject(hdc, oldBrush);
    SelectObject(hdc, oldPen);
    DeleteObject(pen);

    if (label[0] != '\0') {
        drawCenteredText(hdc, rect, label);
    }
}

void Renderer::drawCenteredText(HDC hdc, const RECT& rect, const char* text) const {
    SetBkMode(hdc, TRANSPARENT);
    SetTextColor(hdc, rgb(46, 36, 28));
    DrawTextA(hdc, text, -1, const_cast<RECT*>(&rect), DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}
