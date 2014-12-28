#pragma once

namespace utils {

template<typename T>
struct option;

struct none_t {};
none_t const none {};

template<typename T>
option<T> some(T const& value);

template<typename T>
struct option {
    friend option some<>(T const& value);

    option(none_t);
    option(option const& other);
    ~option();

    option& operator=(option const& other);
    option& operator=(T const& value);

    bool is_empty() const;
    explicit operator bool() const;
    T value() const;

private:
    option(T value);
    T const& get_value() const;
    void destroy_value();
    void copy_from(option const& other);
    void make_value(T const& value);

    bool empty_;
    char data_[sizeof(T)];
};

template<typename T>
option<T>::option(none_t)
    : empty_(true)
{}

template<typename T>
option<T>::option(option const& other)
{ copy_from(other); }

template<typename T>
option<T>::option(T value)
    : empty_(false)
{ new (data_) T(value); }


template<typename T>
option<T>::~option() { destroy_value(); }

template<typename T>
auto option<T>::operator=(option const& other) -> option& {
    destroy_value();
    copy_from(other);
    return *this;
}

template<typename T>
auto option<T>::operator=(T const& value) -> option& {
    destroy_value();
    empty_ = false;
    make_value(value);
    return *this;
}

template<typename T>
bool option<T>::is_empty() const { return empty_; };

template<typename T>
option<T>::operator bool() const { return !is_empty(); }

template<typename T>
auto option<T>::value() const -> T { return get_value(); };

template<typename T>
auto option<T>::get_value() const -> T const&
{ return *reinterpret_cast<T const*>(data_); }

template<typename T>
void option<T>::destroy_value() { if (!empty_) { get_value().~T(); } }

template<typename T>
void option<T>::copy_from(option const& other) {
    empty_ = other.empty_;
    if (!other.empty_) { make_value(other.value()); }
}

template<typename T>
void option<T>::make_value(T const& value) { new (data_) T(value); }

template<typename T>
option<T> some(T const& value) { return option<T>(value); };

} // namespace utils
