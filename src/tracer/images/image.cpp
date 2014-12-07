#include <cassert>
#include <tracer/images/image.h>

namespace tracer {

image::image(unsigned width, unsigned height)
    : dimensions_{{width, height}}
    , data_(width * height)
{}

image::image(std::array<unsigned, 2> dimensions)
    : image(dimensions[0], dimensions[1])
{}

std::array<unsigned, 2> image::dimensions() const { return dimensions_; }

color const& image::operator()(unsigned x, unsigned y) const {
    assert (x < dimensions_[0] && y < dimensions_[1]);
    return data_[x * dimensions_[1] + y];
}

color& image::operator()(unsigned x, unsigned y) {
    assert (x < dimensions_[0] && y < dimensions_[1]);
    return data_[x * dimensions_[1] + y];
}

} // namespace tracer
