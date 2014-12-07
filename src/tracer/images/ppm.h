#pragma once

#include <iostream>
#include <tracer/images/image.h>

namespace tracer {

void write_ppm(std::ostream &os, image const& im);

}
