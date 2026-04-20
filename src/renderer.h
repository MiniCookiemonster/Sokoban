#ifndef RENDERER_H
#define RENDERER_H

#include "game.h"

#include <windows.h>

class Renderer {
public:
    Renderer();

    void renderGame(HDC hdc, const Game& game, const RECT& clientRect) const;

private:
    void drawTile(HDC hdc, const RECT& rect, char tile) const;
    void drawCenteredText(HDC hdc, const RECT& rect, const char* text) const;
};

#endif
