#include <array>

#include <linear/point3d.h>

namespace linear {

point3d::point3d(double const x, double const y, double const z)
    : radius_vector_{x, y, z}
{}

point3d::point3d(std::array<double, 3> const& coords)
    : point3d(coords[0], coords[1], coords[2])
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

std::ostream& operator<<(std::ostream &os, point3d const& p)
{ return os << p.radius_vector_; }

} // namespace linear
