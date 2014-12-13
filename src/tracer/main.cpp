#include <iostream>
#include <vector>
#include <fstream>

#include <linear/point3d.h>
#include <tracer/scene/scene.h>
#include <tracer/scene/scene_builder.h>
#include <tracer/images/ppm.h>

int main() {
    using namespace tracer;

    material const blue{{0, 0, 1}};
    material const red{{1, 0, 0}};
    unsigned const upsampling = 2;

    scene const scene = scene_builder()
        .center({0, 0, 0})
        .up_direction({0, 0, 1})
        .camera_position({-20, 0, 0})
        .focal_distance(10)
        .screen_size({{32.0, 24.0}})
        .resolution({{640u * upsampling, 480u * upsampling}})
        .add_item(item::make_sphere(red,  {0, -8, 0}, 10))
        .add_item(item::make_sphere(blue, {0,  8, 0}, 10))
        .build();

    write_ppm(std::cout, upsample(scene.render(), upsampling));
}
