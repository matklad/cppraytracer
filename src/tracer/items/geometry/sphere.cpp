#include <tracer/items/geometry/sphere.h>
#include <utils/option.h>
#include <linear/utils.h>

namespace tracer {

sphere::sphere(linear::point3d const& center, double radius)
    : center_(center)
    , radius_(radius)
{}

utils::option<double> sphere::intersect_impl(ray const& r) const {
    linear::vector3d const shift = center_ - r.origin();
    double const a = dot_product(r.direction(), r.direction());
    double const b = 2 * dot_product(r.direction(), shift);
    double const c = dot_product(shift, shift) - radius_ * radius_;
    if (auto const solution = linear::solve_quadratic_equation(a, b, c)) {
        if (solution.biggest_root > 0) {
            double const t = solution.smallest_root > 0
                ? solution.smallest_root
                : solution.biggest_root;
            return utils::some(t);
        }
    };
    return utils::none;
};

linear::direction3d sphere::normal_at_impl(linear::point3d const& p) const {
    return linear::direction_from_to(center_, p);
}

} // namespace tracer
