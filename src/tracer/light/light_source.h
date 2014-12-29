#pragma once
#include <linear/linear.h>
#include <tracer/images/color.h>

namespace tracer {

struct light_source {
    light_source(color const& color, linear::point3d const& position);
    color light_color() const;
    linear::point3d position() const;

private:
    color color_;
    linear::point3d position_;
};

} // namespace tracer
