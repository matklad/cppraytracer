#pragma once
#include <linear/direction3d.h>
#include <tracer/images/color.h>

namespace tracer {

struct material {
    material(color const& color);
    color calculate_ambient_color(color const& ambient_light) const;
    color calculate_diffuse_color(
        color const& diffuse_light,
        linear::direction3d const& light_direction,
        linear::direction3d const& normal) const;

private:
    color color_;
};

} // namespace tracer
