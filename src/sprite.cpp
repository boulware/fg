#include "sprite.h"

#include <fstream>

sprite::sprite(std::string SpriteFilepath)
        :
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

        Debug::WriteString("Loaded " + std::to_string(LineNumber) + " textures from " + SpriteFilepath);
    }
    else
    {
        Debug::WriteError("Tried to open invalid sprite file (" + SpriteFilepath + ")");
    }

    if(CurrentFrame < Textures.size())
    {
        SFMLSprite.setTexture(Textures[CurrentFrame].SFMLTexture, true);
    }
}

sprite::sprite(const sprite& Other)
        :
        Textures(Other.Textures),
        CurrentFrame(0)
{
    if(CurrentFrame < Textures.size())
    {
        SFMLSprite.setTexture(Textures[CurrentFrame].SFMLTexture, true);
    }
}

void sprite::AdvanceFrame()
{
    if(++CurrentFrame >= Textures.size()) CurrentFrame = 0;

    texture& FrameTexture = Textures[CurrentFrame];
    
    SFMLSprite.setTexture(FrameTexture.SFMLTexture, true);
    SFMLSprite.setOrigin(FrameTexture.DrawOrigin);
}

void sprite::Draw(int16 X, int16 Y)
{
    SFMLSprite.setPosition(X, Y);
    Global::Window.draw(SFMLSprite);
}
    

//sprite::AdvanceFrame(

/*
collision_sprite::collision_sprite(std::string SpriteFilepath)
        :
        sprite(SpriteFilepath)
{
    
    std::string FileExtension = SpriteFilepath.substr(SpriteFilepath.find_last_of(".") + 1, std::string::npos);

    if(FileExtension == "ani")
    {
        std::string CurrentDirectory = SpriteFilepath;
        CurrentDirectory.erase(SpriteFilepath.find_last_of("/") + 1, std::string::npos);
        std::string FrameData;
    
        std::ifstream In;
        In.open(SpriteFilepath);

        uint16 LineNumber = 0;
    
        while(In.good())
        {
            In >> FrameData;
            LineNumber++;

            std::string ImageName = FrameData.substr(0, FrameData.find_first_of("("));
        
            std::string DrawOriginString; // "(x,y)"
            DrawOriginString = FrameData.substr(FrameData.find_first_of("("), FrameData.find_first_of(")"));
            sf::Vector2<int16> DrawOrigin;
            if(DrawOriginString == "()")
            {
                if(Frames.size() != 0)
                {
                    DrawOrigin = (sf::Vector2<int16>)Frames[Frames.size() - 1].Texture.DrawOrigin;
                }
                else
                {
                    Debug::WriteError(SpriteFilepath + " corrupted on LINE " + std::to_string(LineNumber) + ". DrawOrigin invalid");
                }
            }
            else
            {            
                DrawOrigin.x = std::stoi(DrawOriginString.substr(DrawOriginString.find_first_of("(") + 1, DrawOriginString.find_first_of(",") - 1));
                DrawOrigin.y = std::stoi(DrawOriginString.substr(DrawOriginString.find_first_of(",") + 1, DrawOriginString.find_first_of(")") - 1));
            }

            Frames.push_back({{CurrentDirectory + ImageName + ".png", DrawOrigin}});
        }
    }
    else
    {
        Debug::WriteError("Tried to open invalid sprite file (" + SpriteFilepath + ")");
    }
}


#include <string>
#include <fstream>

sprite::sprite(std::string SpriteFilepath)
        :
        CurrentFrame(0)
{
    LoadSpriteFromFile(SpriteFilepath);
}

void
sprite::AdvanceFrame()
{
    if(++CurrentFrame >= Frames.size()) CurrentFrame = 0;
}

void
sprite::Blit(int16 XOffset, int16 YOffset)
{
    if(Frames.size() > 0)
    {
        SFMLSprite.setPosition(XOffset, YOffset);
        SFMLSprite.setTexture(Frames[CurrentFrame].Texture.SFMLTexture);
//        Frames[CurrentFrame].Sprite.setPosition(XOffset, YOffset);
        SFMLSprite.setPosition(XOffset, YOffset);
        SFMLSprite.setOrigin((sf::Vector2f)Frames[CurrentFrame].Texture.DrawOrigin);
        Global::Window.draw(SFMLSprite);
        
        if(Global::DebugMode)
        {
//            Frames[CurrentFrame].Skeleton.Blit(XOffset, YOffset);
        }
    }
}

void sprite::LoadSpriteFromFile(std::string Filepath)
{
    if(!Frames.empty()) Frames.clear();
    
    std::string FileExtension = Filepath.substr(Filepath.find_last_of(".") + 1, std::string::npos);

    if(FileExtension == "ani")
    {
        std::string CurrentDirectory = Filepath;
        CurrentDirectory.erase(Filepath.find_last_of("/") + 1, std::string::npos);
        std::string FrameData;
    
        std::ifstream In;
        In.open(Filepath);

        uint16 LineNumber = 0;
    
        while(In.good())
        {
            In >> FrameData;
            LineNumber++;

            std::string ImageName = FrameData.substr(0, FrameData.find_first_of("("));
        
            std::string DrawOriginString; // "(x,y)"
            DrawOriginString = FrameData.substr(FrameData.find_first_of("("), FrameData.find_first_of(")"));
            sf::Vector2<int16> DrawOrigin;
            if(DrawOriginString == "()")
            {
                if(Frames.size() != 0)
                {
                    DrawOrigin = (sf::Vector2<int16>)Frames[Frames.size() - 1].Texture.DrawOrigin;
                }
                else
                {
                    Debug::WriteError(Filepath + " corrupted on LINE " + std::to_string(LineNumber) + ". DrawOrigin invalid");
                }
            }
            else
            {            
                DrawOrigin.x = std::stoi(DrawOriginString.substr(DrawOriginString.find_first_of("(") + 1, DrawOriginString.find_first_of(",") - 1));
                DrawOrigin.y = std::stoi(DrawOriginString.substr(DrawOriginString.find_first_of(",") + 1, DrawOriginString.find_first_of(")") - 1));
            }

            Frames.push_back({{CurrentDirectory + ImageName + ".png", DrawOrigin}});
        }
    }
}

void collision_sprite::LoadSpriteFromFile(std::string SpriteFilepath)
{
    
}
*/
