#ifndef IP_TRAITS_H
#define IP_TRAITS_H

#include <list>
#include <string>
#include <tuple>
#include <type_traits>
#include <vector>

/** @file ip_traits.h
 *  @brief Вспомогательные type traits для SFINAE в проекте print_ip.
 */

namespace ip {
namespace traits {

/** @ingroup type_traits
 *  @brief Проверяет, является ли тип целочисленным.
 *
 *  Используется для включения перегрузки `print_ip` для целочисленных типов.
 *
 *  @tparam T проверяемый тип.
 */
template <typename T>
struct is_integral : std::is_integral<T> {};

/** @ingroup type_traits
 *  @brief Проверяет, является ли тип строкой `std::string`.
 *
 *  @tparam T проверяемый тип.
 */
template <typename T>
struct is_string : std::false_type {};

/** @ingroup type_traits
 *  @brief Специализация для типа `std::string`.
 */
template <>
struct is_string<std::string> : std::true_type {};

/** @ingroup type_traits
 *  @brief Проверяет, является ли тип контейнером `std::vector`.
 *
 *  @tparam T проверяемый тип.
 */
template <typename T>
struct is_vector : std::false_type {};

/** @ingroup type_traits
 *  @brief Специализация для контейнера `std::vector`.
 *
 *  @tparam T тип элемента.
 *  @tparam Allocator тип аллокатора.
 */
template <typename T, typename Allocator>
struct is_vector<std::vector<T, Allocator>> : std::true_type {};

/** @ingroup type_traits
 *  @brief Проверяет, является ли тип контейнером `std::list`.
 *
 *  @tparam T проверяемый тип.
 */
template <typename T>
struct is_list : std::false_type {};

/** @ingroup type_traits
 *  @brief Специализация для контейнера `std::list`.
 *
 *  @tparam T тип элемента.
 *  @tparam Allocator тип аллокатора.
 */
template <typename T, typename Allocator>
struct is_list<std::list<T, Allocator>> : std::true_type {};

/** @ingroup type_traits
 *  @brief Проверяет, поддерживается ли контейнер перегрузкой `print_ip`.
 *
 *  Поддерживаются только `std::vector` и `std::list`.
 *
 *  @tparam T проверяемый тип.
 */
template <typename T>
struct is_supported_container
    : std::integral_constant<bool, is_vector<T>::value || is_list<T>::value> {};

/** @ingroup type_traits
 *  @brief Проверяет, что все типы в наборе параметров одинаковы.
 *
 *  @tparam Args набор проверяемых типов.
 */
template <typename... Args>
struct are_all_same : std::true_type {};

/** @ingroup type_traits
 *  @brief Рекурсивная специализация для случая одинаковых типов.
 *
 *  @tparam T базовый тип для сравнения.
 *  @tparam Args остальные типы.
 */
template <typename T, typename... Args>
struct are_all_same<T, T, Args...> : are_all_same<T, Args...> {};

/** @ingroup type_traits
 *  @brief Специализация для случая различающихся типов.
 *
 *  @tparam T первый тип.
 *  @tparam U второй тип.
 *  @tparam Args остальные типы.
 */
template <typename T, typename U, typename... Args>
struct are_all_same<T, U, Args...> : std::false_type {};

/** @ingroup type_traits
 *  @brief Проверяет, является ли кортеж однородным.
 *
 *  Однородным считается `std::tuple`, все элементы которого имеют один и тот же тип.
 *
 *  @tparam T проверяемый тип.
 */
template <typename T>
struct is_homogeneous_tuple : std::false_type {};

/** @ingroup type_traits
 *  @brief Специализация для `std::tuple`.
 *
 *  @tparam Args типы элементов кортежа.
 */
template <typename... Args>
struct is_homogeneous_tuple<std::tuple<Args...>> : are_all_same<Args...> {};

}  // namespace traits
}  // namespace ip

#endif  // IP_TRAITS_H
