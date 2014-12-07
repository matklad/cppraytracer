#include <memory>

#include <tracer/scene/scene.h>

namespace tracer {

scene::scene(camera const camera, shapes shapes)
    : camera_{camera}
    , shapes_(std::move(shapes))
{}

image scene::render() const
{
    image result(camera_.resolution());
    for (unsigned x = 0; x < camera_.resolution()[0]; ++x) {
        for (unsigned y = 0; y < camera_.resolution()[1]; ++y) {
            ray const r = camera_.ray_for_pixel(x, y);
            result(x, y) = trace(r);
        }
    }
    return result;
}

color scene::trace(ray const r) const {
    for (auto const& s: shapes_) {
        if (s->intersect(r)) {
            return color(0, 0, 1);
        }
    }
    return color(1, 1, 1);
}

}
