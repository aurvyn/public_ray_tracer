#include <iostream>

#include "tracer/Scene.hpp"

int main(int argc, char const **argv) {
    Resolution res = {0, 0};
    std::cout << "Please enter the desired camera resolution (width height): ";
    std::cin >> res.width >> res.height;
    if (!std::cin || res.width <= 0 || res.height <= 0) {
        std::cerr << "Invalid resolution entered. Using default values.\n";
        res = {100, 100};
    }
    std::cout << "Resolution set to " << res.width << "x" << res.height << std::endl;
    Scene scene = {res};
    scene.render();
    return 0;
}
