#pragma once

#include <iostream>
#include <tracer/images/image.h>

namespace tracer {

void write_terminal_escape(std::ostream &os, image const& im);

}
