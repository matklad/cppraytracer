#pragma once
#include <vector>
#include <iostream>
#include <tracer/items/geometry/triangle.h>

namespace tracer {

std::vector<triangle> parse_obj(std::istream &is);

} // namespace tracer
