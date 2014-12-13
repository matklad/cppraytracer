#include <memory>
#include <vector>

#include <linear/direction3d.h>
#include <tracer/scene/scene.h>
#include <tracer/items/item.h>
#include <tracer/images/image.h>
#include <tracer/images/color.h>
#include <tracer/images/normalized_color.h>


namespace tracer {

using namespace linear;

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
            result(x, y) = color_at_pixel(x, y);
        }
    }
    return result;
}

normalized_color scene::color_at_pixel(unsigned const x, unsigned const y) const {
    normalized_color const background_color{{0.03, 0.03, 0.03}};
    ray const r = camera_.ray_for_pixel(x, y);
    if (auto const hit = first_hit(r)) {
        return normalized_color{calculate_light(hit.value())};
    } else {
        return background_color;
    }
    return normalized_color{trace(r)};
}

utils::option<intersection_point> scene::first_hit(ray const& r) const {
    utils::option<intersection_point> hit = utils::none;
    for (auto const& obj: items_) {
        if (auto const some_i = obj.intersect(r)) {
            intersection_point const i = some_i.value();
            if (!hit || (hit && i < hit.value())) {
                hit = i;
            }
        }
    }
    return hit;
}

color scene::calculate_light(intersection_point const& p) const {
    color sum_color{0, 0, 0};
    sum_color += p.calculate_ambient_color(ambient_light_);

    struct light_source {
        color color;
        point3d position;
    };

    light_source const l{{.8, .8, .8}, {-100, 100, -40}};
    auto light_sources = {l};

    for (auto const& l: light_sources) {
        direction3d light_direction = direction_from_to(l.position, p);
        ray const pre_out_ray = ray::from_to(p, l.position);
        ray const out_ray = ray::from_to(pre_out_ray.point_along(.001), l.position);
        if (!first_hit(out_ray)) {
            sum_color += p.calculate_diffuse_color(l.color, light_direction);
        }

    }
    return sum_color;
}

}
