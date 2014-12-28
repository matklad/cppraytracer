#include <cassert>
#include <tracer/images/image.h>

namespace tracer {

image::image(unsigned const width, unsigned const height)
    : dimensions_{{width, height}}
    , data_(width * height)
{}

image::image(std::array<unsigned, 2> const& dimensions)
    : image(dimensions[0], dimensions[1])
{}

std::array<unsigned, 2> image::dimensions() const { return dimensions_; }

normalized_color const& image::operator()(unsigned const x, unsigned const y) const {
    assert (x < dimensions_[0] && y < dimensions_[1]);
    return data_[x * dimensions_[1] + y];
}

normalized_color& image::operator()(unsigned const x, unsigned const y) {
    assert (x < dimensions_[0] && y < dimensions_[1]);
    return data_[x * dimensions_[1] + y];
}

image upsample(image const& im, unsigned rate) {
    image result{im.dimensions()[0] / rate, im.dimensions()[1] / rate};
    for (auto x = 0u; x < result.dimensions()[0]; ++x) {
        for (auto y = 0u; y < result.dimensions()[1]; ++y) {
            color sum;
            for (auto dx = 0u; dx < rate; ++dx) {
                for (auto dy = 0u; dy < rate; ++dy) {
                    sum += im(x * rate + dx, y * rate + dy);
                }
            }
            result(x, y) = normalized_color(sum / (rate * rate));
        }
    }
    return result;
};

} // namespace tracer
