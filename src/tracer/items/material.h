#pragma once
#include <tracer/images/color.h>

namespace tracer {

struct material {
    material(color const& color);
    color calculate_color() const;

private:
    color color_;
};

} // namespace tracer
