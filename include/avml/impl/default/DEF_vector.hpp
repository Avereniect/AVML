#ifndef AVML_DEF_VECTOR_HPP
#define AVML_DEF_VECTOR_HPP

#include <cmath>

#include "DEF_uvec2f.hpp"
#include "DEF_uvec3f.hpp"
#include "DEF_uvec4f.hpp"

#include "DEF_vec2f.hpp"
#include "DEF_vec3f.hpp"
#include "DEF_vec4f.hpp"

namespace avml {

    //=========================================================================
    // Vector function specializations
    //=========================================================================

    template<
        unsigned e0,
        unsigned e1,
        class T
    >
    AVML_FINL Vector<T, 2> swizzle(Vector<T, 2> v) {
        static_assert(e0 < 2 && e1 < 2, "Indices out of bounds");

        return Vector<T, 2> {
            v[e0],
            v[e1]
        };
    }

    template<
        unsigned e0,
        unsigned e1,
        unsigned e2,
        class T
    >
    AVML_FINL Vector<T, 3> swizzle(Vector<T, 3> v) {
        static_assert(e0 < 3 && e1 < 3 && e2 < 3, "Indices out of bounds");

        return Vector<T, 3> {
            v[e0],
            v[e1],
            v[e2]
        };
    }

    template<
        unsigned e0,
        unsigned e1,
        unsigned e2,
        unsigned e3,
        class T
    >
    AVML_FINL Vector<T, 4> swizzle(Vector<T, 4> v) {
        static_assert(e0 < 4 && e1 < 4 && e2 < 4 && e3 < 4, "Indices out of bounds");

        return Vector<T, 4> {
            v[e0],
            v[e1],
            v[e2],
            v[e3]
        };
    }

}

#endif //AVML_DEF_VECTOR_HPP
