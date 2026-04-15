#ifndef IP_TRAITS_H
#define IP_TRAITS_H

#include <list>
#include <string>
#include <type_traits>
#include <vector>

namespace ip {
namespace traits {

// ============================================================
// is_integral
// ============================================================
template <typename T>
struct is_integral : std::is_integral<T> {};

// ============================================================
// is_string
// ============================================================
template <typename T>
struct is_string : std::false_type {};

template <>
struct is_string<std::string> : std::true_type {};

// ============================================================
// is_vector
// ============================================================
template <typename T>
struct is_vector : std::false_type {};

template <typename T, typename Allocator>
struct is_vector<std::vector<T, Allocator>> : std::true_type {};

// ============================================================
// is_list
// ============================================================
template <typename T>
struct is_list : std::false_type {};

template <typename T, typename Allocator>
struct is_list<std::list<T, Allocator>> : std::true_type {};

// ============================================================
// is_supported_container
// Поддерживаются только std::vector и std::list
// ============================================================
template <typename T>
struct is_supported_container
    : std::integral_constant<bool, is_vector<T>::value || is_list<T>::value> {};

}  // namespace traits
}  // namespace ip

#endif  // IP_TRAITS_H
