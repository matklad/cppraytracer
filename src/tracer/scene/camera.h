#pragma once
#include <array>

#include <linear/linear.h>
#include <tracer/light/ray.h>

namespace tracer {

struct scene_builder;

struct screen
{
    std::array<double, 2> dimensions;
    std::array<unsigned, 2> resolution;
};

struct camera {
    ray ray_for_pixel(unsigned x, unsigned y) const;
    std::array<unsigned, 2> resolution() const;

private:
    friend struct scene_builder;
    camera(linear::point3d const& position,
           linear::direction3d const& view_direction,
           linear::direction3d const& up_direction,
           linear::direction3d const& right_direction,
           double focal_distance,
           screen const& screen);

    linear::point3d position_;
    linear::direction3d view_direction_;
    linear::direction3d up_direction_;
    linear::direction3d right_direction_;
    double focal_distance_;
    screen screen_;
};

} // namespace tracer
