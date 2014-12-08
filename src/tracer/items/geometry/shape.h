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
    utils::option<point_on_ray> intersect(ray r) const;

    virtual ~shape();

private:
    virtual utils::option<point_on_ray> intersect_impl(ray r) const = 0;
};

} // namespace tracer
