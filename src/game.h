#if !defined(GAME_H)

#include "Globals.h"
#include "input_buffer.h"

#include "fighter.h"

class game
{
private:    
    input_buffer PrevFrameInput;
    input_buffer ThisFrameInput;

    input_buffer PrevLoopInput;
    input_buffer ThisLoopInput;

    sf::RenderTexture Buffer_;
    fighter Fighter;
public:
    game();
    bool32 IsRunning;

    bool32 Paused;
    bool32 AdvancingFrame;

    void HandleInput();
    void Update();
    void Blit();
};

#define GAME_H
#endif
