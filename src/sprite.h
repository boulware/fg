#if !defined(SPRITE_H)

#include <string>

#include "Constants.h"
//#include "skeleton.h"

class sprite
{
private:
    struct texture
    {
        sf::Texture SFMLTexture;
        sf::Vector2f DrawOrigin;

        texture(std::string TextureFilepath, sf::Vector2f DrawOrigin)
                :
                DrawOrigin(DrawOrigin)
        {
            if(!SFMLTexture.loadFromFile(TextureFilepath)) Debug::WriteError("Failed to load texture (" + TextureFilepath + ")");            
        }
    };
    
    std::vector<texture> Textures;
    sf::Sprite SFMLSprite;

    uint16 CurrentFrame;
public:
    sprite(std::string SpriteFilepath);
    sprite(const sprite& Other);

    void Reset() { CurrentFrame = 0; }
    void UpdateTexture();
    void AdvanceFrame();
    void Draw(int16, int16);
};

/*
class sprite
{
private:
    // TODO(tyler): This can probably be optimized to a fixed-size structure if needed.
    std::vector<frame> Frames;
    uint16 CurrentFrame;

    sf::Sprite SFMLSprite;
public:
    sprite(std::string SpriteFilepath);

    void AppendFrame(std::string Filename);
    void AdvanceFrame();
    void Blit(int16 XOffset, int16 YOffset);

    virtual void LoadSpriteFromFile(std::string SpriteFilepath);
};

class collision_sprite : public sprite
{
public:
    void LoadSpriteFromFile(std::string SpriteFilepath);
};
*/
#define SPRITE_H
#endif
