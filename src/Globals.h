#if !defined(GLOBALS_H)

#include <string>

#include "Constants.h"

#include "bitmap.h"

#include "SFML/System.hpp"
#include "SFML/Graphics.hpp"

class game;

namespace Global
{
    global_variable game* Game;
    global_variable sf::RenderWindow Window;

    // Game loop variables
    global_variable double UpdatesPerSecond = 60.0;
    global_variable sf::Time FrameTime = sf::seconds(1.0/UpdatesPerSecond);
    global_variable uint16 MaxFrameSkip = 10;

    std::string ImagePath = "w:/build/fg/img/";

    bitmap LoadFailBitmap(ImagePath + "LoadFail.png");

    bool32 DebugMode = false;
}

#define GLOBALS_H
#endif
