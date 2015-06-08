#if !defined(SPRITE_H)

#include "Constants.h"
#include "bitmap.h"
#include "extern/lodepng.h"

enum alignment : int8
{
    Left = 1,
    Center = 2,
//    Right = 3
};

struct sprite
{
private:
    uint16 Width;
    uint16 Height;
    bool32 Transparency;
public:
    // TODO(tyler): This should probably eventually be private once I'm loading sprites from files.
    bitmap Bitmap;

    sprite(std::string Filename, bool32 Transparency = false);
    sprite(uint16, uint16, bool32);
    ~sprite();
    
    void Blit(bitmap*, int16, int16, alignment, alignment);
};

#define SPRITE_H
#endif
