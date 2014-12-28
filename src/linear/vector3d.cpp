#include <cmath>
#include <iostream>
#include <iomanip>

#include <linear/vector3d.h>

namespace linear {

vector3d::vector3d(double const x, double const y, double const z)
    : coordinates_{{x, y, z}}
{}

vector3d::vector3d()
    : vector3d{0.0, 0.0, 0.0}
{}

vector3d& vector3d::operator+=(vector3d const& rhs) {
    for (auto i = 0u; i < dimension_; ++i) {
        coordinates_[i] += rhs.coordinates_[i];
    }
    return *this;
}

vector3d& vector3d::operator-=(vector3d const& rhs) {
    for (auto i = 0u; i < dimension_; ++i) {
        coordinates_[i] -= rhs.coordinates_[i];
    }
    return *this;
}

double vector3d::x() const { return coordinates_[0]; }
double vector3d::y() const { return coordinates_[1]; }
double vector3d::z() const { return coordinates_[2]; }

double length(vector3d const& v)
{ return std::sqrt(dot_product(v, v)); }

double dot_product(vector3d const& a, vector3d const& b)
{ return a.x()*b.x() + a.y()*b.y() + a.z()*b.z(); }

vector3d cross_product(vector3d const& a, vector3d const& b)
{
    return vector3d{
         a.y() * b.z() - a.z() * b.y(),
        -a.x() * b.z() + a.z() * b.x(),
         a.x() * b.y() - a.y() * b.x()
    };
}


vector3d operator-(vector3d const& v)
{ return vector3d{-v.x(), -v.y(), -v.z()}; }

vector3d operator*(vector3d const& v, double const scalar)
{ return vector3d{v.x() * scalar, v.y() * scalar, v.z() * scalar}; }
vector3d operator/(vector3d const& v, double const scalar)
{ return vector3d{v.x() / scalar, v.y() / scalar, v.z() / scalar}; }


vector3d operator*(double const scalar, vector3d const& v) {return v * scalar; }

std::ostream& operator<<(std::ostream &os, vector3d const& v) {
    os << std::setprecision(2) << std::fixed;
    os << "(" << v.x() << ", " << v.y() << ", " << v.z() <<")";
    return os;
}

} // namespace linear
