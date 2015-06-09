#include "animation.h"

#include "fstream"

animation::animation() :
        CurrentFrame(0)
{
}

void
animation::AppendFrame(std::string Filename)
{
    Frames.push_back({Filename});
}

void animation::LoadFrameDirectory(std::string PathDirectory, alignment HAlign, alignment VAlign)
{   
    uint16 File = 0;

    std::string Path = PathDirectory + std::to_string(File) + ".png";
    
    std::ifstream Stream(Path);
    
    while(Stream.good())
    {
        Stream.close();
        
        Frames.push_back({Path});
        Blit::AlignSprite(Frames[Frames.size() - 1].Sprite, HAlign, VAlign);

        Path = PathDirectory + std::to_string(++File) + ".png";
        
        Stream.open(Path);
    }
}

void
animation::AdvanceFrame()
{
    if(++CurrentFrame >= Frames.size()) CurrentFrame = 0;
}

void
animation::Blit(int16 XOffset, int16 YOffset)
{
    if(Frames.size() > 0)
    {
        Frames[CurrentFrame].Sprite.setPosition(XOffset, YOffset);
        Global::Window.draw(Frames[CurrentFrame].Sprite);
        
        if(Global::DebugMode)
        {
            Frames[CurrentFrame].Skeleton.Blit(XOffset, YOffset);
        }
    }
}
