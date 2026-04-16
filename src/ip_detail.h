#ifndef IP_DETAIL_H
#define IP_DETAIL_H

#include <cstddef>
#include <iostream>
#include <tuple>

/** @file ip_detail.h
 *  @brief Внутренние вспомогательные функции реализации проекта print_ip.
 */

namespace ip {
namespace detail {

/** @ingroup implementation_details
 *  @brief Рекурсивный вывод элементов кортежа через точку.
 *
 *  @tparam Tuple тип кортежа.
 *  @tparam Index текущий индекс.
 *  @tparam Size размер кортежа.
 */
template <typename Tuple, std::size_t Index, std::size_t Size>
struct tuple_printer {
    static void print(const Tuple& tuple) {
        if (Index > 0) {
            std::cout << '.';
        }

        std::cout << std::get<Index>(tuple);
        tuple_printer<Tuple, Index + 1, Size>::print(tuple);
    }
};

/** @ingroup implementation_details
 *  @brief Базовый случай рекурсии вывода кортежа.
 *
 *  Специализация завершает рекурсивный вывод, когда Index == Size.
 *
 *  @tparam Tuple тип кортежа.
 *  @tparam Size размер кортежа.
 */
template <typename Tuple, std::size_t Size>
struct tuple_printer<Tuple, Size, Size> {
    static void print(const Tuple&) {}
};

/** @ingroup implementation_details
 *  @brief Запускает вывод однородного кортежа через точку.
 *
 *  @tparam Tuple тип кортежа.
 *  @param tuple кортеж для вывода.
 */
template <typename Tuple>
void print_tuple_impl(const Tuple& tuple) {
    tuple_printer<Tuple, 0, std::tuple_size<Tuple>::value>::print(tuple);
}

}  // namespace detail
}  // namespace ip

#endif  // IP_DETAIL_H
