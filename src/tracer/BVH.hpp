#pragma once

#include <vector>

#include "AABB.hpp"

class Shape;

typedef struct BVH {
    BVH() : bounds(), object(nullptr), left(nullptr), right(nullptr), depth(0) {}
    AABB bounds;
    const Shape *object;
    BVH *left;
    BVH *right;
    unsigned int depth;

    BVH(std::vector<const Shape*> &objects, unsigned int depth = 0);

    ~BVH() {}

    bool is_leaf() const {
        return left == nullptr && right == nullptr;
    }
} BVH;
