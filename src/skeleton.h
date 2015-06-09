#if !defined(SKELETON_H)

#include <vector>
#include <tuple>

#include "collision_box.h"

class skeleton
{
private:
    std::vector<std::tuple<collision_box, int16, int16>> CollisionBoxes;

    static sf::Texture SkeletonCrosshairTexture;
    static sf::Sprite SkeletonCrosshairSprite;
public:
    skeleton();
    
    void AttachCollisionBox(collision_box CollisionBox, int16 XPosition, int16 YPosition);

    void Blit(int16 XOrigin, int16 YOrigin);
};

#define SKELETON_H
#endif
