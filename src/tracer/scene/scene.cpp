#include <memory>
#include <vector>

#include <linear/direction3d.h>
#include <tracer/scene/scene.h>
#include <tracer/items/item.h>
#include <tracer/images/image.h>
#include <tracer/images/color.h>
#include <tracer/images/normalized_color.h>


namespace tracer {

scene::scene(camera const& camera,
             normalized_color const& ambient_light_,
             std::vector<item> items)
    : camera_{camera}
    , ambient_light_{ambient_light_}
    , items_{std::move(items)}
{}

image scene::render() const {
    image result(camera_.resolution());
    for (unsigned x = 0; x < camera_.resolution()[0]; ++x) {
        for (unsigned y = 0; y < camera_.resolution()[1]; ++y) {
            ray const r = camera_.ray_for_pixel(x, y);
            result(x, y) = normalized_color{trace(r)};
        }
    }
    return result;
}

color scene::trace(ray const& r) const {
    utils::option<intersection_point> intersection = utils::none;
    for (auto const& obj: items_) {
        if (auto const some_i = obj.intersect(r)) {
            intersection_point const i = some_i.value();
            if (!intersection || (intersection && i < intersection.value())) {
                intersection = i;
            }
        }
    }
    color const background_color{0, 0, 0};
    return intersection
        ? calculate_light(intersection.value())
        : background_color;
}

color scene::calculate_light(intersection_point const& p) const {
    color sum_color{0, 0, 0};
    // sum_color += p.get_item().calculate_ambient_color(ambient_light);
    // for (auto const& source: light_sources_) {
    //     linear::direction3d const d = linear::direction3d(p - source.position());
        // sum_color += p.get_item()
        //     .calculate_diffuse_color(source.color(), d, p);
    // }
    sum_color += p.get_item().calculate_ambient_color(ambient_light_);
    color const light{.8, .8, .8};
    linear::point3d position{-20, 10, 10};
    linear::direction3d light_direction = linear::direction_from_to(position, p);
    sum_color += p.get_item().calculate_diffuse_color(
        light, light_direction, p.get_item().normal_at(p));
    return sum_color;
}

}
