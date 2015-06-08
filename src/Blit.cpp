#include "Blit.h"

#include <algorithm>
#include "Color.h"

uint32
ABGRtoARGB(uint32 Pixel)
{
    uint8 Alpha = (uint8)(Pixel >> 24);
    uint8 Red = (uint8)(Pixel >> 0);
    uint8 Green = (uint8)(Pixel >> 8);
    uint8 Blue = (uint8)(Pixel >> 16);

    return (Alpha << 24) | (Red << 16) | (Green << 8) | (Blue << 0);
}

uint32
ARGBtoABGR(uint32 Pixel)
{
    uint8 Alpha = (uint8)(Pixel >> 24);
    uint8 Blue = (uint8)(Pixel >> 0);
    uint8 Green = (uint8)(Pixel >> 8);
    uint8 Red = (uint8)(Pixel >> 16);

    return (Alpha << 24) | (Blue << 16) | (Green << 8) | (Red << 0);
}

namespace Blit
{
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
        
        //sf::Texture SrcTexture;
        /*bool32 LoadTextureBool = SrcTexture.loadFromMemory((void*)SrcBitmap->Pixels,
                                                           SrcBitmap->GetSizeInBytes()/*,
                                                           {SrcX, SrcY, Width, Height});*/
        
    //        sf::Sprite SrcSprite(SrcTexture);
        


    //        uint32* SrcOrigin = SrcBitmap->Pixels + SrcX + SrcY * SrcBitmap->Width;
//        uint32* DestOrigin = DestBitmap->Pixels + DestX + DestY * DestBitmap->Width;

//                        Global::Window.draw(SrcSprite);
                        /*
        for(uint16 Y = 0;
            Y < Height;
            ++Y)
        {
            for(uint16 X = 0;
                X < Width;
                ++X)
            {
        
//                uint32* SrcPixel = SrcOrigin + X + SrcBitmap->Width * Y;
//                uint32* DestPixel = DestOrigin + X + DestBitmap->Width * Y;

                
                
                if(Transparency)
                {

                    *DestPixel = ABGRtoARGB(BlendColors(ARGBtoABGR(*DestPixel), *SrcPixel));//RGBAtoARGB(BlendColors(*DestPixel, *SrcPixel));
                }
                else
                {
                    *DestPixel = ABGRtoARGB(*SrcPixel);
                }

                    
            }
        }
                        */
    }
    
    void
    BlitRectangleToBitmap(bitmap *DestBitmap,
                          uint16 XOffset, uint16 YOffset,
                          uint16 Width, uint16 Height,
                          rgba_color Color,
                          bool32 Transparency = false,
                          bool32 Outline = false)
    {
        
        if(!Outline)
        {
//            bitmap Rectangle(Width, Height);
//            Rectangle.Clear(Color);
            sf::Image TestImage;
            TestImage.create(Width, Height);
        
            BlitBitmap(TestImage,
                       0, 0,
                       XOffset, YOffset,
                       Width, Height,
                       Transparency);
        }
        else
        {
            BlitRectangleToBitmap(DestBitmap,
                                  XOffset, YOffset,
                                  Width, 1,
                                  Color,
                                  Transparency, false);
            BlitRectangleToBitmap(DestBitmap,
                                  XOffset, YOffset + Height - 1,
                                  Width, 1,
                                  Color,
                                  Transparency, false);
            BlitRectangleToBitmap(DestBitmap,
                                  XOffset, YOffset + 1,
                                  1, Height - 2,
                                  Color,
                                  Transparency, false);
            BlitRectangleToBitmap(DestBitmap,
                                  XOffset + Width - 1, YOffset + 1,
                                  1, Height - 2,
                                  Color,
                                  Transparency, false);
        }
    }
    
// TODO(tyler): Instead of returning a new bitmap in memory, develop a method for pointing to subsets
// of a bitmap and still being able to draw correctly from the memory.
/*
    bitmap*
    GetSubBitmap(bitmap *SrcBitmap,
                 uint16 XOffset, uint16 YOffset,
                 uint16 Width, uint16 Height)
    {
        bitmap *NewBitmap = new bitmap(Width, Height);
    
        BlitBitmap(SrcBitmap, NewBitmap,
                   XOffset, YOffset,
                   0, 0,
                   Width, Height);
    
        return NewBitmap;
    }
*/
    void
    BlitBufferToWindow(bitmap* Buffer, HWND Window)
    {
        HDC DeviceContext = GetDC(Window);
        
        RECT ClientRect;
        GetClientRect(Window, &ClientRect);
        
        StretchDIBits(DeviceContext,
                      0, 0,
                      ClientRect.right - ClientRect.left, ClientRect.bottom - ClientRect.top,
                      0, 0,
                      Buffer->Width, Buffer->Height,
                      (void*)&Buffer->Pixels[0],
                      &Buffer->Info,
                      DIB_RGB_COLORS, SRCCOPY);

        ReleaseDC(Window, DeviceContext);
    }
}
