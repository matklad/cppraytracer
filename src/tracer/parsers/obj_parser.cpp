#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>
#include <cassert>
#include <regex>

#include <tracer/parsers/obj_parser.h>
#include <linear/linear.h>

namespace tracer {

namespace  {

constexpr auto dim = 3;

struct face {
    size_t a;
    size_t b;
    size_t c;
};

linear::point3d read_point(std::smatch const& match) {
    std::array<double, dim> coords;
    for (auto i = 0u; i < 3; ++i) {
        coords[i] = std::stod(match[i + 1]);
    }
    return linear::point3d{coords};
}

face read_face(std::smatch const& match) {
    std::array<unsigned, dim> inds;
    for (auto i = 0u; i < 3; ++i) {
        inds[i] = std::stoul(match[3 * i + 1]) - 1;
    }
    return {inds[0], inds[1], inds[2]};
}

std::vector<triangle> assemble_triangles(
    std::vector<linear::point3d> const& points,
    std::vector<face> const& faces)
{
    std::vector<triangle> result;
    for (auto const& f: faces) {
        const triangle t{{{points[f.a], points[f.b], points[f.c]}}};
        result.push_back(t);
    }
    return result;
}

} // namespace

std::vector<triangle> parse_obj(std::istream &is) {
    const std::string float_group = "\\s+(-?\\d+\\.\\d+)";
    const std::regex  vertex_re{"v" + float_group + float_group + float_group};
    const std::string index_group = "\\s+(\\d+)/(\\d+)/(\\d+)";
    const std::regex  face_re{"f" + index_group + index_group + index_group};

    std::vector<linear::point3d> points;
    std::vector<face> faces;

    std::string line;
    while (std::getline(is, line)) {
        std::smatch base_match;
        if (std::regex_match(line, base_match, vertex_re)) {
            points.push_back(read_point(base_match));
        } else if (std::regex_match(line, base_match, face_re)) {
            faces.push_back(read_face(base_match));
        }
    }

    return assemble_triangles(points, faces);
}

} // namespace tracer
