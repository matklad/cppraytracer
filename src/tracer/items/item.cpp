#include <memory>

#include <tracer/items/item.h>
#include <tracer/items/geometry/shape.h>
#include <tracer/items/geometry/sphere.h>
#include <tracer/items/geometry/triangle.h>
#include <tracer/items/material.h>
#include <tracer/images/color.h>
#include <utils/option.h>

namespace tracer {

item item::make_sphere(material const& material,
                       linear::point3d const& position,
                       double const radius)
{ return {material, std::make_unique<sphere>(position, radius)}; }

item item::make_triangle(material const& material,
                         std::array<linear::point3d, 3> const& points)
{ return {material, std::make_unique<triangle>(points)}; }

item item::make_triangle(material const& material, triangle const& t)
{ return {material, std::make_unique<triangle>(t)}; }

item::~item() {}

item::item(item&& other)
    : shape_(std::move(other.shape_))
    , material_(std::move(other.material_))
{}

item& item::operator=(item&& other) {
    shape_ = std::move(other.shape_);
    material_ = std::move(other.material_);
    return *this;
}

item::item(material const& material, std::unique_ptr<shape> shape)
    : shape_{std::move(shape)}
    , material_{material}
{}

utils::option<intersection_point> item::intersect(ray const& r) const {
    if (auto i = shape_->intersect(r))
    {
        return utils::some(intersection_point{*i, r, *this});
    }
    return utils::none;
}

linear::direction3d item::normal_at(linear::point3d const& point) const
{ return shape_->normal_at(point); }

intersection_point::intersection_point(double t, ray const& ray, item const& item)
    : t_{t}
    , ray_{ray}
    , item_{item}
{}

intersection_point::operator linear::point3d() const
{ return ray_.point_along(t_); }

bool intersection_point::operator==(intersection_point const& rhs) const
{ return t_ == rhs.t_; }

bool intersection_point::operator<(intersection_point const& rhs) const
{ return t_ < rhs.t_; }

color intersection_point::calculate_ambient_color(color const& ambient_light) const
{ return item_.material_.calculate_ambient_color(ambient_light); }

color intersection_point::calculate_diffuse_color(color const& diffuse_light,
                                    linear::direction3d const& direction) const
{
    auto const normal = item_.normal_at(*this);
    return item_.material_.calculate_diffuse_color(
        diffuse_light,
        direction,
        normal);
}

} // namespace tracer
