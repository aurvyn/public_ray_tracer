#pragma once

#include "../../include/obj_parser.h"

#include "Common.h"

class Material {
public:
    Material(
        Vector3 ambient = {.2, .2, .2},
        Vector3 diffuse = {.8, .8, .8},
        Vector3 specular = {1, 1, 1},
        float sharpness = 64,
        float reflect = 0
    ) {
        this->ambient = ambient;
        this->diffuse = diffuse;
        this->specular = specular;
        this->sharpness = sharpness;
        this->reflect = reflect;
    }

    Material(obj_material mtl) {
        this->ambient = Vector3(mtl.amb[0], mtl.amb[1], mtl.amb[2]);
        this->diffuse = Vector3(mtl.diff[0], mtl.diff[1], mtl.diff[2]);
        this->specular = Vector3(mtl.spec[0], mtl.spec[1], mtl.spec[2]);
        this->sharpness = mtl.shiny;
        if (this->sharpness == 0) {
            this->sharpness = 98;
        }
        this->reflect = mtl.reflect;
    }
    Vector3 ambient, diffuse, specular;
    float sharpness, reflect;

    virtual ~Material() {}
};
