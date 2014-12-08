#pragma once

#include <vector>
#include <memory>
#include <tracer/items/item.h>
#include <tracer/images/image.h>
#include <tracer/scene/camera.h>

namespace tracer {

struct scene {
    scene(camera const& camera, std::vector<item> items);

    image render() const;

private:
    color trace(ray const&r) const;
    color calculate_light(intersection_point const& intersection) const;

    camera camera_;
    std::vector<item> items_;
};

} // namespace tracer
