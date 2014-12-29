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

const normalized_color white({.7, .7, .7});
const normalized_color red({.7, .05, .05});
const normalized_color green({.05, .7, .05});
const normalized_color blue({.05, .05, .7});

} // namespace tracer
