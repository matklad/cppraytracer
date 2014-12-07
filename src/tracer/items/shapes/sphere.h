#pragma once
#include <array>

#include <tracer/lib/option.h>
#include <tracer/items/shapes/shape.h>

namespace tracer {

struct sphere: shape {
    sphere(linear::point3d center, double radius);

private:
    virtual lib::option<point_on_ray> intersect_impl(ray r) const;

    linear::point3d center_;
    double radius_;
};

} // namespace tracer
