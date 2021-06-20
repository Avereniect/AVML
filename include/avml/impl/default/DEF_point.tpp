#ifndef AVML_DEF_POINT_HPP
#define AVML_DEF_POINT_HPP

#include "DEF_vector.hpp"

#include "DEF_pt2f.hpp"
#include "DEF_pt3f.hpp"
#include "DEF_pt4f.hpp"

namespace avml {

    //=========================================================================
    // Point functions
    //=========================================================================

    template<
        unsigned e0,
        unsigned e1,
        class T
    >
    AVML_FINL Point<T, 2> swizzle(Point<T, 2> v) {
        static_assert(e0 < 2 && e1 < 2);

        return Point<T, 2> {
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
    AVML_FINL Point<T, 3> swizzle(Point<T, 3> v) {
        static_assert(e0 < 3 && e1 < 3 && e2 < 3);

        return Point<T, 3> {
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
    AVML_FINL Point<T, 4> swizzle(Point<T, 4> v) {
        static_assert(e0 < 4 && e1 < 4 && e2 < 4 && e3 < 4);

        return Point<T, 4> {
            v[e0],
            v[e1],
            v[e2],
            v[e3],
        };
    }

    template<class T>
    Point<T, 2> rotate(Point<T, 2> p, T angle, Point<T, 2> o) {
        return o + rotate(p - o, angle);
    }

    template<class T>
    Point<T, 3> rotate(Point<T, 3> p, T angle, Point<T, 3> o, Unit_vector<T, 3> axis) {
        return o + rotate(p - o, angle, o, axis);
    }

    template<class T, unsigned N>
    T distance(Point<T, N> p0, Point<T, N> p1) {
        return (p0 - p1).length();
    }

    template<class T>
    Point<T, 3> shear(Point<T, 3> p, Vector<T, 3> d, Unit_vector<T, 3> dir) {
        auto v = static_cast<Vector<T, 3>>(p);
        return p + dot(v, dir) * d;
    }

}

#endif //AVML_DEF_POINT_HPP
