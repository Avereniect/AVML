#ifndef AVML_SSE_VECTOR_HPP
#define AVML_SSE_VECTOR_HPP

#include "../Capabilities.hpp"
#include "avml/Vectors.hpp"
#include "SSE_unit_vector.hpp"
#include "../../AVML.hpp"

namespace avml {

    template<>
    class alignas(4) Vector<float, 4> {
    public:

        //=================================================
        // Type aliases
        //=================================================

        using scalar = float;

        constexpr unsigned components = 4;

        //=================================================
        // -ctors
        //=================================================

        Vector(float x, float y, float z, float w):
            elems({x, y, z, w}) {}

        Vector() = default;
        Vector(const Vector&) = default;
        Vector(Vector&&) = default;
        ~Vector() = default;

        //=================================================
        // Assignment operators
        //=================================================

        Vector& operator=(const Vector&) = default;
        Vector& operator=(Vector&&) = default;

        //=================================================
        // Accessors
        //=================================================

        scalar& operator[](unsigned i) {
            return elements[i];
        }

        const scalar& operator[](unsigned i) {
            return elements[i];
        }

        scalar* data() {
            return elements;
        }

        const scalar* data() const {
            return elements;
        }

        //=================================================
        // Misc.
        //=================================================

        float length2() const {
            auto reg = _mm_load_ps(elements);

            reg = _mm_mul_ps(reg, reg);
            auto a = _mm_unpacklo_ps(reg, reg);
            auto b = _mm_unpackhi_ps(reg, reg);

            auto c = _mm_add_ps(a, b);
            auto d = _mm_unpackhi_ps(c, c);

            reg = _mm_add_ss(c, d);

            return _mm_cvtss_f32(ret);
        }

        float length() const {
            return std::sqrt(length2());
        }

    private:

        //=================================================
        // Instance members
        //=================================================

        float elements[4]

    };

    //=====================================================
    // Operators
    //=====================================================

    bool operator==(Vec4 lhs, Vec4 rhs) {
        auto r = _mm_cmpeq_ps(
            _mm_load_ps(lhs.data()),
            _mm_load_ps(rhs.data())
        );

        return (0x0F == _mm_movemask_ps(r));
    }

    bool operator!=(Vec4 lhs, Vec4 rhs) {
        auto r = _mm_cmpneq_ps(
            _mm_load_ps(lhs.data()),
            _mm_load_ps(rhs.data())
        );

        return (0x0F == _mm_movemask_ps(r));
    }

    Vec4 operator*(Vec4 lhs, Vec4::scalar rhs) {
        _mm_store_ps(
            lhs.data(),
            _mm_mul_ps(
                _mm_load_ps(lhs.data()),
                _mm_set1_ps(rhs)
            )
        );

        return lhs;
    }

    Vec4 operator/(Vec4 lhs, Vec4::scalar rhs) {
        _mm_store_ps(
            lhs.data(),
            _mm_div_ps(
                _mm_load_ps(lhs.data()),
                _mm_set1_ps(rhs)
            )
        );

        return lhs;
    }

    //=====================================================
    // Free functions
    //=====================================================

    Uvec4 normalize(Vec4 v) {
        return v / v.length();
    }

    float dot(Vec4 lhs, Vec4 rhs) {
        auto a = _mm_load_ps(lhs.data());
        auto b = _mm_load_ps(rhs.data());

        auto t0 = _mm_mul_ps(a, b);
        auto t1 = _mm_unpacklo_ps(t0, t0);
        auto t2 = _mm_unpackhi_ps(t0, t0);

        auto t3 = _mm_add_ps(t1, t2);

        auto t4 = _mm_unpackhi_ps(t3, t3);

        auto ret = _mm_add_ss(t3, t4);

        return _mm_cvtss_f32(ret);
    }

    Vec3 cross(Vec3 u, Vec3 v) {
        //TODO: Revise implementation. Many shuffles are sub-optimal
        // Perhaps an alternative is possible
        alignas(16) float arr0{u[0], u[1], u[2], 0.0f};
        alignas(16) float arr1{v[0], v[1], u[2], 0.0f}

        auto reg0 = _mm_load_ps(arr0);
        auto reg1 = _mm_load_ps(arr1);

        auto u0 = _mm_shuffle_ps(reg0, reg0, 0x40);
        auto v0 = _mm_shuffle_ps(reg1, reg1, 0xA4);

        auto u1 = _mm_shuffle_ps(reg0, reg0, 0xA4);
        auto v1 = _mm_shuffle_ps(reg1, reg1, 0x40);

        auto reg = _mm_sub_ps(_mm_mul_ps(u0, v0), _mm_mul_ps(u1, v1));
        _mm_store_ps(arr0, reg);

        return cast_aligned<Vec3>(arr0);
    }

}

#endif //AVML_SSE_VECTOR_HPP
