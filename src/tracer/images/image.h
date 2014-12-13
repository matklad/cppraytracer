#pragma once

#include <array>
#include <vector>
#include <cstddef>
#include <tracer/images/normalized_color.h>

namespace tracer {

struct image {
    image(unsigned width, unsigned height);
    image(std::array<unsigned, 2> const& dimensions);

    std::array<unsigned, 2> dimensions() const;
    normalized_color const& operator()(unsigned x, unsigned y) const;
    normalized_color& operator()(unsigned x, unsigned y);

private:
    std::array<unsigned, 2> dimensions_;
    std::vector<normalized_color> data_;
};

image upsample(image const& im, unsigned rate);

}
