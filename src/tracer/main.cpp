#include <iostream>
#include <fstream>
#include <vector>
#include <fstream>
#include <ctime>

#include <linear/point3d.h>
#include <tracer/scene/scene.h>
#include <tracer/scene/scene_builder.h>
#include <tracer/images/ppm.h>
#include <tracer/images/terminal.h>
#include <tracer/light/light_source.h>
#include <tracer/parsers/obj_parser.h>

int main() {
    using namespace tracer;

    std::ifstream ifs("utah.obj");
    auto const triangles = parse_obj(ifs);

    unsigned const upsampling = 1;
    scene_builder builder;

    builder
        .up_direction({0, 0, -1})
        .camera_position({0, 40, 90})
        .focal_distance(80)
        .screen_size({{40.0, 30.0}})
        .resolution({{640u * upsampling, 480u * upsampling}})
        .add_light({white, {80, 80, 50}})
        .background_color(blue * .2)
        .ambient_light(white * .3);

    for (auto const& t: triangles) {
        builder.add_item(item::make_triangle(material(red), t));
    }

    scene const scene = std::move(builder).build();

    std::time_t start, finish;
    std::time(&start);
    auto const im = upsample(scene.render(), upsampling);
    write_ppm(std::cout, im);
    std::time(&finish);

    std::cerr << "time: " << std::difftime(finish, start) << std::endl;
}
