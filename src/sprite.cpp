#include "sprite.h"

sprite::sprite(std::string Filename, bool32 Transparency)
        :
        Bitmap(Filename),
        Transparency(Transparency)
{
    Width = Bitmap.Width;
    Height = Bitmap.Height;
}
        
sprite::~sprite()
{
}

void
sprite::Blit(int16 XOffset, int16 YOffset,
             alignment HorizontalAlign = alignment::Left, alignment VerticalAlign = alignment::Left)
{
//    if(Bitmap != nullptr)
    {
        XOffset -= (Bitmap.Width - 1)/HorizontalAlign;
        YOffset -= (Bitmap.Height - 1)/VerticalAlign;

        sf::Image Image;
        Image.create(Bitmap.Width, Bitmap.Height, (uint8*)Bitmap.Pixels);
//        Image.loadFromMemory((void*)Bitmap.Pixels, Bitmap.GetSizeInBytes());
        
        Blit::BlitBitmap(Image,
                         0, 0,
                         XOffset, YOffset,
                         Width, Height,
                         Transparency);
    }
}
