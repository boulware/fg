#if !defined(COLOR_H)

struct rgba_color
{
    uint8 Alpha;    
    uint8 Red;
    uint8 Green;
    uint8 Blue;

    rgba_color() : Red(0), Green(0), Blue(0), Alpha(0) {}
    rgba_color(uint8 Alpha, uint8 Red, uint8 Green, uint8 Blue) : Alpha(Alpha), Red(Red), Green(Green), Blue(Blue) {}
};

rgba_color BlendColors(rgba_color BackgroundColor, rgba_color ForegroundColor);
uint32 BlendColors(uint32 BackgroundColor, uint32 ForegroundColor);

#define COLOR_H
#endif
