#pragma once
#include <array>
#include <memory>
#include <vector>

#include <linear/linear.h>
#include <tracer/light/light_source.h>
#include <tracer/items/item.h>
#include <tracer/scene/scene.h>

namespace tracer {

struct scene_builder {
    scene_builder& center(linear::point3d const& center);
    scene_builder& up_direction(linear::direction3d const& direction);
    scene_builder& camera_position(linear::point3d const& position);
    scene_builder& focal_distance(double distance);
    scene_builder& screen_size(std::array<double, 2> const& size);
    scene_builder& resolution(std::array<unsigned, 2> const& resolution);
    scene_builder& ambient_light(normalized_color const& light);
    scene_builder& add_light(light_source const& s);
    scene_builder& add_item(item i);
    scene build();

private:
    linear::point3d center_ = {0, 0, 0};
    linear::direction3d up_direction_ = {0, 0, 1};
    linear::point3d camera_position_;
    double focal_distance_;
    std::array<double, 2> screen_size_;
    std::array<unsigned, 2> resolution_ = {{640u, 480u}};
    normalized_color ambient_light_;
    std::vector<light_source> lights_;
    std::vector<item> items_;
};

} // namespace tracer
