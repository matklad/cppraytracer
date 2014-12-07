#pragma once
#include <linear/vector3d.h>

namespace linear {

struct direction3d
    : vector3d {
    explicit direction3d(vector3d v);
    direction3d(double a, double b, double c);

private:
    direction3d() = delete;
};

direction3d cross_product(direction3d a, direction3d b);

} // namespace linear
