#if !defined(BITMAP_H)

#include "Color.h"

struct bitmap
{
public:
    bitmap(uint32, uint32);
    bitmap(std::string Filename);
    bitmap(const bitmap& Other);
    void operator=(const bitmap& Other);
    ~bitmap();

    BITMAPINFO Info;
    uint16 Pitch;
//    uint32 *Pixels;
//    std::vector<uint32> Pixels;
    uint32* Pixels;
    uint32 Width;
    uint32 Height;

    void Clear(rgba_color ClearColor = {255, 0, 0, 0});
};

#define BITMAP_H
#endif
