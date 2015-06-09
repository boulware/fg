#if !defined(FRAME_H)

#include "skeleton.h"
#include "Blit.h"

struct frame
{
    sf::Texture Texture;
    sf::Sprite Sprite;
    skeleton Skeleton;

    frame(std::string Filepath);
    frame(const frame& Other);
    ~frame();
};

frame::frame(std::string Filepath)
{
    Texture.loadFromFile(Filepath);
    Sprite.setTexture(Texture, true);
}

frame::frame(const frame& Other)
        :
        Texture(Other.Texture),
        Skeleton(Other.Skeleton)
{
    Sprite.setTexture(Texture);
    Sprite.setOrigin(Other.Sprite.getOrigin());
}

frame::~frame()
{
}

#define FRAME_H
#endif
