#pragma once

#include <vector>

#include "../../include/Buffer.h"

#include "Common.h"

class BVH;
class Light;

class Camera {
public:
    Camera(Vector3 position = {}) {
        this->position = position;
        this->basis[0] = Vector3(1, 0, 0);
        this->basis[1] = Vector3(0, 1, 0);
        this->basis[2] = Vector3(0, 0, 1);
        this->res = {100, 100};
    }

    Camera(Vector3 position, Vector3 look_point, Vector3 up, Resolution res) {
        this->position = position;
        this->basis[2] = (look_point - position).normalize();
        this->basis[0] = basis[2].cross(up).normalize();
        this->basis[1] = basis[0].cross(basis[2]);
        this->res = res;
    }
    Vector3 position;
    Vector3 basis[3]; // u, v, w
    Resolution res;

    virtual ~Camera() {}

    Buffer<Color> capture(
        BVH &objects,
        const std::vector<const Light*> &lights,
        float FOV
    ) const;
};
