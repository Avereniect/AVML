#ifndef AVML_DEF_POINT_HPP
#define AVML_DEF_POINT_HPP

namespace avml {

    template<>
    class Point<float, 2> {
    public:

        using scalar = float;

        static constexpr unsigned width = 2;

        //=================================================
        // Creation functions
        //=================================================

        static Point read(float* p) {
            return Point{p[0], p[1]};
        }

        static Point read_aligned(float* p) {
            return Point{p[0], p[1]};
        }

        //=================================================
        // -ctors
        //=================================================

        Point(float x, float y):
            elements{x, y} {}

        explicit Point(Vec2 v):
            elements{v[0], v[1]} {}

        Point() = default;
        Point(const Point&) = default;
        Point(Point&&) = default;
        ~Point();

        //=================================================
        // Assignment operators
        //=================================================

        Point& operator=(const Point&) = default;
        Point& operator=(Point&&) = default;

        //=================================================
        // Accessors
        //=================================================

        float& operator[](unsigned i) {
            return  elements[i];
        }

        const float& operator[](unsigned i) const {
            return elements[i];
        }

        float* data() {
            return elements;
        }

        const float* data() const {
            return elements;
        }

        //=================================================
        // Conversion operators
        //=================================================

        explicit operator Vec2() const {
            return Vec2{
                elements[0],
                elements[1]
            };
        }

    private:

        //=================================================
        // Instance members
        //=================================================

        float elements[2];

    };

    //=========================================================================
    // Point operators
    //=========================================================================

    template<class T, unsigned N>
    Point<T, N> operator+(Point<T, N> lhs, Vector<T, N> rhs) {
        for (int i = 0; i < N; ++i) {
            lhs[i] += rhs[i];
        }

        return lhs;
    }

    template<class T, unsigned N>
    Vector<T, N> operator-(Point<T, N> lhs, Point<T, N> rhs) {
        Vector<T, N> ret;

        for (int i = 0; i < N; ++i) {
            ret[i] = (lhs[i] - rhs[i]);
        }

        return ret;
    }

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
