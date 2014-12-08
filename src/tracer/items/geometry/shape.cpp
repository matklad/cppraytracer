#include <utils/option.h>
#include <tracer/items/geometry/shape.h>

namespace tracer {

utils::option<point_on_ray> shape::intersect(ray const& r) const {
    if ( auto const& i = intersect_impl(r)) {
        return utils::some(r.point_along(i.value()));
    }
    return utils::none;
}

linear::direction3d shape::normal_at(linear::point3d const& point) const
{ return normal_at_impl(point); }

shape::~shape() {}

} // namespace tracer
