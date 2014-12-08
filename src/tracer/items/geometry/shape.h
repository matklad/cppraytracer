#pragma once

#include <vector>
#include <memory>

#include <utils/option.h>
#include <utils/operators.h>

#include <linear/linear.h>
#include <tracer/light/ray.h>

namespace tracer {

struct shape;

struct shape {
    utils::option<point_on_ray> intersect(ray const& r) const;
    linear::direction3d normal_at(linear::point3d const& point) const;

    virtual ~shape();

private:
    virtual utils::option<point_on_ray> intersect_impl(ray const& r) const = 0;
    virtual linear::direction3d normal_at_impl(
        linear::point3d const& point) const = 0;
};

} // namespace tracer
