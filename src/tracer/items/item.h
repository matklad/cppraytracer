#pragma once
#include <memory>

#include <utils/option.h>
#include <linear/direction3d.h>
#include <tracer/items/material.h>
#include <tracer/items/geometry/triangle.h>
#include <tracer/light/ray.h>
#include <tracer/images/color.h>

namespace tracer {

struct intersection_point;
struct shape;

struct item {
    static item make_sphere(material const& material,
                            linear::point3d const& position,
                            double radius);
    static item make_triangle(material const& material, triangle const& t);

    item(item&&);
    item& operator=(item&&);
    ~item();

    utils::option<intersection_point> intersect(ray const& r) const;
    linear::direction3d normal_at(linear::point3d const& point) const;

private:
    friend struct intersection_point;
    item(material const& material, std::unique_ptr<shape> shape);

    std::unique_ptr<shape> shape_;
    material material_;
};

struct intersection_point
    : utils::comparable<intersection_point>
{
    operator linear::point3d() const;
    bool operator==(intersection_point const& rhs) const;
    bool operator< (intersection_point const& rhs) const;

    color calculate_ambient_color(color const& ambient_light) const;
    color calculate_diffuse_color(color const& diffuse_light,
                                  linear::direction3d const& direction) const;
    color calculate_specular_color(color const& specular_light,
                                   linear::direction3d const& light_direction) const;

private:
    friend struct item;
    intersection_point(double t, ray const& ray, item const& item);

    double t_;
    ray const& ray_;
    item const& item_;
};


} // namespace tracer
