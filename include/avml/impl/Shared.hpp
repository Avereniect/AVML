#ifndef AVML_IMPL_SHARED_HPP
#define AVML_IMPL_SHARED_HPP

#include "Capabilities.hpp"

#include <type_traits>

namespace avml_impl {

    template<class T, class U>
    T reinterpret_bits(const U& u) {
        static_assert(sizeof(T) == sizeof(U), "Types should be of same size.");
        static_assert(std::is_trivial<T>::value, "T should be trivial");
        static_assert(std::is_trivial<U>::value, "U should be trivial");

        T ret;

        char* src = reinterpret_cast<char*>(&u);
        char* dest = reinterpret_cast<char*>(&ret);

        for (int i = 0; i < sizeof(U); ++i) {
            dest[i] = src[i];
        }

        return ret;
    }

    template<class T>
    [[nodiscard]]
    constexpr inline bool is_pow2(const T v) {
        return v && !(v & (v - 1));
    }

    template<class T, unsigned N>
    [[nodiscard]]
    constexpr std::size_t vector_alignment() {
        return is_pow2(N) ? alignof(T) * N : alignof(T);
    }

}

#endif
