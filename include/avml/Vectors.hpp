#ifndef AVML_VECTORS_HPP
#define AVML_VECTORS_HPP

namespace avml {

    //=====================================================
    // Class declarations
    //=====================================================

    template<class R, unsigned N>
    class Unit_vector;

    template<class R, unsigned N>
    class Vector;

    //=====================================================
    // Unit vector aliases
    //=====================================================

    using uvec2f = Unit_vector<float, 2>;
    using uvec3f = Unit_vector<float, 3>;
    using uvec4f = Unit_vector<float, 4>;


    using uvec2d = Unit_vector<double, 2>;
    using uvec3d = Unit_vector<double, 3>;
    using uvec4d = Unit_vector<double, 4>;

    //=====================================================
    // Vector aliases
    //=====================================================

    using vec2f = Vector<float, 2>;
    using vec3f = Vector<float, 3>;
    using vec4f = Vector<float, 4>;


    using vec2d = Vector<double, 2>;
    using vec3d = Vector<double, 3>;
    using vec4d = Vector<double, 4>;


    /*
    using vec2u8 = Vector<std::uint8_t, 2>;
    using vec3u8 = Vector<std::uint8_t, 3>;
    using vec4u8 = Vector<std::uint8_t, 4>;

    using vec2i8 = Vector<std::int8_t, 2>;
    using vec3i8 = Vector<std::int8_t, 3>;
    using vec4i8 = Vector<std::int8_t, 4>;


    using vec2u16 = Vector<std::uint16_t, 2>;
    using vec3u16 = Vector<std::uint16_t, 3>;
    using vec4u16 = Vector<std::uint16_t, 4>;

    using vec2i16 = Vector<std::int16_t, 2>;
    using vec3i16 = Vector<std::int16_t, 3>;
    using vec4i16 = Vector<std::int16_t, 4>;


    using vec2u32 = Vector<std::uint32_t, 2>;
    using vec3u32 = Vector<std::uint32_t, 3>;
    using vec4u32 = Vector<std::uint32_t, 4>;

    using vec2i32 = Vector<std::int32_t, 2>;
    using vec3i32 = Vector<std::int32_t, 3>;
    using vec4i32 = Vector<std::int32_t, 4>;
    */

}

#include "impl/IMPL_vectors.hpp"

#endif //AVML_VECTORS_HPP
