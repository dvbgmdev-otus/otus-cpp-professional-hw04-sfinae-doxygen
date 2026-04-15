#ifndef IP_DETAIL_H
#define IP_DETAIL_H

#include <iostream>
#include <tuple>

/** @file ip_detail.h
 *  @brief Внутренние вспомогательные функции реализации проекта print_ip.
 */

namespace ip {
namespace detail {

/** @ingroup implementation_details
 *  @brief Рекурсивно выводит элементы кортежа через точку.
 *
 *  Функция используется внутренней перегрузкой `print_ip` для
 *  однородных кортежей `std::tuple`.
 *
 *  @tparam Tuple тип кортежа.
 *  @tparam Index индекс текущего элемента.
 *  @param tuple кортеж для вывода.
 */
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
