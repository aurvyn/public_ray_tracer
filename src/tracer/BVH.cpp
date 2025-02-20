#include "BVH.hpp"
#include "Shape.hpp"

BVH::BVH(std::vector<const Shape*> &objects, unsigned int depth) {
    if (objects.size() == 1) {
        left = nullptr;
        right = nullptr;
        object = objects[0];
        //std::cout << "Leaf: " << object << std::endl;
        return;
    }
    //std::cout << "Branching: " << std::endl;
    for (const Shape *shape : objects) {
        shape->expand(bounds);
    }
    Vector3 size = bounds.bb_max - bounds.bb_min;
    unsigned int axis = size[0] > size[1] ? 0 : 1;
    axis = size[axis] > size[2] ? axis : 2;
    std::vector<const Shape*> left_objects, right_objects;
    for (const Shape *shape : objects) {
        if (shape->position[axis] < bounds.bb_min[axis] + size[axis] / 2) {
            left_objects.push_back(shape);
        } else {
            right_objects.push_back(shape);
        }
    }
    if (left_objects.empty() || right_objects.empty()) {
        std::sort(objects.begin(), objects.end(), [axis](const Shape *a, const Shape *b) {
            return a->position[axis] < b->position[axis];
        });
        auto half = objects.begin() + objects.size() / 2;
        left_objects.assign(objects.begin(), half);
        right_objects.assign(half, objects.end());
    }
    //std::cout << std::string(depth, ' ') << " Left - ";
    left = new BVH(left_objects, depth + 1);
    //std::cout << std::string(depth, ' ') << " Right - ";
    right = new BVH(right_objects, depth + 1);
}
