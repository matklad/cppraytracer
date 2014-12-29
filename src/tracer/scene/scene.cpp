#include <memory>
#include <vector>

#include <linear/direction3d.h>
#include <tracer/scene/scene.h>
#include <tracer/items/item.h>
#include <tracer/light/light_source.h>
#include <tracer/images/image.h>
#include <tracer/images/color.h>
#include <tracer/images/normalized_color.h>

namespace tracer {

scene::scene(camera const& camera,
             normalized_color const& ambient_light_,
             std::vector<light_source> lights,
             std::vector<item> items)
    : camera_{camera}
    , ambient_light_{ambient_light_}
    , lights_{lights}
    , items_{std::move(items)}
{}

image scene::render() const {
    image result(camera_.resolution());
    for (auto x = 0u; x < camera_.resolution()[0]; ++x) {
        for (auto y = 0u; y < camera_.resolution()[1]; ++y) {
            result(x, y) = color_at_pixel(x, y);
        }
    }
    return result;
}

normalized_color scene::color_at_pixel(unsigned const x, unsigned const y) const {
    normalized_color const background_color = blue;
    auto const r = camera_.ray_for_pixel(x, y);
    auto const hit = first_hit(r);
    return hit
        ? normalized_color{calculate_light(*hit)}
        : background_color;
}

utils::option<intersection_point> scene::first_hit(ray const& r) const {
    utils::option<intersection_point> hit = utils::none;
    for (auto const& obj: items_) {
        if (auto const i = obj.intersect(r)) {
            if (!hit || (hit && *i < *hit)) {
                hit = *i;
            }
        }
    }
    return hit;
}

color scene::calculate_light(intersection_point const& p) const {
    color sum_color{0, 0, 0};
    sum_color += p.calculate_ambient_color(ambient_light_);

    for (auto const& l: lights_) {
        auto const light_direction = direction_from_to(l.position(), p);
        auto const pre_out_ray = ray::from_to(p, l.position());
        auto const out_ray = ray::from_to(pre_out_ray.point_along(.001), l.position());
        if (!first_hit(out_ray)) {
            sum_color += p.calculate_diffuse_color(l.color(), light_direction);
        }
    }
    return sum_color;
}

}
