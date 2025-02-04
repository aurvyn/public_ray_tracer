#include "Ray.hpp"
#include "BVH.hpp"
#include "Light.hpp"
#include "Shape.hpp"

Vector3 Ray::trace(
    BVH &obj_tree,
    const std::vector<const Light*> &lights,
    float reach,
    const Shape* ignored_object
) const {
    std::optional<HitData> hit = cast(obj_tree, reach, ignored_object, false);
    if (!hit) {
        return {};
    }
    HitData hit_data = hit.value();
    Vector3
        &hit_point = hit_data.hit_point,
        &hit_normal = hit_data.normal,
        diffuse = {},
        specular = {},
        reflect = {};
    const Shape *hit_obj = hit_data.hit_obj;
    const Material obj_mtl = hit_obj->material;
    if (obj_mtl.reflect > 0) {
        Vector3 reflection = 2 * hit_normal.dot(-direction) * hit_normal + direction;
        Ray reflected_ray(hit_point, reflection);
        reflect = reflected_ray.trace(obj_tree, lights, reach, hit_obj);
    }
    for (const Light *light : lights) {
        Vector3 surface_to_light = light->position - hit_point;
        Ray shadow_ray(hit_point, surface_to_light);
        if (shadow_ray.cast(obj_tree, surface_to_light.length(), hit_obj)) {
            continue;
        }
        surface_to_light.normalize();
        Material light_mtl = light->material;
        diffuse += obj_mtl.diffuse
            * light_mtl.diffuse
            * std::max(surface_to_light.dot(hit_normal), 0.0f);
        Vector3 reflection = 2 * hit_normal.dot(surface_to_light) * hit_normal - surface_to_light;
        specular += obj_mtl.specular
            * light_mtl.specular
            * pow(std::max(reflection.dot(-direction), 0.0f), obj_mtl.sharpness);
    }
    return obj_mtl.ambient + (diffuse + specular) * (1 - obj_mtl.reflect) + reflect * obj_mtl.reflect;
}

std::optional<HitData> Ray::cast(
    BVH &obj_tree,
    float reach,
    const Shape* ignored_object,
    bool once
) const {
    if (obj_tree.bounds.hit_by(*this)) {
        std::optional<HitData> hit = std::nullopt;
        if (obj_tree.is_leaf()) {
            if (obj_tree.object != ignored_object
            && (hit = obj_tree.object->hit_by(*this, reach))) {
                return hit;
            }
        } else {
            if (obj_tree.left != nullptr)
            if (hit = cast(*obj_tree.left, reach, ignored_object, once)) {
                if (once) return hit;
                reach = hit->distance;
            }
            if (obj_tree.right != nullptr)
            if (auto result = cast(*obj_tree.right, reach, ignored_object, once)) {
                hit = result;
            }
            return hit;
        }
    }
    return std::nullopt;
}
