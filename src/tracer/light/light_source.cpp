#include "tracer/light/light_source.h"

namespace tracer {

light_source::light_source(normalized_color const& color,
                           linear::point3d const& position)
    : color_(color)
    , position_(position)
{}

normalized_color light_source::color() const { return color_; }
linear::point3d  light_source::position() const { return position_; }

} // namespace tracer
