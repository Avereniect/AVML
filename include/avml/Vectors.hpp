#ifndef AVML_VECTORS_HPP
#define AVML_VECTORS_HPP

#include <cstdint>

#include "impl/Capabilities.hpp"

namespace avml {

    //=====================================================
    // Class declarations
    //=====================================================

    template<class R>
    class Unit_vector2R;

    template<class R>
    class Unit_vector3R;

    template<class R>
    class Unit_vector4R;

    template<class R>
    class Vector2R;

    template<class R>
    class Vector3R;

    template<class R>
    class Vector4R;

    template<class I>
    class Vector2I;

    template<class I>
    class Vector3I;

    template<class I>
    class Vector4I;

    //=====================================================
    // Unit vector aliases
    //=====================================================

    using uvec2f = Unit_vector2R<float>;
    using uvec3f = Unit_vector3R<float>;
    using uvec4f = Unit_vector4R<float>;

    using uvec2d = Unit_vector2R<double>;
    using uvec3d = Unit_vector3R<double>;
    using uvec4d = Unit_vector4R<double>;

    //=====================================================
    // Vector aliases
    //=====================================================

    using vec2f = Vector2R<float>;
    using vec3f = Vector3R<float>;
    using vec4f = Vector4R<float>;

    using vec2d = Vector2R<double>;
    using vec3d = Vector3R<double>;
    using vec4d = Vector4R<double>;

    using vec2i = Vector2I<std::int32_t>;
    using vec3i = Vector3I<std::int32_t>;
    using vec4i = Vector4I<std::int32_t>;

    using vec2u = Vector2I<std::uint32_t>;
    using vec3u = Vector3I<std::uint32_t>;
    using vec4u = Vector4I<std::uint32_t>;


    /*
    using vec2u8 = Vector2I<std::uint8_t>;
    using vec3u8 = Vector3I<std::uint8_t>;
    using vec4u8 = Vector4I<std::uint8_t>;

    using vec2i8 = Vector2I<std::int8_t>;
    using vec3i8 = Vector3I<std::int8_t>;
    using vec4i8 = Vector4I<std::int8_t>;

    using vec2u16 = Vector2I<std::uint16_t>;
    using vec3u16 = Vector3I<std::uint16_t>;
    using vec4u16 = Vector4I<std::uint16_t>;

    using vec2i16 = Vector2I<std::int16_t>;
    using vec3i16 = Vector3I<std::int16_t>;
    using vec4i16 = Vector4I<std::int16_t>;

    using vec2u32 = Vector2I<std::uint16_t>;
    using vec3u32 = Vector3I<std::uint16_t>;
    using vec4u32 = Vector4I<std::uint16_t>;

    using vec2i32 = Vector2I<std::int32_t>;
    using vec3i32 = Vector3I<std::int32_t>;
    using vec4i32 = Vector4I<std::int32_t>;
    */

}

#include "impl/Vectors.hpp"

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
