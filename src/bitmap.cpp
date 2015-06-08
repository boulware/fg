#include "bitmap.h"

//#include "SFML\Graphics.hpp"

bitmap::bitmap(std::string Filename)
{
    std::vector<uint8> image;
    std::vector<uint8> png;
    uint32 Width, Height;
//    uint32 Width = 0;
//    uint32 Height = 0;
    
    lodepng::load_file(png, Filename);

    lodepng_inspect(&Width, &Height, &lodepng::State(), &png[0], png.size());

    Pixels = new uint32[Width * Height];
    
    lodepng::decode(image, Width, Height, png);
    
    memcpy((void*)Pixels, (void*)&image[0], Width * Height * BytesPerPixel);

    Pitch = BytesPerPixel * Width;

    Info = {};
    
    Info.bmiHeader.biSize = sizeof(Info.bmiHeader);
    Info.bmiHeader.biWidth = Width;
    Info.bmiHeader.biHeight = -Height;
    Info.bmiHeader.biPlanes = 1;
    Info.bmiHeader.biBitCount = 32;
    Info.bmiHeader.biCompression = BI_RGB;

    this->Width = Width;
    this->Height = Height;
}

bitmap::bitmap(uint32 Width, uint32 Height) : Width(Width), Height(Height)
{
    Pitch = BytesPerPixel * Width;

    Info = {};
    
    Info.bmiHeader.biSize = sizeof(Info.bmiHeader);
    Info.bmiHeader.biWidth = Width;
    Info.bmiHeader.biHeight = -Height;
    Info.bmiHeader.biPlanes = 1;
    Info.bmiHeader.biBitCount = 32;
    Info.bmiHeader.biCompression = BI_RGB;

//    Pixels.resize(Width * Height);
    
    Pixels = new uint32[Width * Height];
    
//    Pixels = VirtualAlloc(0, BytesPerPixel * Width * Height, MEM_RESERVE|MEM_COMMIT, PAGE_READWRITE);
}

bitmap::bitmap(const bitmap& Other)
{
    Width = Other.Width;
    Height = Other.Height;
    Info = Other.Info;
    Pitch = Other.Pitch;

    Pixels = new uint32[Width * Height];
    memcpy((void*)Pixels, (void*)Other.Pixels, Width * Height * BytesPerPixel);
}

void
bitmap::operator=(const bitmap& Other)
{
    Width = Other.Width;
    Height = Other.Height;
    Info = Other.Info;
    Pitch = Other.Pitch;
    Pixels = new uint32[Width * Height];
    memcpy((void*)Pixels, (void*)Other.Pixels, Width * Height * BytesPerPixel);
    //   Pixels = Other.Pixels;
}

bitmap::~bitmap()
{
//    VirtualFree(Pixels, 0, MEM_RELEASE);
    delete[] Pixels;
}

void
bitmap::Clear(rgba_color ClearColor)
{
//    std::vector<uint32>::iterator Origin = Pixels.begin();
    uint32* Origin = Pixels;
    for(uint16 Y = 0;
        Y < Height;
        ++Y)
    {
        for(uint16 X = 0;
            X < Width;
            ++X)
        {
            *(Origin + X + Width * Y) = (ClearColor.Alpha << 24) | (ClearColor.Red << 16) | (ClearColor.Green << 8) | (ClearColor.Blue);
        }
    }
}
