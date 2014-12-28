#include <memory>

#include "tracer/scene/scene_builder.h"
#include "tracer/scene/scene.h"
#include "tracer/scene/camera.h"

namespace tracer {

scene_builder scene_builder::center(linear::point3d const& center) &&
{ center_ = center; return std::move(*this); }

scene_builder scene_builder::up_direction(linear::direction3d const& direction) &&
{ up_direction_ = direction; return std::move(*this); }

scene_builder scene_builder::camera_position(linear::point3d const& position) &&
{ camera_position_ = position; return std::move(*this); }

scene_builder scene_builder::focal_distance(double distance) &&
{ focal_distance_ = distance; return std::move(*this); }

scene_builder scene_builder::screen_size(std::array<double, 2> const& size) &&
{ screen_size_ = size; return std::move(*this); }

scene_builder scene_builder::resolution(std::array<unsigned, 2> const& resolution) &&
{ resolution_ = resolution; return std::move(*this); }

scene_builder scene_builder::ambient_light(normalized_color const& light) &&
{ ambient_light_ = light; return std::move(*this); }

scene_builder scene_builder::add_light(light_source const& s) &&
{ lights_.push_back(s); return std::move(*this); }

scene_builder scene_builder::add_item(item i) &&
{
    items_.push_back(std::move(i));
    return std::move(*this);
}

scene scene_builder::build() && {
    auto const view_direction =
        direction_from_to(camera_position_, center_);

    auto const right_direction =
        cross_product(view_direction, up_direction_);
    auto const true_up_direction =
        cross_product(right_direction, view_direction);

    camera const cam{
        camera_position_,
        view_direction,
        true_up_direction,
        right_direction,
        focal_distance_,
        screen{screen_size_, resolution_}
    };
    return {cam, ambient_light_, lights_, std::move(items_)};
}

} // namespace tracer
