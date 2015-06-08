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
sprite::Blit(bitmap* DestBitmap, int16 XOffset, int16 YOffset,
             alignment HorizontalAlign = alignment::Left, alignment VerticalAlign = alignment::Left)
{
//    if(Bitmap != nullptr)
    {
        XOffset -= (Bitmap.Width - 1)/HorizontalAlign;
        YOffset -= (Bitmap.Height - 1)/VerticalAlign;

        Blit::BlitBitmap(&Bitmap, DestBitmap,
                         0, 0,
                         XOffset, YOffset,
                         Width, Height,
                         Transparency);
    }
}
