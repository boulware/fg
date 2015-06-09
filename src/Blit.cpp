#include "Blit.h"

#include <algorithm>

namespace Blit
{
    void AlignSprite(sf::Sprite& Sprite, alignment HAlign, alignment VAlign)
    {
        sf::FloatRect BB = Sprite.getGlobalBounds();

        sf::Vector2f V;
        
        if((int)BB.width%2 == 0) V.x = BB.width / 2;
        else V.x = (BB.width / 2) - 1;

        if((int)BB.height%2 == 0) V.y = (BB.height / 2) - 10;
        else V.y = (BB.height / 2) - 1;
        
        V.x *= (int8)HAlign;
        V.y *= (int8)VAlign;

        if(HAlign == alignment::Right) V.x += 1;
        if(VAlign == alignment::Right) V.y += 1;
                 
        Sprite.setOrigin(V);
    }
    
    void
    BlitBitmap(sf::Image SrcImage,
               int16 SrcX, int16 SrcY,
               int16 DestX, int16 DestY,
               uint16 Width, uint16 Height,
               bool32 Transparency)               
    {
        // If part of the bitmap to be drawn is outside the destination bitmap, these will optimize
        // the call to a BlitBitmap that only blits the part that's inside the destination bitmap.
        if(DestX < 0)
        {
            SrcX = min(Width, -DestX);
            Width = max(Width + DestX, 0);
            DestX = 0;
        }
        if(DestY < 0)
        {
            SrcY = min(Height, -DestY);
            Height = max(Height + DestY, 0);
            DestY = 0;
        }
        if(DestX + Width > Global::Window.getSize().x)
        {
            Width = max(Global::Window.getSize().x - DestX, 0);
        }
        if(DestY + Height > Global::Window.getSize().y)
        {
            Height = max(Global::Window.getSize().y - DestY, 0);
        }


        sf::Texture Texture;
        Texture.loadFromImage(SrcImage);

        sf::Sprite Sprite;
        Sprite.setTexture(Texture);
        Sprite.setPosition(DestX, DestY);
        
        Global::Window.draw(Sprite);
    }
}
