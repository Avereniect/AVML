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

    using Pt2 = Point<float, 2>;
    using Pt3 = Point<float, 3>;
    using Pt4 = Point<float, 4>;

    using Pt2d = Point<double, 2>;
    using Pt3d = Point<double, 3>;
    using Pt4d = Point<double, 4>;

    using Pt2i = Point<std::int32_t, 2>;
    using Pt3i = Point<std::int32_t, 3>;
    using Pt4i = Point<std::int32_t, 4>;

    using Pt2u = Point<std::uint32_t, 2>;
    using Pt3u = Point<std::uint32_t, 3>;
    using Pt4u = Point<std::uint32_t, 4>;

}

#include "impl/default/DEF_point.tpp"

#endif //AVML_POINTS_HPP
