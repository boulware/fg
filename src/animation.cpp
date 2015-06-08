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

void animation::LoadFrameDirectory(std::string Directory)
{
    uint16 File = 0;
    
    std::ifstream Stream(Directory + std::to_string(File) + ".png");
    
    while(Stream.good())
    {
        Stream.close();
        
        Frames.push_back({Directory + std::to_string(File++) + ".png"});

        Stream.open(Directory + std::to_string(File) + ".png");
    }
}

void
animation::AdvanceFrame()
{
    if(++CurrentFrame >= Frames.size()) CurrentFrame = 0;
}

void
animation::Blit(bitmap* DestBitmap, int16 XOffset, int16 YOffset)
{
    if(Frames.size() > 0)
    {
        Frames[CurrentFrame].Sprite.Blit(DestBitmap,
                                         XOffset, YOffset,
                                         alignment::Center, alignment::Left);
        if(Global::DebugMode)
        {
            Frames[CurrentFrame].Skeleton.Blit(DestBitmap,
                                               XOffset, YOffset);
        }
    }
}
