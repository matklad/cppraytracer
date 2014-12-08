#include <iostream>
#include <vector>
#include <memory>
#include <fstream>

#include <linear/point3d.h>
#include <tracer/scene/camera.h>
#include <tracer/scene/scene.h>
#include <tracer/items/geometry/shape.h>
#include <tracer/items/geometry/sphere.h>
#include <tracer/images/ppm.h>

using namespace tracer;

shapes make_shapes() {
    shapes result;
    result.push_back(std::make_unique<sphere>(linear::point3d{0, -8, 0}, 10));
    result.push_back(std::make_unique<sphere>(linear::point3d{0,  8, 0}, 10));

    return result;

};

camera make_camera() {
    linear::point3d position{-100, 0, 0};
    linear::point3d look_at{0, 0, 0};
    linear::direction3d up{0, 0, 1};
    double focus = 60;
    screen s{{{64, 48}}, {{640u, 480u}}};
    camera_parameters params{position, look_at, up, focus, s};
    return camera{params};
}

int main() {
    scene scene{make_camera(), make_shapes()};
    image im = scene.render();
    write_ppm(std::cout, im);
}
