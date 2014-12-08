#pragma once
#include <linear/vector3d.h>

namespace linear {

struct point3d {
    point3d(double x, double y, double z);
    point3d();
    point3d& operator+=(vector3d const& rhs);
    point3d& operator-=(vector3d const& rhs);

    vector3d operator-(point3d const& rhs) const;
private:
    vector3d radius_vector_;
};

point3d operator+(point3d lhs,  vector3d const& rhs);
point3d operator-(point3d lhs,  vector3d const& rhs);

} // namespace linear
