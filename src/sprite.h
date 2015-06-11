#if !defined(SPRITE_H)

#include <string>

#include "Constants.h"

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

#define SPRITE_H
#endif
