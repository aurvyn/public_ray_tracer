#pragma once

#include <optional>
#include <vector>

#include "Common.h"

class BVH;
class Shape;
class Light;

class Ray {
public:
    Ray(Vector3 origin, Vector3 direction) {
        this->origin = origin;
        this->direction = direction.normalize();
    }
    Vector3 origin;
    Vector3 direction;

    virtual ~Ray() {}

    Vector3 trace(
        BVH &obj_tree,
        const std::vector<const Light*> &lights,
        float reach = INFINITY,
        const Shape* ignored_object = nullptr
    ) const;

    std::optional<HitData> cast(
        BVH &obj_tree,
        float reach = INFINITY,
        const Shape* ignored_object = nullptr,
        bool once = true
    ) const;
};
