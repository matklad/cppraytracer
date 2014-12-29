#include <iostream>
#include <string>
#include <array>
#include <tracer/images/image.h>
#include <tracer/images/terminal.h>

namespace tracer {

namespace  {

std::string color_s(char c, std::array<uint8_t, 3> const& rgb) {
    std::string preffix = "\x1b[38;2;";
    std::string sn = ";";
    std::string suffix = "\x1b[0m";
    return preffix
        + std::to_string(rgb[0]) + sn
        + std::to_string(rgb[1]) + sn
        + std::to_string(rgb[2]) + "m" + c + suffix;
}

} // namespace

void write_terminal_escape(std::ostream &os, image const& im) {
    auto const width = im.dimensions()[0];
    auto const height = im.dimensions()[1];
    std::string const text = "HELLOWORLD";
    for (auto y = 0u; y < height; ++y) {
        for (auto x = 0u; x < width; ++x) {
            os << color_s(text[(x + y) % text.size()],
                          im(x, y).to_8_bit_rgb());
        }
        os << std::endl;
    }
}

}
