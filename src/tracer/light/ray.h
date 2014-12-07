#pragma once

#include <linear/linear.h>

namespace tracer {

struct point_on_ray;

struct ray {
    static ray from_to(linear::point3d from, linear::point3d to);

    point_on_ray point_along(double distance) const;
    linear::point3d origin() const;
    linear::direction3d direction() const;
private:
    ray() = delete;
    ray(linear::point3d origin, linear::direction3d direction3d);
    linear::point3d origin_;
    linear::direction3d direction_;
};

struct point_on_ray {
    friend struct ray;

    bool operator==(point_on_ray rhs) const;
    bool operator<(point_on_ray rhs) const;
    operator linear::point3d() const;
private:
    point_on_ray(double distance, linear::point3d point);

    double distance_;
    linear::point3d point_;
};

bool operator!=(point_on_ray lhs, point_on_ray rhs);
bool operator<=(point_on_ray lhs, point_on_ray rhs);
bool operator> (point_on_ray lhs, point_on_ray rhs);
bool operator>=(point_on_ray lhs, point_on_ray rhs);

} // namespace tracer
