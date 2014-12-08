#pragma once
#include <array>

#include <utils/option.h>
#include <tracer/items/geometry/shape.h>

namespace tracer {

struct sphere: shape {
    sphere(linear::point3d center, double radius);

private:
    virtual utils::option<point_on_ray> intersect_impl(ray r) const;

    linear::point3d center_;
    double radius_;
};

} // namespace tracer
