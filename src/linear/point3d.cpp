#include <linear/point3d.h>

namespace linear {

point3d::point3d(double const x, double const y, double const z)
    : radius_vector_{x, y, z}
{}

point3d::point3d()
    : point3d(0.0, 0.0, 0.0)
{}

point3d& point3d::operator+=(vector3d const& rhs)
{
    radius_vector_ += rhs;
    return *this;
}

point3d& point3d::operator-=(vector3d const& rhs)
{
    radius_vector_ -= rhs;
    return *this;
}

vector3d point3d::operator-(point3d const& rhs) const
{ return radius_vector_ - rhs.radius_vector_; }

point3d operator+(point3d lhs, vector3d const& rhs)
{ return lhs += rhs; }

point3d operator-(point3d lhs, vector3d const& rhs)
{ return lhs -= rhs; }

} // namespace linear
