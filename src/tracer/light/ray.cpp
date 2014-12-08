#include <linear/linear.h>
#include <tracer/light/ray.h>

namespace tracer {

ray ray::from_to(linear::point3d const& from, linear::point3d const& to)
{ return ray(from, linear::direction_from_to(from, to)); }

ray::ray(linear::point3d const& origin, linear::direction3d const& direction3d)
    : origin_{origin}
    , direction_{direction3d}
{}

point_on_ray ray::point_along(double const distance) const
{ return point_on_ray{distance, origin_ + distance * direction_}; }

linear::point3d ray::origin() const { return origin_; }
linear::direction3d ray::direction() const { return direction_; }

point_on_ray::point_on_ray(double const distance, linear::point3d const& point)
    : distance_(distance)
    , point_(point)
{}

bool point_on_ray::operator==(point_on_ray const& rhs) const
{ return distance_ == rhs.distance_; }

bool point_on_ray::operator<(point_on_ray const& rhs) const
{ return distance_ < rhs.distance_; }

point_on_ray::operator linear::point3d() const { return point_; };

} // namespace tracer
