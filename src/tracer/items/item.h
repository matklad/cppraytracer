#pragma once
#include <memory>
#include <utils/option.h>
#include <tracer/items/geometry/shape.h>
#include <tracer/items/material.h>
#include <tracer/light/ray.h>
#include <tracer/images/color.h>

namespace tracer {


struct intersection_point;

struct item {
    item(std::unique_ptr<shape> shape, material material);

    utils::option<intersection_point> intersect(ray r) const;
    color calculate_color() const;
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

private:
    friend struct item;
    intersection_point(point_on_ray point, item const& item);

    point_on_ray point_;
    item const& item_;
};


} // namespace tracer
