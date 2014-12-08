#pragma once

#include <utils/operators.h>
#include <linear/linear.h>

namespace tracer {

struct point_on_ray;

struct ray {
    static ray from_to(linear::point3d const& from, linear::point3d const& to);

    point_on_ray point_along(double distance) const;
    linear::point3d origin() const;
    linear::direction3d direction() const;
private:
    ray() = delete;
    ray(linear::point3d const& origin, linear::direction3d const& direction3d);

    linear::point3d origin_;
    linear::direction3d direction_;
};

struct point_on_ray
    : private utils::comparable<point_on_ray>
{
    friend struct ray;

    bool operator==(point_on_ray const& rhs) const;
    bool operator< (point_on_ray const& rhs) const;
    operator linear::point3d() const;
private:
    point_on_ray(double distance, linear::point3d const& point);

    double distance_;
    linear::point3d point_;
};

} // namespace tracer
