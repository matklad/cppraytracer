#include <cassert>

#include <tracer/scene/camera.h>
#include <linear/linear.h>

namespace tracer {

namespace {
using namespace linear;

direction3d calculate_view_direction(camera_parameters const& parameters)
{ return direction_from_to(parameters.position, parameters.look_at); }

direction3d calculate_up_direction(camera_parameters const& parameters) {
    direction3d const view = calculate_view_direction(parameters);
    direction3d const right = cross_product(view, parameters.up_direction);
    return cross_product(right, view);
}

}

camera::camera(camera_parameters const& parameters)
    : position_(parameters.position)
    , view_direction_(calculate_view_direction(parameters))
    , up_direction_(calculate_up_direction(parameters))
    , right_direction_(cross_product(view_direction_, up_direction_))
    , focal_distance_(parameters.focal_distance)
    , screen_(parameters.screen)
{}

ray camera::ray_for_pixel(unsigned x, unsigned y) const {
    assert (x < screen_.resolution[0] && y < screen_.resolution[1]);
    std::array<unsigned, 2> const pixel = {{x, y}};
    point3d const screen_center = position_ + focal_distance_ * view_direction_;

    std::array<double, 2> ds = {};
    for (size_t i = 0; i < 2; ++i)
    {
        int const pixel_d = screen_.resolution[i] / 2 - pixel[i];
        ds[i] = screen_.dimensions[i] * pixel_d / screen_.resolution[i];
    }

    point3d const point_on_screen =
        screen_center + ds[0] * right_direction_ + ds[1] * up_direction_;

    return ray::from_to(position_, point_on_screen);
}

std::array<unsigned, 2> camera::resolution() const
{ return screen_.resolution; }

} // namespace tracer
