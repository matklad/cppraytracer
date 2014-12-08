#include <tracer/images/color.h>
#include <tracer/items/material.h>

namespace tracer {

material::material(color const& c): color_(c) {}

color material::calculate_color() const { return color_; }

} // namespace tracer
