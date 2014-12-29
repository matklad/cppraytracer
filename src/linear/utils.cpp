#include <algorithm>
#include <cassert>

#include <linear/utils.h>

namespace linear {

solution::operator bool() const { return has_root; }

bool is_nearly_zero(double const x) { return std::abs(x) < 1e-6; }

solution solve_quadratic_equation(double a, double b, double c) {
    assert (!is_nearly_zero(a));
    auto const d = b*b - 4*a*c;
    if (d < 0) { return solution{false, 0, 0}; };
    auto const d_root = std::sqrt(d);
    auto const t1 = (b - d_root) / (2 * a);
    auto const t2 = (b + d_root) / (2 * a);
    return {true, std::min(t1, t2), std::max(t1, t2)};
}

double solve_linear_equation(double a, double b)
{ return -b / a; }

} // namespace linear
