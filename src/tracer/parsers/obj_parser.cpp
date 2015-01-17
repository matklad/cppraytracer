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

template<typename T>
using array3 = std::array<T, dim>;

template<typename F, typename T>
auto map(F f, array3<T> xs) -> array3<decltype(f(xs[0]))> {
    return {{f(xs[0]), f(xs[1]), f(xs[2])}};
}

struct face {
    array3<size_t> points;
    array3<size_t> normals;
};

linear::point3d read_point(std::smatch const& match) {
    array3<double> coords;
    for (auto i = 0u; i < 3; ++i) {
        coords[i] = std::stod(match[i + 1]);
    }
    return linear::point3d{coords};
}

linear::direction3d read_normal(std::smatch const& match) {
    array3<double> coords;
    for (auto i = 0u; i < 3; ++i) {
        coords[i] = std::stod(match[i + 1]);
    }
    return linear::direction3d{linear::vector3d{coords}};
}

face read_face(std::smatch const& match) {
    array3<size_t> vi;
    array3<size_t> ni;
    for (auto i = 0u; i < 3; ++i) {
        vi[i] = std::stoul(match[3 * i + 1]) - 1;
        ni[i] = std::stoul(match[3 * i + 3]) - 1;
    }
    return face{vi, ni};
}

std::vector<triangle> assemble_triangles(
    std::vector<linear::point3d> const& points,
    std::vector<linear::direction3d> const& normals,
    std::vector<face> const& faces)
{
    std::vector<triangle> result;
    for (auto const& f: faces) {
        auto const vs = map([&points](size_t i) { return points[i]; }, f.points);
        auto const ns = map([&normals](size_t i) { return normals[i]; }, f.normals);

        result.push_back(triangle{vs, ns});
    }
    return result;
}

} // namespace

std::vector<triangle> parse_obj(std::istream &is) {
    const std::string float_group = "\\s+(-?\\d+\\.\\d+)";
    const std::regex  vertex_re{"v" + float_group + float_group + float_group};
    const std::regex  normal_re{"vn" + float_group + float_group + float_group};
    const std::string index_group = "\\s+(\\d+)/(\\d+)/(\\d+)";
    const std::regex  face_re{"f" + index_group + index_group + index_group};

    std::vector<linear::point3d> points;
    std::vector<linear::direction3d> normals;
    std::vector<face> faces;

    std::string line;
    while (std::getline(is, line)) {
        std::smatch base_match;
        if (std::regex_match(line, base_match, vertex_re)) {
            points.push_back(read_point(base_match));
        } else if (std::regex_match(line, base_match, normal_re)) {
            normals.push_back(read_normal(base_match));
        } else if (std::regex_match(line, base_match, face_re)) {
            faces.push_back(read_face(base_match));
        }
    }

    return assemble_triangles(points, normals, faces);
}

} // namespace tracer
