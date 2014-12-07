#pragma once

#include <vector>
#include <memory>
#include <tracer/items/shapes/shape.h>
#include <tracer/images/image.h>
#include <tracer/scene/camera.h>

namespace tracer {

struct scene {
    scene(camera camera, shapes shapes);

    image render() const;
private:
    color trace(ray r) const;

    camera camera_;
    shapes shapes_;
};

} // namespace tracer
