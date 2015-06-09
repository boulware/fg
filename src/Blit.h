#if !defined(BLIT_H)

enum class alignment : int8
{
    Left = 0,
    Center = 1,
    Right = 2,
};

namespace Blit
{
    void AlignSprite(sf::Sprite& Sprite, alignment HAlign, alignment VAlign);
    
    void BlitBitmap(sf::Image SrcImage,
               int16 SrcX, int16 SrcY,
               int16 DestX, int16 DestY,
               uint16 Width, uint16 Height,
               bool32 Transparency);
}

#define BLIT_H
#endif
