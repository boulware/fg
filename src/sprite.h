#if !defined(SPRITE_H)

#include <string>

#include "Constants.h"
#include "win32_debug.h"

class sprite
{
private:
    struct texture
    {
        sf::Texture SFMLTexture;
        sf::Vector2f DrawOrigin;

        texture(std::string TextureFilepath, sf::Vector2f DrawOrigin = {0, 0})
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

    static const std::string ImagePath;
public:
    
    sprite(std::string SpriteFilepath, bool32 Loops = true);
    sprite(const sprite& Other);

    void Reset() { CurrentFrame = 0; AnimationEnded = false; }
    void UpdateTexture();
    void AdvanceFrame();
    void Draw(int16, int16);

    bool32 GetAnimationEnded() { return AnimationEnded; }

    static sprite LoadFailSprite;
};

#define SPRITE_H
#endif
