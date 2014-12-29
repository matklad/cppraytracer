#pragma once

namespace linear {

struct solution
{
    bool has_root;
    double smallest_root;
    double biggest_root;
    explicit operator bool() const;
};

bool is_nearly_zero(double a);

solution solve_quadratic_equation(double a, double b, double c);

double solve_linear_equation(double a, double b);

} // namespace linear
