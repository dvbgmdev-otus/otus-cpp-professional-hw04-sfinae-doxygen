#ifndef PRINT_IP_H
#define PRINT_IP_H

#include <cstddef>
#include <iostream>
#include <type_traits>

#include "ip_traits.h"

namespace ip {

// ============================================================
// print_ip for integral types
// Вывод: беззнаково, побайтово, от старшего байта к младшему
// ============================================================
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

// ============================================================
// print_ip for std::string
// Вывод: строка как есть
// ============================================================
template <typename T, typename std::enable_if<traits::is_string<T>::value, int>::type = 0>
void print_ip(const T& value) {
    std::cout << value << std::endl;
}

// ============================================================
// print_ip for supported containers (std::vector и std::list)
// Вывод: элементы контейнера, разделенные точкой
// ============================================================
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

}  // namespace ip

#endif  // PRINT_IP_H
