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

    bool32 Loops;
    bool32 AnimationEnded;
    
    uint16 CurrentFrame;
public:
    sprite(std::string SpriteFilepath, bool32 Loops = true);
    sprite(const sprite& Other);

    void Reset() { CurrentFrame = 0; AnimationEnded = false; }
    void UpdateTexture();
    void AdvanceFrame();
    void Draw(int16, int16);

    bool32 GetAnimationEnded() { return AnimationEnded; }
};

#define SPRITE_H
#endif
