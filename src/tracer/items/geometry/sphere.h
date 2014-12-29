#pragma once

#include <utils/option.h>
#include <tracer/items/geometry/shape.h>

namespace tracer {

struct sphere: shape {
    sphere(linear::point3d const& center, double radius);

private:
    utils::option<double> intersect_impl(ray const& r) const override;
    linear::direction3d normal_at_impl(linear::point3d const& p) const override;

    linear::point3d center_;
    double radius_;
};

} // namespace tracer
