#pragma once

#include <utils/operators.h>
#include <linear/linear.h>

namespace tracer {

struct ray {
    static ray from_to(linear::point3d const& from, linear::point3d const& to);

    linear::point3d point_along(double distance) const;
    linear::point3d origin() const;
    linear::direction3d direction() const;
private:
    ray() = delete;
    ray(linear::point3d const& origin, linear::direction3d const& direction3d);

    linear::point3d origin_;
    linear::direction3d direction_;
};

} // namespace tracer
