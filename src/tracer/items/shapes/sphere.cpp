#include <tracer/items/shapes/sphere.h>
#include <utils/option.h>
#include <linear/utils.h>

namespace tracer {

sphere::sphere(linear::point3d const center, double const radius)
    : center_(center)
    , radius_(radius)
{}

utils::option<point_on_ray> sphere::intersect_impl(ray const r) const {
    linear::vector3d const shift = r.origin() - center_;
    double const a = dot_product(r.direction(), r.direction());
    double const b = 2 * dot_product(r.direction(), shift);
    double const c = dot_product(shift, shift) - radius_ * radius_;
    if (auto const solution = linear::solve_quadratic_equation(a, b, c)) {
        if (solution.biggest_root > 0) {
            double const t = solution.smallest_root > 0
                ? solution.smallest_root
                : solution.biggest_root;
            return utils::some(r.point_along(t));
        }
    };
    return utils::none;
};

} // namespace tracer
