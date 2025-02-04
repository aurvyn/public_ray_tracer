#pragma once

#include "Common.h"
#include "Material.hpp"

class Light {
public:
    Vector3 position;
    Material material;

    virtual ~Light() {}
};

class PointLight : public Light {
public:
    PointLight(Vector3 position = {}, Material material = {}) {
        this->position = position;
        this->material = material;
    }

    virtual ~PointLight() {}
};

class SpotLight : public Light {
public:
    SpotLight(
        Vector3 position = {},
        Material material = {},
        Vector3 direction = {},
        float fall_off = 1
    ) {
        this->position = position;
        this->material = material;
        this->direction = direction;
        this->fall_off = fall_off;
    }
    Vector3 direction;
    float fall_off;

    virtual ~SpotLight() {}
};

class DirectionalLight : public Light {
public:
    DirectionalLight(
        Vector3 position = {},
        Material material = {},
        Vector3 direction = {}
    ) {
        this->position = position;
        this->material = material;
        this->direction = direction;
    }
    Vector3 direction;

    virtual ~DirectionalLight() {}
};
