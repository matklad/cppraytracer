#include <iostream>
#include <tracer/images/ppm.h>

void tracer::write_ppm(std::ostream &os, image const& im) {
    auto const width = im.dimensions()[0];
    auto const height = im.dimensions()[1];
    auto const max_val = 255u;
    os << "P6\n"
       << width << " " << height << "\n"
       << max_val << "\n";
    for (auto y = 0u; y < height; ++y) {
        for (auto x = 0u; x < width; ++x)
        {
            auto const c = im(x, y);
            char const pixel[3] = {char(c.r() * max_val),
                                   char(c.g() * max_val),
                                   char(c.b() * max_val)};
            os.write(pixel, 3);
        }
    }
}
