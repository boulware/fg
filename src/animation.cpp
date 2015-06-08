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

void animation::LoadFrameDirectory(std::string PathDirectory)
{   
    uint16 File = 0;

    std::string Path = PathDirectory + std::to_string(File) + ".png";

//    std::string Test = Directory + std::to_string(File) + ".png";
    
    std::ifstream Stream(Path);

    
    
    while(Stream.good())
    {
        Stream.close();
        
        Frames.push_back({Path});

        Stream.open(PathDirectory + std::to_string(++File) + ".png");
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
