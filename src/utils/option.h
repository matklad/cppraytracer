#pragma once

namespace utils {

template<typename T>
struct option;

struct none_t {};

template<typename T>
option<T> some(T const& value);

none_t const none{};

template<typename T>
struct option {
    friend option some<>(T const& value);

    option(none_t): empty_(true) {}
    option(option const& other) { copy_value(other); }

    option& operator=(option const& other) {
        destroy_value();
        copy_value(other);
        return *this;
    }

    option& operator=(T const& value) {
        destroy_value();
        empty_ = false;
        make_value(value);
        return *this;
    }

    ~option() { destroy_value(); }

    bool is_empty() const { return empty_; };
    explicit operator bool() const { return !is_empty(); };
    T value() const { return get_value(); };

private:
    option(T value): empty_(false) { new (data_) T(value); }

    T const& get_value() const { return *reinterpret_cast<T const*>(data_); }
    void destroy_value() { if (!empty_) { get_value().~T(); } }
    void copy_value(option const& other) {
        empty_ = other.empty_;
        if (!other.empty_) { make_value(other.value()); }
    }

    void make_value(T const& value) { new (data_) T(value); }

    bool empty_;
    char data_[sizeof(T)];
};

template<typename T>
option<T> some(T const& value) { return option<T>(value); };

} // namespace utils
