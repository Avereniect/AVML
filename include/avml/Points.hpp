#ifndef AVML_POINTS_HPP
#define AVML_POINTS_HPP

#include "impl/Capabilities.hpp"
#include "Vectors.hpp"

#include <cstdint>

namespace avml {

    ///
    /// \tparam T A floating-point or integral type
    /// \tparam N Number of components: [2, 4]
    template<class T, unsigned N>
    class Point;

    //=====================================================
    // Aliases
    //=====================================================

    using pt2f = Point<float, 2>;
    using pt3f = Point<float, 3>;
    using pt4f = Point<float, 4>;

    using pt2d = Point<double, 2>;
    using pt3d = Point<double, 3>;
    using pt4d = Point<double, 4>;

    using pt2i = Point<std::int32_t, 2>;
    using pt3i = Point<std::int32_t, 3>;
    using pt4i = Point<std::int32_t, 4>;

    using pt2u = Point<std::uint32_t, 2>;
    using pt3u = Point<std::uint32_t, 3>;
    using pt4u = Point<std::uint32_t, 4>;

}

#include "impl/IMPL_points.hpp"

#endif //AVML_POINTS_HPP
