#ifndef AVML_VECTORS_HPP
#define AVML_VECTORS_HPP

#include <cstdint>

namespace avml {

    //=====================================================
    // Class declarations
    //=====================================================

    template<class R>
    class Unit_vector2;

    template<class R>
    class Unit_vector3;

    template<class R>
    class Unit_vector4;

    template<class R>
    class Vector2;

    template<class R>
    class Vector3;

    template<class R>
    class Vector4;

    //=====================================================
    // Unit vector aliases
    //=====================================================

    using uvec2f = Unit_vector2<float>;
    using uvec3f = Unit_vector3<float>;
    using uvec4f = Unit_vector4<float>;


    using uvec2d = Unit_vector2<double>;
    using uvec3d = Unit_vector3<double>;
    using uvec4d = Unit_vector4<double>;

    //=====================================================
    // Vector aliases
    //=====================================================

    using vec2f = Vector2<float>;
    using vec3f = Vector3<float>;
    using vec4f = Vector4<float>;


    using vec2d = Vector2<double>;
    using vec3d = Vector3<double>;
    using vec4d = Vector4<double>;


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


    using vec2u = Vector<std::uint32_t, 2>;
    using vec3u = Vector<std::uint32_t, 3>;
    using vec4u = Vector<std::uint32_t, 4>;

    using vec2i = Vector<std::int32_t, 2>;
    using vec3i = Vector<std::int32_t, 3>;
    using vec4i = Vector<std::int32_t, 4>;
    */

}

#include "impl/IMPL_vectors.hpp"

namespace avml {

    static const uvec2f X2f{1.0f, 0.0f};
    static const uvec2f Y2f{0.0f, 1.0f};

    static const uvec3f X3f{1.0f, 0.0f, 0.0f};
    static const uvec3f Y3f{0.0f, 1.0f, 0.0f};
    static const uvec3f Z3f{0.0f, 0.0f, 1.0f};

    static const uvec4f X4f{1.0f, 0.0f, 0.0f, 0.0f};
    static const uvec4f Y4f{0.0f, 1.0f, 0.0f, 0.0f};
    static const uvec4f Z4f{0.0f, 0.0f, 1.0f, 0.0f};
    static const uvec4f W4f{0.0f, 0.0f, 0.0f, 1.0f};

}

#endif //AVML_VECTORS_HPP
