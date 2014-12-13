#pragma once

#include <vector>
#include <memory>
#include <tracer/items/item.h>
#include <tracer/images/image.h>
#include <tracer/scene/camera.h>

namespace tracer {

struct scene_builder;

struct scene {
    image render() const;

private:
    friend struct scene_builder;

    scene(camera const& camera, std::vector<item> items);
    color trace(ray const&r) const;
    color calculate_light(intersection_point const& intersection) const;

    camera camera_;
    std::vector<item> items_;
};

} // namespace tracer
