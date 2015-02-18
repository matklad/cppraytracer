#pragma once
#include <linear/vector3d.h>
#include <linear/point3d.h>

namespace linear {

struct direction3d {
    explicit direction3d(vector3d const& v);
    direction3d(double a, double b, double c);

    operator vector3d() const;

private:
    vector3d directrion_;
};

direction3d direction_from_to(point3d const& from, point3d const& to);

} // namespace linear
