#include "game.h"

game::game()
        :
        Fighter(100, 500),
        Paused(false),
        AdvancingFrame(false),
        IsRunning(true)
{   
}

void
game::Update()
{   
    Fighter.Update();
}

void
game::Blit()
{
    Global::Window.clear({30, 30, 30, 255});

    sf::RectangleShape Floor({(float)Const::WindowWidth, 1});
    Floor.setOutlineColor(sf::Color::White);
    Floor.setPosition(0, 500);
    Global::Window.draw(Floor);
    
    Fighter.Draw();

    Global::Window.display();

    if(AdvancingFrame)
    {
        AdvancingFrame = false;
        Paused = true;
    }
}

void
game::HandleInput()
{
    FetchAndParseInput(&ThisLoopInput, &PrevLoopInput);
  
    if(ThisLoopInput.FrameStop.WasPressed)
    {
        Paused = !Paused;
    }

    if(ThisLoopInput.HitboxToggle.WasPressed)
    {
        Global::DebugMode = !Global::DebugMode;
    }
  
    if(Paused)
    {
        if(ThisLoopInput.FrameAdvance.WasPressed)
        {
            FetchAndParseInput(&ThisFrameInput, &PrevFrameInput);
            Fighter.HandleInput(ThisFrameInput);
            Update();            
        }
    }
    else
    {
        ThisFrameInput = ThisLoopInput;
        PrevFrameInput = PrevLoopInput;

        Fighter.HandleInput(ThisFrameInput);
        Update();
    }
}

