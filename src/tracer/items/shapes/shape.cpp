#include <utils/option.h>
#include <tracer/items/shapes/shape.h>

namespace tracer {

utils::option<point_on_ray> shape::intersect(ray const r) const
{ return intersect_impl(r); }

shape::~shape() {}

} // namespace tracer
