#include "AABB.hpp"
#include "Ray.hpp"

using std::min, std::max;

bool AABB::hit_by(const Ray &ray) const {
    //we want to find the farthest entrace and closest exit to the box
    //if the exit is closer than the entrance, there is no hit
    float entry = 0.0f;
    float exit = INFINITY;
    for (int i = 0; i < 3; ++i) {
        float near = (bb_min[i] - ray.origin[i]) / ray.direction[i];
        float far = (bb_max[i] - ray.origin[i]) / ray.direction[i];
        if (far < near) std::swap(near, far);
        entry = max(entry, near);
        exit = min(exit, far);
    }
    return entry < exit;
}
