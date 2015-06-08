#include "bitmap.h"

#include "SFML\Graphics.hpp"

#include <string>

bitmap::bitmap(std::string Filename)
        :
        Width(0), Height(0)
{
    const std::string Path = Filename;
    
    sf::Image image;

    if(image.loadFromFile(Path))
    {
        Width = image.getSize().x;
        Height = image.getSize().y;

        Pixels = new uint32[Width * Height];
    
        memcpy((void*)Pixels, (void*)image.getPixelsPtr(), Width * Height * Const::BytesPerPixel);
    }
    else
    {
        Debug::WriteError("Failed to load image [Path=" + Path + "]\n");

        Width = Global::LoadFailBitmap.Width;
        Height = Global::LoadFailBitmap.Height;

        Pixels = new uint32[Width * Height];
        
        memcpy((void*)Pixels, (void*)Global::LoadFailBitmap.Pixels, Global::LoadFailBitmap.GetSizeInBytes());
    }
    
    Info = {};
    
    Info.bmiHeader.biSize = sizeof(Info.bmiHeader);
    Info.bmiHeader.biWidth = Width;
    Info.bmiHeader.biHeight = -Height;
    Info.bmiHeader.biPlanes = 1;
    Info.bmiHeader.biBitCount = 32;
    Info.bmiHeader.biCompression = BI_RGB;    
}

bitmap::bitmap(uint32 Width, uint32 Height) : Width(Width), Height(Height)
{
    Info = {};
    
    Info.bmiHeader.biSize = sizeof(Info.bmiHeader);
    Info.bmiHeader.biWidth = Width;
    Info.bmiHeader.biHeight = -Height;
    Info.bmiHeader.biPlanes = 1;
    Info.bmiHeader.biBitCount = 32;
    Info.bmiHeader.biCompression = BI_RGB;
    
    Pixels = new uint32[Width * Height];
}

bitmap::bitmap(const bitmap& Other)
{
    Width = Other.Width;
    Height = Other.Height;
    Info = Other.Info;

    Pixels = new uint32[Width * Height];
    memcpy((void*)Pixels, (void*)Other.Pixels, Width * Height * Const::BytesPerPixel);
}

void
bitmap::operator=(const bitmap& Other)
{
    Width = Other.Width;
    Height = Other.Height;
    Info = Other.Info;
    Pixels = new uint32[Width * Height];
    memcpy((void*)Pixels, (void*)Other.Pixels, Width * Height * Const::BytesPerPixel);
}

bitmap::~bitmap()
{
    delete[] Pixels;
}

void
bitmap::Clear(rgba_color ClearColor)
{
    for(uint16 Y = 0;
        Y < Height;
        ++Y)
    {
        for(uint16 X = 0;
            X < Width;
            ++X)
        {
            *(Pixels + X + Width * Y) = (ClearColor.Alpha << 24) | (ClearColor.Red << 16) | (ClearColor.Green << 8) | (ClearColor.Blue);
        }
    }
}
