#include <cmath>
#include <tracer/images/color.h>

namespace tracer {

namespace {
double saturate(double const c) { return std::max(0.0, std::min(1.0, c)); }
}

color::color(double const r, double const g, double const b)
    :data_{{saturate(r), saturate(g), saturate(b)}}
{}

color::color(): color(0.0, 0.0, 0.0) {}

color& color::operator+=(color const& other)
{
    for (size_t i = 0; i < data_.size(); ++i)
    { data_[i] = saturate(data_[i] + other.data_[i]); }
    return *this;
}

color& color::operator-=(color const& other)
{
    for (size_t i = 0; i < data_.size(); ++i)
    { data_[i] = saturate(data_[i] - other.data_[i]); }
    return *this;
}

color& color::operator*=(double const alpha)
{
    for (size_t i = 0; i < data_.size(); ++i)
    { data_[i] = saturate(data_[i] * alpha); }
    return *this;
}

double color::r() const { return data_[0]; }
double color::g() const { return data_[1]; }
double color::b() const { return data_[2]; }

color operator*(double const alpha, color c) { return c *= alpha; }
color operator*(color c, double const alpha) { return c *= alpha; }

} // namespace tracer
