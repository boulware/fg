#include "skeleton.h"

void
skeleton::AttachCollisionBox(collision_box CollisionBox, int16 XPosition, int16 YPosition)
{
    CollisionBoxes.push_back(std::tuple<collision_box, int16, int16>(CollisionBox, XPosition, YPosition));
}
