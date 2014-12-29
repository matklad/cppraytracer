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
            auto const rgb = im(x, y).to_8_bit_rgb();
            char buff[3] = {};
            for (auto i = 0u; i < 3; ++i) {
                buff[i] = rgb[i];
            }
            os.write(buff, 3);
        }
    }
}
