#pragma once
#include <iostream>
#include <array>

#include <utils/operators.h>

namespace linear {

struct vector3d
    : private utils::add_sub<vector3d>
{
    vector3d(double x, double y, double z);
    explicit vector3d(std::array<double, 3> const& coords);

    vector3d();
    vector3d& operator+=(vector3d const& rhs);
    vector3d& operator-=(vector3d const& rhs);

    double x() const;
    double y() const;
    double z() const;

private:
    static size_t constexpr dimension_ = 3;
    std::array<double, dimension_> coordinates_;
};

double length(vector3d const& v);
double dot_product(vector3d const& a, vector3d const& b);
vector3d cross_product(vector3d const& a, vector3d const& b);
vector3d projection(vector3d const& to, vector3d const& from);

vector3d operator-(vector3d const& v);

vector3d operator*(vector3d const& v, double scalar);
vector3d operator/(vector3d const& v, double scalar);

vector3d operator*(double scalar, vector3d const& v);

std::ostream& operator<<(std::ostream &os, vector3d const& v);

} // namespace linear
