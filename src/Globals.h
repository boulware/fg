#if !defined(GLOBALS_H)

#include <string>

#include "Constants.h"

#include "timer.h"

class game;

namespace Global
{
    global_variable game* Game;
    global_variable HWND Window;

    // Game loop variables
    global_variable double UpdatesPerSecond = 60.0;
    global_variable time FrameTime = time(1.0/Global::UpdatesPerSecond, unit::s);
    global_variable uint16 MaxFrameSkip = 10;

    std::string ImagePath = "w:/fg/build/img/";

    bool32 DebugMode = false;
}

#define GLOBALS_H
#endif
