#include "skeleton.h"

sf::Texture skeleton::SkeletonCrosshairTexture;
sf::Sprite skeleton::SkeletonCrosshairSprite;

skeleton::skeleton()
{
    static bool IsInitialized = false;

    if(!IsInitialized)
    {
        SkeletonCrosshairTexture.loadFromFile(Global::ImagePath + "SkeletonCrosshair.png");
        SkeletonCrosshairSprite.setTexture(SkeletonCrosshairTexture);
        
        Blit::AlignSprite(SkeletonCrosshairSprite, alignment::Center, alignment::Center);
    }
}

void
skeleton::AttachCollisionBox(collision_box CollisionBox, int16 XPosition, int16 YPosition)
{
    
}

void
skeleton::Blit(int16 XOrigin, int16 YOrigin)
{
    uint8 HitboxTransparency = 70;

    SkeletonCrosshairSprite.setPosition(XOrigin, YOrigin);
    Global::Window.draw(SkeletonCrosshairSprite);
    
/*
    for(auto const CollisionBox : CollisionBoxes)
    {
        Blit::BlitRectangleToBitmap(DestBitmap,
                                    XOrigin + std::get<1>(CollisionBox), YOrigin + std::get<2>(CollisionBox),
                                    std::get<0>(CollisionBox).Width, std::get<0>(CollisionBox).Height,
                                    {HitboxTransparency, 100, 100, 255}, true);
        
        Blit::BlitRectangleToBitmap(DestBitmap,
                                    XOrigin + std::get<1>(CollisionBox), YOrigin + std::get<2>(CollisionBox),
                                    std::get<0>(CollisionBox).Width, std::get<0>(CollisionBox).Height,
                                    {HitboxTransparency, 255, 255, 255}, true, true);

    }
*/
}
