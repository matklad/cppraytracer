#pragma once
#include <array>

#include <utils/option.h>
#include <linear/linear.h>
#include <tracer/items/geometry/shape.h>

namespace tracer {

struct triangle: shape {
    triangle(std::array<linear::point3d, 3> const& points);

private:
    utils::option<double> intersect_impl(ray const& r) const override;
    linear::direction3d normal_at_impl(linear::point3d const& p) const override;

    linear::vector3d ab() const;
    linear::vector3d ac() const;

    std::array<linear::point3d, 3> points_;
};

} // namespace tracer
