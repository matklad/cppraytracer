#include <linear/direction3d.h>

namespace linear {

direction3d::direction3d(vector3d const v)
    : vector3d{v.x() / length(v), v.y() / length(v), v.z() / length(v)}
{}

direction3d::direction3d(double a, double b, double c)
    : direction3d{vector3d{a, b, c}}
{}


direction3d cross_product(direction3d const a, direction3d const b)
{ return direction3d{cross_product(static_cast<vector3d>(a), b)};}

} // namespace linear
