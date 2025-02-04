#pragma once

#include "../../include/GenVector.h"

class Shape;

typedef struct HitData {
    const Shape *hit_obj;
    Vector3 hit_point;
    Vector3 normal;
    float distance;
} HitData;

typedef struct Resolution {
    unsigned short width, height;
} Resolution;
