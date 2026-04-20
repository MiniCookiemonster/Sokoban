#ifndef INPUT_H
#define INPUT_H

#include <windows.h>

class Input {
public:
    static bool keyToDirection(WPARAM key, int& dx, int& dy);
};

#endif
