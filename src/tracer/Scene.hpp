#pragma once

#include "../../include/objLoader.hpp"
#include "../../include/simplePNG.h"

#include "Common.h"
#include "BVH.hpp"
#include "Camera.hpp"
#include "Light.hpp"
#include "Shape.hpp"

Vector3 doubleToVec3(double *arr) {
    return Vector3(arr[0], arr[1], arr[2]);
}

class Scene {
public:
    Scene(Resolution res, const char *obj_path = "resources/bunny-scene.obj") : objects(), lights() {
        objLoader loader = {};
        loader.load(obj_path);
        load_camera(loader, res);
        load_spheres(loader);
        load_triangles(loader);
        obj_tree = BVH(objects);
        load_lights(loader);
    }
    Camera camera;
    BVH obj_tree;
    std::vector<const Shape*> objects;
    std::vector<const Light*> lights;

    virtual ~Scene() {
        for (const Shape* obj : objects) {
            delete obj;
        }
    }

    void render(const char *output_path = "traced_image.png") {
        Buffer<Color> frame_buffer = camera.capture(obj_tree, lights, 1.5708);
        simplePNG_write(output_path, camera.res.width, camera.res.height, (unsigned char*) &frame_buffer.at(0, 0));
    }

private:
    void load_camera(objLoader &loader, Resolution res) {
        this->camera = Camera(
            doubleToVec3(loader.vertexList[loader.camera->camera_pos_index]->e),
            doubleToVec3(loader.vertexList[loader.camera->camera_look_point_index]->e),
            doubleToVec3(loader.normalList[loader.camera->camera_up_norm_index]->e),
            res
        );
    }

    void load_spheres(objLoader &loader) {
        for (unsigned int i = 0; i < loader.sphereCount; ++i) {
            obj_sphere *sphereData = loader.sphereList[i];
            this->objects.push_back(new Sphere(
                doubleToVec3(loader.vertexList[sphereData->pos_index]->e),
                doubleToVec3(loader.normalList[sphereData->up_normal_index]->e).length(),
                Material(*loader.materialList[sphereData->material_index])
            ));
        }
    }

    void load_triangles(objLoader &loader) {
        for (unsigned int i = 0; i < loader.faceCount; ++i) {
            obj_face *faceData = loader.faceList[i];
            this->objects.push_back(new Triangle(
                doubleToVec3(loader.vertexList[faceData->vertex_index[0]]->e),
                doubleToVec3(loader.vertexList[faceData->vertex_index[1]]->e),
                doubleToVec3(loader.vertexList[faceData->vertex_index[2]]->e),
                Material(*loader.materialList[faceData->material_index])
            ));
        }
    }

    void load_lights(objLoader &loader) {
        for (unsigned int i = 0; i < loader.lightPointCount; ++i) {
            obj_light_point *lightData = loader.lightPointList[i];
            this->lights.push_back(new PointLight(
                doubleToVec3(loader.vertexList[lightData->pos_index]->e),
                Material(*loader.materialList[lightData->material_index])
            ));
        }
    }
};
