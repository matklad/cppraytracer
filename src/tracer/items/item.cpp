#include <memory>

#include <tracer/items/item.h>
#include <tracer/items/geometry/shape.h>
#include <tracer/items/geometry/sphere.h>
#include <tracer/items/material.h>
#include <tracer/images/color.h>
#include <utils/option.h>

namespace tracer {

item item::make_sphere(material const& material,
                    linear::point3d const& position,
                    double const radius) {
    return {material, std::make_unique<sphere>(position, radius)};
}

item::~item() {}

item::item(material const& material, std::unique_ptr<shape> shape)
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

linear::direction3d item::normal_at(linear::point3d const& point) const
{ return shape_->normal_at(point); }

color item::calculate_ambient_color(color const& ambient_light) const
{ return material_.calculate_ambient_color(ambient_light); }

color item::calculate_diffuse_color(color const& diffuse_light,
                                    linear::direction3d const& direction,
                                    linear::direction3d const& normal) const
{
    return material_.calculate_diffuse_color(
            diffuse_light,
            direction,
            normal);
}


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

intersection_point::operator linear::point3d() const { return point_; }

} // namespace tracer
