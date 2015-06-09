#include "game.h"

game::game()
        :
        PrevFrameInput(),
        ThisFrameInput(),
        Fighter(100, 500),
        Paused(false),
        AdvancingFrame(false)
{   
    Fighter.Animation.LoadFrameDirectory(Global::ImagePath + "RedSquare/Neutral/", alignment::Center, alignment::Right);

    IsRunning = true;
}

void
game::Update()
{   
    Fighter.HandleInput(&ThisFrameInput);
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
    
    Fighter.Blit();

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
    FetchAndParseInput(&ThisFrameInput, &PrevFrameInput);

    if(ThisFrameInput.HitboxToggle.WasPressed)
    {
        Global::DebugMode = !Global::DebugMode;
    }
    
    if(ThisFrameInput.FrameStop.WasPressed)
    {
        Paused = !Paused;
    }
    if(Paused)
    {
        if(ThisFrameInput.FrameAdvance.WasPressed)
        {
            HandleInput();
            Update();
        }
        Blit();
    }
}

