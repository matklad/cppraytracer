#pragma once

#include <vector>
#include <memory>
#include <tracer/items/item.h>
#include <tracer/images/image.h>
#include <tracer/scene/camera.h>

namespace tracer {

struct scene {
    scene(camera camera, std::vector<item> items);

    image render() const;
private:
    color trace(ray r) const;

    camera camera_;
    std::vector<item> items_;
};

} // namespace tracer
