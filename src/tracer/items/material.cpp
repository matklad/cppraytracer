#include <algorithm>

#include <linear/direction3d.h>
#include <tracer/images/color.h>
#include <tracer/items/material.h>

namespace tracer {

material::material(color const& c): color_(c) {}

color material::calculate_ambient_color(color const& ambient_light) const
{ return color_ * ambient_light; }

color material::calculate_diffuse_color(
    color const& diffuse_light,
    linear::direction3d const& light_direction,
    linear::direction3d const& normal) const
{
    auto const k = std::max(dot_product(light_direction, -normal), 0.0);
    return color_ * diffuse_light * k;
}

color material::calculate_specular_color(
    color const& speculat_light,
    linear::direction3d const& light_direction,
    linear::direction3d const& normal,
    linear::direction3d const& view_direction) const
{
    auto const n_proj = -projection(normal, light_direction);
    auto const reflected_light = 2 * n_proj + light_direction;
    auto const k = std::max(dot_product(view_direction, -reflected_light), 0.0);
    return speculat_light * k;
}

} // namespace tracer
