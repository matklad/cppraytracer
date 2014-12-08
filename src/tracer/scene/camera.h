#pragma once
#include <array>

#include <linear/linear.h>
#include <tracer/light/ray.h>

namespace tracer {

struct screen
{
    std::array<double, 2> dimensions;
    std::array<unsigned, 2> resolution;
};

struct camera_parameters {
    linear::point3d position;
    linear::point3d look_at;
    linear::direction3d up_direction;
    double focal_distance;
    screen screen;
};


struct camera {
    camera(camera_parameters const& parameters);
    ray ray_for_pixel(unsigned x, unsigned y) const;
    std::array<unsigned, 2> resolution() const;

private:
    linear::point3d position_;
    linear::direction3d view_direction_;
    linear::direction3d up_direction_;
    linear::direction3d right_direction_;
    double focal_distance_;
    screen screen_;
};

} // namespace tracer
