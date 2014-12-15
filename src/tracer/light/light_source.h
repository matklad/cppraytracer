#pragma once
#include <linear/linear.h>
#include <tracer/images/normalized_color.h>

namespace tracer {

struct light_source {
    light_source(normalized_color const& color, linear::point3d const& position);
    normalized_color color() const;
    linear::point3d position() const;

private:
    normalized_color color_;
    linear::point3d position_;
};

} // namespace tracer
