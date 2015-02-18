#include <linear/direction3d.h>

namespace linear {

direction3d::direction3d(vector3d const& v)
    : directrion_{v.x() / length(v), v.y() / length(v), v.z() / length(v)}
{}

direction3d::direction3d(double const a, double const b, double const c)
    : direction3d{vector3d{a, b, c}}
{}

direction3d::operator vector3d() const { return directrion_; }

direction3d direction_from_to(point3d const& from, point3d const& to)
{ return direction3d(to - from); }

} // namespace linear
