#include "input.h"

bool Input::keyToDirection(WPARAM key, int& dx, int& dy) {
    dx = 0;
    dy = 0;

    switch (key) {
    case VK_UP:
    case 'W':
        dy = -1;
        return true;
    case VK_DOWN:
    case 'S':
        dy = 1;
        return true;
    case VK_LEFT:
    case 'A':
        dx = -1;
        return true;
    case VK_RIGHT:
    case 'D':
        dx = 1;
        return true;
    default:
        return false;
    }
}
