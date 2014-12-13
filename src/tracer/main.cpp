#include <iostream>
#include <vector>
#include <fstream>

#include <linear/point3d.h>
#include <tracer/scene/camera.h>
#include <tracer/scene/scene.h>
#include <tracer/images/ppm.h>

using namespace tracer;

std::vector<item> make_items() {
    std::vector<item> result;
    material blue{{0, 0, 1}};
    material red{{1, 0, 0}};

    result.push_back(item::make_sphere(red,  {0, -8, 0}, 10));
    result.push_back(item::make_sphere(blue, {0,  8, 0}, 10));
    return result;
};

camera make_camera() {
    camera_parameters params;
    params.position = {-20, 0, 0};
    params.look_at = {0, 0, 0};
    params.up_direction = {0, 0, 1};
    params.focal_distance = 10;
    params.screen = {{{32, 24}}, {{640u, 480u}}};
    return camera{params};
}

int main() {
    scene scene{make_camera(), make_items()};
    image im = scene.render();
    write_ppm(std::cout, im);
}
