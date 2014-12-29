#include <array>

#include <tracer/items/geometry/triangle.h>
#include <utils/option.h>
#include <linear/linear.h>
#include <linear/utils.h>

namespace tracer {

triangle::triangle(std::array<linear::point3d, 3> const& points)
    : a_(points[0])
    , ab_(points[1] - points[0])
    , ac_(points[2] - points[0])
{}

/* Intersection picture

   A ------> B
   \       /
    \     /
     \   /
      v /
       C

   A + alpha*AB + beta*AC = O + t*D
*/

utils::option<double> triangle::intersect_impl(ray const& r) const {
    auto const normal = cross_product(ab_, ac_);
    auto const a = dot_product(r.direction(), normal);
    auto const b = dot_product(r.origin() - a_, normal);
    auto const t = linear::solve_linear_equation(a, b);

    auto const intersection = r.point_along(t) - a_;

    auto const ac_d = cross_product(ac_, r.direction());
    auto const alpha = dot_product(ac_d, intersection) / dot_product(ac_d, ab_);

    auto const ab_d = cross_product(ab_, r.direction());
    auto const beta = dot_product(ab_d, intersection) / dot_product(ab_d, ac_);

    return t >= 0 && 0 <= alpha && alpha <= 1 && 0 <= beta && beta <= 1 &&
        alpha + beta <= 1 ? utils::some(t) : utils::none;
}

linear::direction3d triangle::normal_at_impl(linear::point3d const&) const
{ return linear::direction3d{cross_product(ab_, ac_)}; }

} // namespace tracer
