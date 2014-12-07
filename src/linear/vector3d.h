#pragma once
#include <iostream>
#include <array>

#include <tracer/lib/operators.h>

namespace linear {

struct vector3d: private add_sub<vector3d> {
    vector3d(double x, double y, double z);
    vector3d();
    vector3d& operator+=(vector3d rhs);
    vector3d& operator-=(vector3d rhs);

    double x() const;
    double y() const;
    double z() const;

private:
    static size_t const dimension_ = 3;
    std::array<double, dimension_> coordinates_;
};

double length(vector3d v);
double dot_product(vector3d a, vector3d b);
vector3d cross_product(vector3d a, vector3d b);

vector3d operator-(vector3d v);

vector3d operator*(vector3d v, double scalar);
vector3d operator/(vector3d v, double scalar);

vector3d operator*(double scalar, vector3d v);

std::ostream& operator<<(std::ostream &os, vector3d v);

} // namespace linear
