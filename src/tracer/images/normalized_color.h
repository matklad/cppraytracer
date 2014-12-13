#pragma once

#include "tracer/images/color.h"

namespace tracer {

struct normalized_color {
    explicit normalized_color(color const& c);
    normalized_color();

    operator color() const;

private:
    color color_;
};

} // namespace tracer
