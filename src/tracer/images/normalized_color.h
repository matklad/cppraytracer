#pragma once

#include "tracer/images/color.h"

namespace tracer {

struct normalized_color {
    explicit normalized_color(color const& c);
    normalized_color();

    operator color() const;

    double r() const;
    double g() const;
    double b() const;
private:
    color color_;
};

} // namespace tracer
