#include <iostream>

#include "tracer/AABB.hpp"
#include "tracer/BVH.hpp"
#include "tracer/Camera.hpp"
#include "tracer/Common.h"
#include "tracer/Light.hpp"
#include "tracer/Material.hpp"
#include "tracer/Ray.hpp"
#include "tracer/Scene.hpp"
#include "tracer/Shape.hpp"

int main(int argc, char const **argv) {
    Resolution res = {0, 0};
    std::cout << "Enter the relative obj file path: ";
    std::string obj_path;
    std::cin >> obj_path;
    std::cout << "Please enter the desired camera resolution (width height): ";
    std::cin >> res.width >> res.height;
    if (res.width <= 0 || res.height <= 0) {
        std::cerr << "Invalid resolution entered. Using default values.\n";
        res = {100, 100};
    }
    std::cout << "Resolution set to " << res.width << "x" << res.height << std::endl;
    Scene scene = Scene(res, obj_path.c_str());
    scene.render();
    return 0;
}
