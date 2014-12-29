#pragma once
#include <array>

#include <linear/vector3d.h>

namespace linear {

struct point3d {
    point3d(double x, double y, double z);
    explicit point3d(std::array<double, 3> const& coords);
    point3d();
    point3d& operator+=(vector3d const& rhs);
    point3d& operator-=(vector3d const& rhs);

    vector3d operator-(point3d const& rhs) const;
private:
    friend std::ostream& operator<<(std::ostream &os, point3d const& p);

    vector3d radius_vector_;
};

point3d operator+(point3d lhs,  vector3d const& rhs);
point3d operator-(point3d lhs,  vector3d const& rhs);

std::ostream& operator<<(std::ostream &os, point3d const& p);

} // namespace linear
