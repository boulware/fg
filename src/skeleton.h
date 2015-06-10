#if !defined(SKELETON_H)

#include <vector>
#include <tuple>

#include "collision_box.h"

class skeleton
{
private:
    std::vector<std::tuple<collision_box, int16, int16>> CollisionBoxes;
public:
    void AttachCollisionBox(collision_box CollisionBox, int16 XPosition, int16 YPosition);
};

#define SKELETON_H
#endif
