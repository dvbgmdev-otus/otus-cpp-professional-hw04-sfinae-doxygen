#ifndef IP_DETAIL_H
#define IP_DETAIL_H

#include <iostream>
#include <tuple>

namespace ip {
namespace detail {

// ============================================================
// print_tuple_impl
// Вспомогательная функция для вывода кортежа
// ============================================================
template <typename Tuple, std::size_t Index = 0>
void print_tuple_impl(const Tuple& tuple) {
    if constexpr (Index < std::tuple_size<Tuple>::value) {
        if (Index > 0) {
            std::cout << '.';
        }
        std::cout << std::get<Index>(tuple);
        print_tuple_impl<Tuple, Index + 1>(tuple);
    }
}

}  // namespace detail
}  // namespace ip

#endif  // IP_DETAIL_H
