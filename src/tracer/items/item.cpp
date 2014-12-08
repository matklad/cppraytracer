#include <tracer/items/item.h>
#include <tracer/items/geometry/shape.h>
#include <tracer/items/material.h>
#include <tracer/images/color.h>
#include <utils/option.h>

namespace tracer {

item::item(std::unique_ptr<shape> shape, material const& material)
    : shape_{std::move(shape)}
    , material_{material}
{}

utils::option<intersection_point> item::intersect(ray const& r) const {
    if (auto i = shape_->intersect(r))
    {
        return utils::some(intersection_point{i.value(), *this});
    }
    return utils::none;
}

color item::calculate_color() const
{ return material_.calculate_color(); }

intersection_point::intersection_point(point_on_ray const& point,
                                       item const& item)
    : point_{point}
    , item_{item}
{}

item const& intersection_point::get_item() const { return item_; }

bool intersection_point::operator==(intersection_point const& rhs) const
{ return point_ == rhs.point_; }

bool intersection_point::operator<(intersection_point const& rhs) const
{ return point_ < rhs.point_; }

} // namespace tracer
