#pragma once

#include <vector>
#include <memory>

#include <tracer/lib/option.h>
#include <linear/linear.h>
#include <tracer/light/ray.h>

namespace tracer {

struct shape {
    lib::option<point_on_ray> intersect(ray r) const;

    virtual ~shape();

private:
    virtual lib::option<point_on_ray> intersect_impl(ray r) const = 0;
};

typedef std::vector<std::unique_ptr<shape>> shapes;

} // namespace tracer
