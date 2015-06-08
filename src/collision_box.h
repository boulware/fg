#if !defined(COLLISION_BOX_H)

#include "Constants.h"

enum class collision_box_type : uint8
{
    Hurtbox,
    Hitbox,
};

struct collision_box
{
public:
    collision_box(collision_box_type Type, real32 Width, real32 Height);

    collision_box_type Type;
    real32 Width, Height;
};

#define COLLISION_BOX_H
#endif
