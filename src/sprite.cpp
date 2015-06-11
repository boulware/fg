#include "sprite.h"

#include <fstream>

sprite::sprite(std::string SpriteFilepath, bool32 Loops)
        :
        Loops(Loops),
        AnimationEnded(false),
        CurrentFrame(0)
{    
    std::string FileExtension = SpriteFilepath.substr(SpriteFilepath.find_last_of(".") + 1, std::string::npos);

    if(FileExtension == "ani")
    {
        std::string CurrentDirectory = SpriteFilepath.substr(0, SpriteFilepath.find_last_of("/") + 1);
        std::string Line;
    
        std::ifstream In;
        In.open(SpriteFilepath);

        uint16 LineNumber = 0;
    
        while(In.good())
        {
            In >> Line;
            LineNumber++;

            std::string ImageName = Line.substr(0, Line.find_first_of("("));
        
            std::string DrawOriginString = Line.substr(Line.find_first_of("("), Line.find_first_of(")")); // "(x,y)"
            sf::Vector2f DrawOrigin;
            
            if(DrawOriginString == "()") // Use previous frame's draw origin.
            {
                if(Textures.size() != 0)
                {
                    DrawOrigin = Textures.back().DrawOrigin;
                }
                else
                {
                    Debug::WriteError(SpriteFilepath + " corrupted on LINE " + std::to_string(LineNumber) + ". Draw origin invalid.");
                }
            }
            else
            {
                try
                {
                    DrawOrigin.x = std::stoi(DrawOriginString.substr(DrawOriginString.find_first_of("(") + 1, DrawOriginString.find_first_of(",") - 1));
                    DrawOrigin.y = std::stoi(DrawOriginString.substr(DrawOriginString.find_first_of(",") + 1, DrawOriginString.find_first_of(")") - 1));
                }
                catch(...)
                {
                    Debug::WriteError(SpriteFilepath + " corrupted on LINE " + std::to_string(LineNumber) + ". Draw origin invalid.");
                }
            }

            Textures.push_back({{CurrentDirectory + ImageName + ".png", DrawOrigin}});
        }

        Debug::WriteLine("Loaded " + std::to_string(LineNumber) + " textures from " + SpriteFilepath);
    }
    else
    {
        Debug::WriteError("Tried to open invalid sprite file (" + SpriteFilepath + ")");
    }

    if(CurrentFrame < Textures.size())
    {
        UpdateTexture();
    }
}

sprite::sprite(const sprite& Other)
        :
        Loops(Other.Loops),
        AnimationEnded(Other.AnimationEnded),
        Textures(Other.Textures),
        CurrentFrame(0)
{
    if(CurrentFrame < Textures.size())
    {
        UpdateTexture();
    }
}

void
sprite::UpdateTexture()
{
    if(SFMLSprite.getTexture() != &Textures[CurrentFrame].SFMLTexture)
    {
        texture& CurrentFrameTexture = Textures[CurrentFrame];

        SFMLSprite.setTexture(CurrentFrameTexture.SFMLTexture, true);
        SFMLSprite.setOrigin(CurrentFrameTexture.DrawOrigin);
    }
}
    

void
sprite::AdvanceFrame()
{
    if(Loops)
    {
        if(++CurrentFrame >= Textures.size()) CurrentFrame = 0;

        UpdateTexture();
    }
    else
    {
        if(CurrentFrame != Textures.size() - 1)
        {
            CurrentFrame++;
            UpdateTexture();
        }
        else
        {
            AnimationEnded = true;
        }
    }
}

void
sprite::Draw(int16 X, int16 Y)
{
    SFMLSprite.setPosition(X, Y);
    Global::Window.draw(SFMLSprite);
}
