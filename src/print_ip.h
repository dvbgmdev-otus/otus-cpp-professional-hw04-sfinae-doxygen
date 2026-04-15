#ifndef PRINT_IP_H
#define PRINT_IP_H

#include <cstddef>
#include <iostream>
#include <type_traits>

#include "ip_detail.h"
#include "ip_traits.h"

/** @file print_ip.h
 *  @brief Шаблонные перегрузки функции print_ip для различных представлений условного IP-адреса.
 */

namespace ip {

/** @ingroup public_api
 *  @brief Выводит условный IP-адрес, представленный целочисленным типом.
 *
 *  Значение выводится побайтово в беззнаковом виде, начиная со старшего байта.
 *  Все байты разделяются символом точки (`.`).
 *
 *  @tparam T тип параметра.
 *  @param value значение для вывода.
 */
template <typename T, typename std::enable_if<traits::is_integral<T>::value, int>::type = 0>
void print_ip(const T& value) {
    using unsigned_type = typename std::make_unsigned<T>::type;

    const unsigned_type raw = static_cast<unsigned_type>(value);
    const std::size_t byte_count = sizeof(T);

    for (std::size_t i = 0; i < byte_count; ++i) {
        const std::size_t shift = (byte_count - 1 - i) * 8;
        const unsigned_type byte = (raw >> shift) & static_cast<unsigned_type>(0xFF);

        if (i != 0) {
            std::cout << '.';
        }

        std::cout << static_cast<unsigned int>(byte);
    }

    std::cout << std::endl;
}

/** @ingroup public_api
 *  @brief Выводит условный IP-адрес, представленный строкой.
 *
 *  Строковое значение выводится без изменений.
 */
template <typename T, typename std::enable_if<traits::is_string<T>::value, int>::type = 0>
void print_ip(const T& value) {
    std::cout << value << std::endl;
}

/** @ingroup public_api
 *  @brief Выводит условный IP-адрес, представленный поддерживаемым контейнером.
 *
 *  Поддерживаются контейнеры `std::vector` и `std::list`.
 *  Элементы контейнера выводятся по порядку и разделяются символом точки (`.`).
 */
template <typename T,
          typename std::enable_if<traits::is_supported_container<T>::value, int>::type = 0>
void print_ip(const T& value) {
    auto it = value.begin();
    const auto end = value.end();

    if (it != end) {
        std::cout << *it;
        ++it;
    }

    for (; it != end; ++it) {
        std::cout << '.' << *it;
    }

    std::cout << std::endl;
}

/** @ingroup public_api
 *  @brief Выводит условный IP-адрес, представленный однородным кортежем.
 *
 *  Элементы кортежа выводятся по порядку и разделяются символом точки (`.`).
 *  Перегрузка доступна только для `std::tuple`, все элементы которого имеют
 *  одинаковый тип.
 */
template <typename T,
          typename std::enable_if<traits::is_homogeneous_tuple<T>::value, int>::type = 0>
void print_ip(const T& value) {
    detail::print_tuple_impl(value);
    std::cout << std::endl;
}

}  // namespace ip

#endif  // PRINT_IP_H
