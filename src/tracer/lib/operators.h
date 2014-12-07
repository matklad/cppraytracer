#pragma once

template<typename T>
struct add_sub
{
    friend T operator+(T lhs, T const& rhs) { return lhs += rhs; }
    friend T operator-(T lhs, T const& rhs) { return lhs -= rhs; }
};
