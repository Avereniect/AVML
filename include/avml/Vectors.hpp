#ifndef AVML_VECTORS_HPP
#define AVML_VECTORS_HPP

#include "impl/Capabilities.hpp"

#include <cstdint>

namespace avml {

    //=====================================================
    // Class declarations
    //=====================================================

    template<class T, unsigned N>
    class Unit_vector;

    template<class T, unsigned N>
    class Vector;

    //=====================================================
    // Unit vector aliases
    //=====================================================

    using Uvec2f = Unit_vector<float, 2>;
    using Uvec3f = Unit_vector<float, 3>;
    using Uvec4f = Unit_vector<float, 4>;

    using Uvec2d = Unit_vector<double, 2>;
    using Uvec3d = Unit_vector<double, 3>;
    using Uvec4d = Unit_vector<double, 4>;

    using Uvec2i = Unit_vector<std::int32_t, 2>;
    using Uvec3i = Unit_vector<std::int32_t, 3>;
    using Uvec4i = Unit_vector<std::int32_t, 4>;

    using Uvec2u = Unit_vector<std::uint32_t, 2>;
    using Uvec3u = Unit_vector<std::uint32_t, 3>;
    using Uvec4u = Unit_vector<std::uint32_t, 4>;

    //=====================================================
    // Vector aliases
    //=====================================================

    using Vec2f = Vector<float, 2>;
    using Vec3f = Vector<float, 3>;
    using Vec4f = Vector<float, 4>;

    using Vec2d = Vector<double, 2>;
    using Vec3d = Vector<double, 3>;
    using Vec4d = Vector<double, 4>;

    using Vec2i = Vector<std::int32_t, 2>;
    using Vec3i = Vector<std::int32_t, 3>;
    using Vec4i = Vector<std::int32_t, 4>;

    using Vec2u = Vector<std::uint32_t, 2>;
    using Vec3u = Vector<std::uint32_t, 3>;
    using Vec4u = Vector<std::uint32_t, 4>;

}

#include "impl/default/DEF_vector.hpp"

#endif //AVML_VECTORS_HPP
