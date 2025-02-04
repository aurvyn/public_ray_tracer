#include "AABB.hpp"
#include "Ray.hpp"

using std::min, std::max;

bool AABB::hit_by(const Ray &ray) const {
    float t[6];
    for (int i = 0; i < 3; ++i) {
        t[i] = (t_min[i] - ray.origin[i]) / ray.direction[i];
        t[i+3] = (t_max[i] - ray.origin[i]) / ray.direction[i];
        if (t[i] > t[i+3]) std::swap(t[i], t[i+3]);
    }
    float entry = max({t[0], t[1], t[2]});
    float exit = min({t[3], t[4], t[5]});
    return exit > 0 && entry < exit;
}
