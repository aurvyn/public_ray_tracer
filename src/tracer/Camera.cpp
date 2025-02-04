#include <iostream>

#include "Camera.hpp"
#include "Ray.hpp"

Buffer<Color> Camera::capture(
    BVH &obj_tree,
    const std::vector<const Light*> &lights,
    float FOV
) const {
    Buffer<Color> frame_buffer(res.width, res.height);
    for (unsigned short x = 0; x < res.width; ++x) {
        for (unsigned short y = 0; y < res.height; ++y) {
            //std::cout << "Rendering pixel " << x << ", " << y << std::endl;
            float u = (2.0f * x / (float)res.width - 1.0f) * res.width / (float)res.height;
            float v = 1.0f - 2.0f * y / (float)res.height;
            float d = 1.0f / tan(FOV / 2.0f);
            Vector3 dir = u*basis[0] + v*basis[1] + d*basis[2];
            Vector3 color = Ray(position, dir).trace(obj_tree, lights) * 255;
            frame_buffer.at(x, y) = Color(
                std::min((int) color[0], 255),
                std::min((int) color[1], 255),
                std::min((int) color[2], 255)
            );
        }
    }
    return frame_buffer;
}
