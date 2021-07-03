#ifndef AVML_VECTORS_HPP
#define AVML_VECTORS_HPP

#include "impl/Capabilities.hpp"

#include <cstdint>

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

    using Uvec2f = Unit_vector<float, 2>;
    using Uvec3f = Unit_vector<float, 3>;
    using Uvec4f = Unit_vector<float, 4>;

    using Uvec2d = Unit_vector<double, 2>;
    using Uvec3d = Unit_vector<double, 3>;
    using Uvec4d = Unit_vector<double, 4>;

    //=====================================================
    // Vector aliases
    //=====================================================

    using Vec2f = Vector<float, 2>;
    using Vec3f = Vector<float, 3>;
    using Vec4f = Vector<float, 4>;

    using Vec2d = Vector<double, 2>;
    using Vec3d = Vector<double, 3>;
    using Vec4d = Vector<double, 4>;

}

#include "impl/IMPL_vectors.hpp"

#endif //AVML_VECTORS_HPP
