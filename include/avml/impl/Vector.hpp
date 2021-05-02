#ifndef AVML_VECTOR_HPP
#define AVML_VECTOR_HPP

#include "Shared.hpp"
#include "Array.hpp"
#include "Unit_vector.hpp"

namespace avml {

    template<class T, unsigned N>
    class alignas(alignment(sizeof(T) * N)) Vector {
    public:

        //=============================================
        // Assertions
        //=============================================

        static_assert((1 < N) && (N < 5));
        static_assert(std::is_floating_point_v<T> || std::is_integral_v<T>);

        //=============================================
        // -ctors
        //=============================================

        Vector(Unit_vector<T, N> v) {
            for (int i = 0; i < N; ++i) {
                elems[i] = v[i];
            }
        }

        Vector(T x, T y) {
            static_assert(N == 2);
            std::enable_if_t<N == 2, T> dummy{};

            elems[0] = x;
            elems[1] = y;
        }

        Vector(T x, T y, T z) {
            static_assert(N == 3);
            std::enable_if_t<N == 3, T> dummy{};

            elems[0] = x;
            elems[1] = y;
            elems[2] = z;
        }

        Vector(T w, T x, T y, T z) {
            static_assert(N == 4);
            std::enable_if_t<N == 4, T> dummy{};

            elems[0] = w;
            elems[1] = x;
            elems[2] = y;
            elems[3] = z;
        }

        Vector() = default;
        Vector(const Vector&) = default;
        Vector(Vector&&) noexcept= default;
        ~Vector() = default;

        //=============================================
        // Assignment Operators
        //=============================================

        Vector& operator=(const Vector&) = default;
        Vector& operator=(Vector&&) noexcept = default;

        //=============================================
        // Arithmetic Assignment
        //=============================================

        Vector& operator+=(Vector rhs) {
            for (int i = 0; i < N; ++i) {
                elems[i] += rhs[i];
            }

            return *this;
        }

        Vector& operator-=(Vector rhs) {
            for (int i = 0; i < N; ++i) {
                elems[i] -= rhs[i];
            }

            return *this;
        }

        Vector& operator*=(T rhs) {
            for (int i = 0; i < N; ++i) {
                elems[i] *= rhs;
            }

            return *this;
        }

        Vector& operator/=(T rhs) {
            for (int i = 0; i < N; ++i) {
                elems[i] /= rhs;
            }

            return *this;
        }

        //=============================================
        // Vector math
        //=============================================

        T length2() const {
            std::enable_if_t<std::is_floating_point_v<T>, T> dummy{};

            T ret = 0.0f;

            for (int i = 0; i < N; ++i) {
                ret[i] += elems[i] * elems[i];
            }

            return ret;
        }

        T length() const {
            std::enable_if_t<std::is_floating_point_v<T>, T> dummy{};

            return std::sqrt(length2());
        }

        Unit_vector<T, N> normalize() const {
            std::enable_if_t<std::is_floating_point_v<T>, T> dummy{};

            Vector temp = *this;
            temp /= length();

            Unit_vector<T, N> ret;
            for (int i = 0; i < N; ++i) {
                ret[i] = temp[i];
            }

            return ret;
        }

        //=================================================
        // Comparison operators
        //=================================================

        bool operator==(Vector rhs) const {
            for (int i = 0; i < N; ++i) {
                if (elems[i] != rhs[i]) {
                    return false;
                }
            }
            return true;
        }

        bool operator!=(Vector rhs) const {
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

        //=================================================
        // Conversion operators
        //=================================================

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
    Vector<T, N> operator+(Vector<T, N> lhs, Vector<T, N> rhs) {
        return (lhs += rhs);
    }

    template<class T, unsigned N>
    Vector<T, N> operator-(Vector<T, N> lhs, Vector<T, N> rhs) {
        return (lhs -= rhs);
    }

    template<class T, unsigned N, class U,
        class = typename std::enable_if_t<std::is_convertible_v<U, T>>>
    Vector<T, N> operator*(Vector<T, N> lhs, U rhs) {
        return (lhs *= rhs);
    }

    template<class T, unsigned N, class U,
        class = typename std::enable_if_t<std::is_convertible_v<U, T>>>
    Vector<T, N> operator*(U lhs, Vector<T, N> rhs) {
        return (rhs *= lhs);
    }

    template<class T, unsigned N, class U,
        class = typename std::enable_if_t<std::is_convertible_v<U, T>>>
    Vector<T, N> operator/(Vector<T, N> lhs, U rhs) {
        return (lhs /= rhs);
    }

    //=====================================================
    // Vector math
    //=====================================================

    template<class T, unsigned N>
    T dot(Vector<T, N> a, Vector<T, N> b) {
        T ret = 0;

        for (unsigned i = 0; i < N; ++i) {
            ret += (a[i] * b[i]);
        }

        return ret;
    }

    template<class T>
    Vector<T, 3> cross(Vector<T, 3> a, Vector<T, 3> b) {
        Vector<T, 3> ret{};

        ret[0] = a[1] * b[2] - a[2] * b[1];
        ret[1] = a[2] * b[0] + a[0] * b[2];
        ret[2] = a[0] * b[1] + a[1] * b[0];

        return ret;
    }

    //=====================================================
    // Aliases
    //=====================================================

    using Vec2 = Vector<float, 2>;
    using Vec3 = Vector<float, 3>;
    using Vec4 = Vector<float, 4>;

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

#endif //AVML_VECTOR_HPP
