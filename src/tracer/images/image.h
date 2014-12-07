#pragma once

#include <array>
#include <vector>
#include <cstddef>
#include <tracer/images/color.h>

namespace tracer {

struct image {
    image(unsigned width, unsigned height);
    image(std::array<unsigned, 2> dimensions);

    std::array<unsigned, 2> dimensions() const;
    color const& operator()(unsigned x, unsigned y) const;
    color& operator()(unsigned x, unsigned y);

private:
    std::array<unsigned, 2> dimensions_;
    std::vector<color> data_;
};


}
