#include <cmath>
#include <tracer/images/color.h>

namespace tracer {

color::color(double const r, double const g, double const b)
    :data_{{r, g, b}}
{}

color::color(): color(0.0, 0.0, 0.0) {}

color& color::operator+=(color const& rhs) {
    for (size_t i = 0; i < data_.size(); ++i)
    { data_[i] = data_[i] + rhs.data_[i]; }
    return *this;
}

color& color::operator-=(color const& rhs) {
    for (size_t i = 0; i < data_.size(); ++i)
    { data_[i] = data_[i] - rhs.data_[i]; }
    return *this;
}

color& color::operator*=(color const& rhs) {
    for (size_t i = 0; i < data_.size(); ++i)
    { data_[i] = data_[i] * rhs.data_[i]; }
    return *this;
}

color& color::operator*=(double const alpha)
{
    for (size_t i = 0; i < data_.size(); ++i)
    { data_[i] = data_[i] * alpha; }
    return *this;
}

color& color::operator/=(double const alpha)
{
    for (size_t i = 0; i < data_.size(); ++i)
    { data_[i] = data_[i] / alpha; }
    return *this;
}

double color::r() const { return data_[0]; }
double color::g() const { return data_[1]; }
double color::b() const { return data_[2]; }

color operator*(color lhs, color const& rhs) {return lhs *= rhs; };
color operator*(double const alpha, color c) { return c *= alpha; }
color operator*(color c, double const alpha) { return c *= alpha; }
color operator/(double const alpha, color c) { return c /= alpha; }
color operator/(color c, double const alpha) { return c /= alpha; }

} // namespace tracer
