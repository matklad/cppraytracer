#pragma once
#include <linear/vector3d.h>
#include <linear/point3d.h>

namespace linear {

struct direction3d
    : vector3d
{
    explicit direction3d(vector3d const& v);
    direction3d(double a, double b, double c);

private:
    direction3d() = delete;
};

direction3d cross_product(direction3d const& a, direction3d const& b);

direction3d direction_from_to(point3d const& from, point3d const& to);

} // namespace linear
