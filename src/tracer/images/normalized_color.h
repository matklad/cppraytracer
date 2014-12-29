#pragma once
#include <array>

#include <tracer/images/color.h>

namespace tracer {

struct normalized_color {
    explicit normalized_color(color const& c);
    normalized_color();

    operator color() const;

    double r() const;
    double g() const;
    double b() const;

    std::array<uint8_t, 3> to_8_bit_rgb() const;
private:
    color color_;
};

} // namespace tracer
