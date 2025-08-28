//
// Created by Максим Процик on 15.08.2023.
//

#ifndef GAMETEST_TEMPLATES_H
#define GAMETEST_TEMPLATES_H

#include <type_traits>
#include <tuple>

template <typename T, T... S, typename F>
constexpr void for_sequence(std::integer_sequence<T, S...>, F&& f) {
    (static_cast<void>(f(std::integral_constant<T, S>{})), ...);
}

template<typename T> struct is_vector : public std::false_type {};

template<typename T, typename A>
struct is_vector<std::vector<T, A>> : public std::true_type {};

template<typename T> struct is_unordered_map : public std::false_type {};

template<typename T, typename A, typename B, typename C, typename D>
struct is_unordered_map<std::unordered_map<T, A, B, C, D>> : public std::true_type {};

#endif //GAMETEST_TEMPLATES_H
