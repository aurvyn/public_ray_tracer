#include "Shape.hpp"
#include "AABB.hpp"
#include "Ray.hpp"

using std::min, std::max;

void Sphere::expand(AABB &bounds) const {
    for (unsigned short i = 0; i < 3; ++i) {
        bounds.bb_min[i] = min(bounds.bb_min[i], position[i] - radius);
        bounds.bb_max[i] = max(bounds.bb_max[i], position[i] + radius);
    }
}

void Triangle::expand(AABB &bounds) const {
    for (unsigned short i = 0; i < 3; ++i) {
        bounds.bb_min[i] = min({bounds.bb_min[i], a[i], b[i], c[i]});
        bounds.bb_max[i] = max({bounds.bb_max[i], a[i], b[i], c[i]});
    }
}

std::optional<HitData> Sphere::hit_by(const Ray &ray, float reach) const {
    Vector3 sphereToRay = ray.origin - position;
    float b = ray.direction.dot(sphereToRay);
    float discriminant = b*b - (sphereToRay.dot(sphereToRay) - radius*radius);
    if (discriminant < 0) {
        return std::nullopt;
    }
    float distance = -b - sqrt(discriminant);
    if (distance > reach) {
        return std::nullopt;
    }
    Vector3 hit_point = ray.origin + distance*ray.direction;
    Vector3 normal = (hit_point - position).normalize();
    if (distance >= 0) {
        return HitData{this, hit_point, normal, distance};
    }
    return std::nullopt;
}

std::optional<HitData> Triangle::hit_by(const Ray &ray, float reach) const {
    Vector3
        edge0 = b - a,
        edge1 = c - b,
        edge2 = a - c,
        normal = (edge0).cross(edge1).normalize();
    float distance = (a-ray.origin).dot(normal) / ray.direction.dot(normal);
    if (distance < 0 || distance > reach) {
        return std::nullopt;
    }
    Vector3 hit_point = ray.origin + distance*ray.direction;
    if (edge0.cross(hit_point - a).dot(normal) > 0
        && edge1.cross(hit_point - b).dot(normal) > 0
        && edge2.cross(hit_point - c).dot(normal) > 0) {
        return HitData{this, hit_point, normal, distance};
    }
    return std::nullopt;
}
