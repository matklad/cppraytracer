#include <cassert>

#include <tracer/scene/camera.h>
#include <linear/linear.h>

namespace tracer {

camera::camera(linear::point3d const& position,
               linear::direction3d const& view_direction,
               linear::direction3d const& up_direction,
               linear::direction3d const& right_direction,
               double const focal_distance,
               screen const& screen)
    : position_(position)
    , view_direction_(view_direction)
    , up_direction_(up_direction)
    , right_direction_(right_direction)
    , focal_distance_(focal_distance)
    , screen_(screen)
{}

ray camera::ray_for_pixel(unsigned x, unsigned y) const {
    assert (x < screen_.resolution[0] && y < screen_.resolution[1]);
    std::array<unsigned, 2> const pixel = {{x, y}};
    auto const screen_center = position_ + focal_distance_ * view_direction_;

    std::array<double, 2> ds = {};
    for (size_t i = 0; i < 2; ++i)
    {
        auto signed_mid = static_cast<int>(screen_.resolution[i] / 2);
        auto signed_pixel = static_cast<int>(pixel[i]);
        auto const pixel_d =  signed_mid - signed_pixel;
        ds[i] = screen_.dimensions[i] * pixel_d / screen_.resolution[i];
    }

    auto const point_on_screen =
        screen_center + ds[0] * right_direction_ + ds[1] * up_direction_;

    return ray::from_to(position_, point_on_screen);
}

std::array<unsigned, 2> camera::resolution() const
{ return screen_.resolution; }

} // namespace tracer
