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

} // namespace tracer
