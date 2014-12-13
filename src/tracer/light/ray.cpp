#include <linear/linear.h>
#include <tracer/light/ray.h>

namespace tracer {

ray ray::from_to(linear::point3d const& from, linear::point3d const& to)
{ return ray(from, linear::direction_from_to(from, to)); }

ray::ray(linear::point3d const& origin, linear::direction3d const& direction3d)
    : origin_{origin}
    , direction_{direction3d}
{}

linear::point3d ray::point_along(double const distance) const
{ return origin_ + distance * direction_; }

linear::point3d ray::origin() const { return origin_; }
linear::direction3d ray::direction() const { return direction_; }

} // namespace tracer
