#include "tracer/images/normalized_color.h"

namespace tracer {

namespace {

double normalize(double const c) { return std::max(0.0, std::min(1.0, c)); }

} // namespace

normalized_color::normalized_color(color const& c)
    : color_(normalize(c.r()), normalize(c.g()), normalize(c.b()))
{}

normalized_color::normalized_color()
    : color_(0.0, 0.0, 0.0)
{}

normalized_color::operator color() const { return color_; }

double normalized_color::r() const { return color_.r(); };
double normalized_color::g() const { return color_.g(); };
double normalized_color::b() const { return color_.b(); };

std::array<uint8_t, 3> normalized_color::to_8_bit_rgb() const {
    uint8_t const max_val = 255u;
    uint8_t const ur = r() * max_val;
    uint8_t const ug = g() * max_val;
    uint8_t const ub = b() * max_val;
    return {{ur, ug, ub}};
}


} // namespace tracer
