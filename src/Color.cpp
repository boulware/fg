#include "Color.h"

rgba_color
BlendColors(rgba_color BackgroundColor, rgba_color ForegroundColor)
{
    rgba_color BlendedColor;
    BlendedColor.Alpha = 1 - (1 - ForegroundColor.Alpha) * (1 - BackgroundColor.Alpha);
    if (BlendedColor.Alpha < 1.0e-6) return BlendedColor; // Fully transparent -- R,G,B not important
    BlendedColor.Red = ForegroundColor.Red * ForegroundColor.Alpha / BlendedColor.Alpha + BackgroundColor.Red * BackgroundColor.Alpha * (1 - ForegroundColor.Alpha) / BlendedColor.Alpha;
    BlendedColor.Green = ForegroundColor.Green * ForegroundColor.Alpha / BlendedColor.Alpha + BackgroundColor.Green * BackgroundColor.Alpha * (1 - ForegroundColor.Alpha) / BlendedColor.Alpha;
    BlendedColor.Blue = ForegroundColor.Blue * ForegroundColor.Alpha / BlendedColor.Alpha + BackgroundColor.Blue * BackgroundColor.Alpha * (1 - ForegroundColor.Alpha) / BlendedColor.Alpha;

    return BlendedColor;
}

float GetNormAlpha(uint32 Color)
{
    uint8 Value = (uint8)(Color >> 24);

    return (float)Value / (float)0xFF;
}
float GetNormBlue(uint32 Color)
{
    uint8 Value = (uint8)(Color >> 16);

    return (float)Value / (float)0xFF;
}
float GetNormGreen(uint32 Color)
{
    uint8 Value = (uint8)(Color >> 8);

    return (float)Value / (float)0xFF;
}
float GetNormRed(uint32 Color)
{
    uint8 Value = (uint8)(Color >> 0);

    return (float)Value / (float)0xFF;
}


// Pixel format: 0xAABBGGRR
uint32
BlendColors(uint32 bg, uint32 fg)
{
    uint32 BlendedColor;
    
    float Alpha = GetNormAlpha(fg);

    if(Alpha < 1.0e-6)
    {
        BlendedColor = bg;

        return BlendedColor;
    }
    
    float Red = Alpha * GetNormRed(fg) + (1 - Alpha) * GetNormRed(bg);
    float Green = Alpha * GetNormGreen(fg) + (1 - Alpha) * GetNormGreen(bg);
    float Blue = Alpha * GetNormBlue(fg) + (1 - Alpha) * GetNormBlue(bg);

    uint8 RedHex = (uint8)(Red * (float)0xFF);
    uint8 GreenHex = (uint8)(Green * (float)0xFF);
    uint8 BlueHex = (uint8)(Blue * (float)0xFF);
    uint8 AlphaHex = (uint8)(Alpha * (float)0xFF);

    BlendedColor = (AlphaHex << 24) | (BlueHex << 16) | (GreenHex << 8) | (RedHex << 0);
    
    return BlendedColor;
}
