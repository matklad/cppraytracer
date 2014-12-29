#pragma once

#include <array>
#include <utils/operators.h>

namespace tracer {

struct color
    : private utils::add_sub<color>
{
    color(double r, double g, double b);
    color();

    color& operator+=(color const& rhs);
    color& operator-=(color const& rhs);
    color& operator*=(color const& rhs);
    color& operator*=(double alpha);
    color& operator/=(double alpha);


    double r() const;
    double g() const;
    double b() const;

private:
    std::array<double, 3> data_;
};

color operator*(color lhs, color const& rhs);
color operator*(double alpha, color c);
color operator*(color c, double alpha);
color operator/(double alpha, color c);
color operator/(color c, double alpha);

const color white({.7, .7, .7});
const color red({.7, .05, .05});
const color green({.05, .7, .05});
const color blue({.05, .05, .7});

} // namespace tracer
