#if !defined(FRAME_H)

#include "sprite.h"
#include "skeleton.h"

struct frame
{
    sprite Sprite;
    skeleton Skeleton;

    frame(std::string Filename);
    ~frame();
};

frame::frame(std::string Filename)
        :
        Sprite(sprite(Filename, true)),
        Skeleton(skeleton())
{
    
}

frame::~frame()
{
}

#define FRAME_H
#endif
