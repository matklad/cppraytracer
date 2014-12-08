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
    double const k = dot_product(light_direction, -normal);
    return color_ * diffuse_light * k;
}

} // namespace tracer
