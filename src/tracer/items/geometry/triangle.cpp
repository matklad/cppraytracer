#include <array>

#include <tracer/items/geometry/triangle.h>
#include <utils/option.h>
#include <linear/linear.h>
#include <linear/utils.h>

namespace tracer {

namespace  {

linear::vector3d ort_in_plain(linear::vector3d const& a,
                              linear::vector3d const& b)
{ return b - projection(a, b); }

} // namespace

triangle::triangle(array3<linear::point3d> const& points,
                   array3<linear::direction3d> const& normals)
    : a_(points[0])
    , ab_(points[1] - points[0])
    , ac_(points[2] - points[0])
    , normals_(normals)
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

linear::direction3d triangle::normal_at_impl(linear::point3d const& p) const
{
    // a + x*ab + y*ac = p
    auto const v = p - a_;
    auto const abn = ort_in_plain(ab_, ac_);
    auto const acn = ort_in_plain(ac_, ab_);
    auto const x = dot_product(v, acn) / dot_product(ab_, acn);
    auto const y = dot_product(v, abn) / dot_product(ac_, abn);
    auto const z = 1 - (x + y);
    (void)z;
    return linear::direction3d{
        normals_[1] * x + normals_[2] * y + normals_[0] * z
        // cross_product(ab_, ac_)
    };
}

} // namespace tracer
