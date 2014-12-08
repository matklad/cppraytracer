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
        auto ip = intersection_point
            {i.value(), shape_->normal_at(i.value()),*this};
        return utils::some(ip);
    }
    return utils::none;
}

color item::calculate_ambient_color(color const& ambient_light) const
{ return material_.calculate_ambient_color(ambient_light); }

color item::calculate_diffuse_color(color const& diffuse_light,
                                    linear::direction3d const& direction,
                                    intersection_point const& point) const
{
    return material_.calculate_diffuse_color(
            diffuse_light,
            direction,
            point.normal_);
}


intersection_point::intersection_point(point_on_ray const& point,
                                       linear::direction3d const& normal,
                                       item const& item)
    : point_{point}
    , normal_{normal}
    , item_{item}
{}

item const& intersection_point::get_item() const { return item_; }

bool intersection_point::operator==(intersection_point const& rhs) const
{ return point_ == rhs.point_; }

bool intersection_point::operator<(intersection_point const& rhs) const
{ return point_ < rhs.point_; }

intersection_point::operator linear::point3d() const { return point_; }

} // namespace tracer
