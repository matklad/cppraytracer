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

    color calculate_specular_color(
        color const& speculat_light,
        linear::direction3d const& light_direction,
        linear::direction3d const& normal,
        linear::direction3d const& view_direction) const;

private:
    color color_;
};

} // namespace tracer
