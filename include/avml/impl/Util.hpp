#ifndef AVML_UTIL_HPP
#define AVML_UTIL_HPP

#include <type_traits>

#include "Array.hpp"
#include "Point.hpp"
#include "Shared.hpp"
#include "Unit_vector.hpp"

namespace avml {

    template<class T>
    struct is_array : public std::bool_constant<false> {};

    template<class T>
    static constexpr bool is_array_v = is_array<T>::value;

}

#endif //AVML_UTIL_HPP
