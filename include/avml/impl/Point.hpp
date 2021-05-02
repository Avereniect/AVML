#ifndef AVML_POINT_HPP
#define AVML_POINT_HPP

#include "Shared.hpp"
#include "Array.hpp"
#include "Vector.hpp"

namespace avml {

    template<class T, unsigned N>
    class alignas(alignment(sizeof(T) * N)) Point {
    public:

        //=============================================
        // Assertions
        //=============================================

        static_assert((1 < N) && (N < 5));
        static_assert(std::is_floating_point_v<T> || std::is_integral_v<T>);

        //=============================================
        // -ctors
        //=============================================

        Point(T x, T y) {
            std::enable_if_t<N == 2, T> dummy{};

            elems[0] = x;
            elems[1] = y;
        }

        Point(T x, T y, T z) {
            std::enable_if_t<N == 3, T> dummy{};

            elems[0] = x;
            elems[1] = y;
            elems[2] = z;
        }

        Point(T w, T x, T y, T z) {
            std::enable_if_t<N == 4, T> dummy{};

            elems[0] = w;
            elems[1] = x;
            elems[2] = y;
            elems[3] = z;
        }

        Point() = default;
        Point(const Point&) = default;
        Point(Point&&) noexcept= default;
        ~Point() = default;

        //=================================================
        // Assignment Operators
        //=================================================

        Point& operator=(const Point&) = default;
        Point& operator=(Point&&) noexcept = default;

        //=================================================
        // Arithmetic assignment operators
        //=================================================

        Point& operator+=(const Vector<T, N>& vec) {
            for (unsigned i = 0; i < N; ++i) {
                elems[i] += vec[i];
            }

            return *this;
        };

        Point& operator-=(const Vector<T, N>& vec) {
            for (int i = 0; i < N; ++i) {
                elems[i] -= vec[i];
            }

            return *this;
        };

        //=================================================
        // Comparison operators
        //=================================================

        bool operator==(Point<T, N> rhs) const {
            for (int i = 0; i < N; ++i) {
                if (elems[i] != rhs[i]) {
                    return false;
                }
            }
            return true;
        }

        bool operator!=(Point<T, N> rhs) const {
            return !(*this == rhs);
        }

        //=================================================
        // Accessors
        //=================================================

        float& operator[](unsigned i) {
            return elems[i % N];
        }

        float operator[](unsigned i) const {
            return elems[i % N];
        }

        float* data() {
            return elems;
        }

        const float* data() const {
            return elems;
        }

        constexpr std::size_t size() const {
            return N;
        }

        //=============================================
        // Conversion operators
        //=============================================

        operator Array<T, N>() const{
            Array<T, N> ret;

            for (int i = 0; i < N; ++i) {
                ret[i] = elems[i];
            }

            return ret;
        }

        //=============================================
        // Instance members
        //=============================================

    protected:

        T elems[N];

    };

    //=====================================================
    // Arithmetic operators
    //=====================================================

    template<class T, unsigned N>
    Vector<T, N> operator-(Point<T, N> lhs, Point<T, N> rhs) {
        Vector<T, N> ret;

        for (int i = 0; i < N; ++i) {
            ret[i] = (lhs[i] - rhs[i]);
        }

        return ret;
    }

    template<class T, unsigned N>
    Point<T, N> operator+(Point<T, N> lhs, Vector<T, N> rhs) {
        return lhs += rhs;
    }

    template<class T, unsigned N>
    Point<T, N> operator+(Vector<T, N> lhs, Point<T, N> rhs) {
        return rhs += lhs;
    }

    template<class T, unsigned N>
    Point<T, N> operator-(Point<T, N> lhs, Vector<T, N> rhs) {
        return lhs -= rhs;
    }

    template<class T, unsigned N>
    Point<T, N> operator-(Vector<T, N> lhs, Point<T, N> rhs) {
        return rhs -= lhs;
    }

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

#endif //AVML_POINT_HPP
