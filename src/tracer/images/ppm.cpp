#include <iostream>
#include <tracer/images/ppm.h>

void tracer::write_ppm(std::ostream &os, image const& im) {
    size_t const width = im.dimensions()[0];
    size_t const height = im.dimensions()[1];
    unsigned const max_val = 255;
    os << "P6\n"
       << width << " " << height << "\n"
       << max_val << "\n";
    for (size_t y = 0; y < height; ++y) {
        for (size_t x = 0; x < width; ++x)
        {
            color const c = im(x, y);
            char const pixel[3] = {char(c.r() * max_val),
                                   char(c.g() * max_val),
                                   char(c.b() * max_val)};
            os.write(pixel, 3);
        }
    }
}
