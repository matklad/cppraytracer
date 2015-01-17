#pragma once
#include <array>

#include <utils/option.h>
#include <linear/linear.h>
#include <tracer/items/geometry/shape.h>

namespace tracer {

struct triangle: shape {
    template<typename T>
    using array3 = std::array<T, 3>;

    triangle(array3<linear::point3d> const& points,
             array3<linear::direction3d> const& normals);

private:
    utils::option<double> intersect_impl(ray const& r) const override;
    linear::direction3d normal_at_impl(linear::point3d const& p) const override;

    linear::point3d a_;
    linear::vector3d ab_;
    linear::vector3d ac_;
    array3<linear::direction3d> normals_;
};

} // namespace tracer
