#pragma once

#include <algorithm>

#include "Common.h"

class Ray;

class AABB {
public:
    AABB() : t_min(INFINITY, INFINITY, INFINITY), t_max(-INFINITY, -INFINITY, -INFINITY) {}
    Vector3 t_min, t_max;

    bool hit_by(const Ray &ray) const;

    virtual ~AABB() {}
};
