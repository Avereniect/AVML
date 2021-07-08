#ifndef AVML_IMPL_SHARED_HPP
#define AVML_IMPL_SHARED_HPP

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

}

#endif //AVML_IMPL_SHARED_HPP
