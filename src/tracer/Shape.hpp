#pragma once

#include <optional>

#include "Common.h"
#include "Material.hpp"

class AABB;
class Ray;

class Shape {
public:
    Material material;
    Vector3 position;

    virtual ~Shape() {}

    virtual void expand(AABB &bounds) const = 0;

    virtual std::optional<HitData> hit_by(const Ray &ray, float reach) const = 0;
};

class Sphere : public Shape {
public:
    Sphere(Vector3 position, float radius, Material material = {}) {
        this->material = material;
        this->position = position;
        this->radius = radius;
    }
    float radius;

    virtual ~Sphere() {}

    void expand(AABB &bounds) const override;

    std::optional<HitData> hit_by(const Ray &ray, float reach = INFINITY) const override;
};

class Triangle : public Shape {
public:
    Triangle(Vector3 a, Vector3 b, Vector3 c, Material material = {}) {
        this->material = material;
        this->position = (a + b + c) / 3;
        this->a = a;
        this->b = b;
        this->c = c;
    }
    Vector3 a, b, c;

    virtual ~Triangle() {}

    void expand(AABB &bounds) const override;

    std::optional<HitData> hit_by(const Ray &ray, float reach = INFINITY) const override;
};
