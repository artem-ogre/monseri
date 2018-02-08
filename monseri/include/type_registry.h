#pragma once

#include <type_traits>

namespace monseri
{
namespace registry
{

namespace detail
{

/// Holds registered type names using partial template specialization
template <typename T>
struct Registered_type_info
{};

// Checking if type is registered
template <typename...>
using Void = void;

template <typename U, typename = void>
struct Is_registered : public std::false_type
{};

template <typename U>
struct Is_registered<U, Void<decltype(Registered_type_info<U>::name)> >
    : public std::true_type
{};

} // namespace detail

template <typename T>
constexpr const char* type_name()
{
    static_assert(
        detail::Is_registered<T>::value,
        "Serializable type is not registered: see REGISTER_TYPE macro");
    return detail::Registered_type_info<T>::name;
}

} // namespace registry
} // namespace monseri
