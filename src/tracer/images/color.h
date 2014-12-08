#pragma once

#include <array>
#include <utils/operators.h>

namespace tracer {

struct color
    : private utils::add_sub<color>
{
    color(double r, double g, double b);
    color();

    color& operator+=(color const& other);
    color& operator-=(color const& other);
    color& operator*=(double alpha);

    double r() const;
    double g() const;
    double b() const;

private:
    std::array<double, 3> data_;
};

color operator*(double alpha, color c);
color operator*(color c, double alpha);

} // namespace tracer
