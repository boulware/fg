#include "skeleton.h"

sprite skeleton::SkeletonCrosshair("SkeletonCrosshair.png", true);

void
skeleton::AttachCollisionBox(collision_box CollisionBox, int16 XPosition, int16 YPosition)
{
    
}

void
skeleton::Blit(bitmap* DestBitmap, int16 XOrigin, int16 YOrigin)
{
    uint8 HitboxTransparency = 70;

    SkeletonCrosshair.Blit(DestBitmap,
                           XOrigin, YOrigin,
                           alignment::Center, alignment::Center);
#if 0
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
#endif
}
