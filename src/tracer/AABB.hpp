#pragma once

#include <algorithm>

#include "Common.h"

class Ray;

class AABB {
public:
    AABB() : bb_min(INFINITY, INFINITY, INFINITY), bb_max(-INFINITY, -INFINITY, -INFINITY) {}
    Vector3 bb_min, bb_max;

    bool hit_by(const Ray &ray) const;

    virtual ~AABB() {}
};
