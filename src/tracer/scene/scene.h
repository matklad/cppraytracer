#pragma once

#include <vector>
#include <memory>
#include <tracer/items/item.h>
#include <tracer/images/image.h>
#include <tracer/images/normalized_color.h>
#include <tracer/scene/camera.h>
#include <tracer/light/light_source.h>

namespace tracer {

struct scene_builder;

struct scene {
    image render() const;

private:
    friend struct scene_builder;

    scene(camera const& camera,
          color const& ambient_light,
          color const& background_color,
          std::vector<light_source> lights,
          std::vector<item> items);

    color color_at_pixel(unsigned x, unsigned y) const;
    utils::option<intersection_point> first_hit(ray const& r) const;
    color trace(ray const&r) const;
    color calculate_light(intersection_point const& intersection) const;

    camera camera_;
    color ambient_light_;
    color background_color_;
    std::vector<light_source> lights_;
    std::vector<item> items_;
};

} // namespace tracer
