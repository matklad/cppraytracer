#include <memory>
#include <vector>

#include <tracer/scene/scene.h>
#include <tracer/items/item.h>

namespace tracer {

scene::scene(camera const camera, std::vector<item> items)
    : camera_{camera}
    , items_(std::move(items))
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
    utils::option<intersection_point> intersection = utils::none;
    for (auto const& obj: items_) {
        if (auto const some_i = obj.intersect(r)) {
            intersection_point const i = some_i.value();
            if (!intersection || (intersection && i < intersection.value())) {
                intersection = i;
            }
        }
    }
    return intersection
        ? intersection.value().get_item().calculate_color()
        : color(0, 0, 0);
}

}
