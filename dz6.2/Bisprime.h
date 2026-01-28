#ifndef CT_PRIME_H
#define CT_PRIME_H
#include <type_traits>
#include <iostream>

template <int64_t N, int64_t L, int64_t R, bool NeedToCount>
    struct Sqrt : std::integral_constant < int64_t,
    Sqrt<N, L, (L + R) / 2,
         N<((L + R) / 2) * ((L + R) / 2)>::value + Sqrt<N, (L + R) / 2, R, N >= ((L + R) / 2) * ((L + R) / 2)>::value> {
};

template <int64_t N, int64_t L, int64_t R>
struct Sqrt<N, L, R, false> : std::integral_constant<int64_t, 0> {};

template <int64_t N, int64_t L>
struct Sqrt<N, L, L, true> : std::integral_constant<int64_t, L> {};

template <int64_t N, int64_t L>
struct Sqrt<N, L, L + 1, true> : std::integral_constant<int64_t, L> {};

template <int64_t N>
inline const int64_t kSqrtV = Sqrt<N, 0, 1000000000, true>::value;

template <int64_t N, int64_t L, int64_t R>
struct HasDivisorOn;

template <int64_t N, int64_t L, int64_t R>
struct HasDivisorOn : std::integral_constant<bool, HasDivisorOn<N, L, (L + R) / 2>::value ||
                                                       HasDivisorOn<N, (L + R + 1) / 2, R>::value> {};

template <int64_t N, int64_t L>
struct HasDivisorOn<N, L, L> : std::integral_constant<bool, N % L == 0> {};

template <int64_t N, int64_t L>
struct HasDivisorOn<N, L, L + 1> : std::integral_constant<bool, (N % L == 0) || (N % (L + 1) == 0)> {};

template <int64_t N, int64_t L, int64_t R>
inline const bool kHasDivisorOnV = HasDivisorOn<N, L, R>::value;

template <int64_t N>
struct IsPrime : std::integral_constant<bool, !kHasDivisorOnV<N, 2, kSqrtV<N> + 1>> {};

template <>
struct IsPrime<0> : std::integral_constant<bool, false> {};

template <>
struct IsPrime<1> : std::integral_constant<bool, false> {};

template <>
struct IsPrime<2> : std::integral_constant<bool, true> {};

template <int64_t N>
inline const bool kIsPrimeV = IsPrime<N>::value;
#endif