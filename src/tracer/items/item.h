#pragma once
#include <memory>

#include <utils/option.h>
#include <linear/direction3d.h>
#include <tracer/items/geometry/shape.h>
#include <tracer/items/material.h>
#include <tracer/light/ray.h>
#include <tracer/images/color.h>

namespace tracer {

struct intersection_point;

struct item {
    item(std::unique_ptr<shape> shape, material const& material);

    utils::option<intersection_point> intersect(ray const& r) const;
    color calculate_ambient_color(color const& ambient_light) const;
    color calculate_diffuse_color(color const& diffuse_light,
                                  linear::direction3d const& direction,
                                  intersection_point const& point) const;

private:
    std::unique_ptr<shape> shape_;
    material material_;
};

struct intersection_point
    : utils::comparable<intersection_point>
{
    item const& get_item() const;
    bool operator==(intersection_point const& rhs) const;
    bool operator< (intersection_point const& rhs) const;

    operator linear::point3d() const;
private:
    friend struct item;
    intersection_point(point_on_ray const& point,
                       linear::direction3d const& normal,
                       item const& item);

    point_on_ray point_;
    linear::direction3d normal_;
    item const& item_;
};


} // namespace tracer
