#pragma once

#include <type_traits>

template <class From, class To>
struct is_convertible_no_narrowing_impl {
  template <class F, class T, class Enable = decltype(std::declval<T&>() = {std::declval<F>()})>
  static auto test(F f, T t) -> std::true_type;
  static auto test(...) -> std::false_type;

  static constexpr bool value = decltype(test(std::declval<From>(), std::declval<To>()))::value;
};

template <class From, class To>
struct is_convertible_no_narrowing
        : std::integral_constant<bool, is_convertible_no_narrowing_impl<From, To>::value> {};
