#pragma once

namespace utils {

template<typename T>
struct add_sub
{
    friend T operator+(T lhs, T const& rhs) { return lhs += rhs; }
    friend T operator-(T lhs, T const& rhs) { return lhs -= rhs; }
};

template<typename T>
struct comparable
{
    friend T operator!=(T const& lhs, T const& rhs) { return !(lhs == rhs); }
    friend T operator<=(T const& lhs, T const& rhs) { return !(lhs > rhs); }
    friend T operator> (T const& lhs, T const& rhs) { return rhs < lhs; }
    friend T operator>=(T const& lhs, T const& rhs) { return !(rhs < lhs); }
};

} // namespace utils
