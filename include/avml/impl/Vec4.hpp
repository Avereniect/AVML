#ifndef AVML_VEC4_HPP
#define AVML_VEC4_HPP

#include <cmath>

#include "Vec3.hpp"

namespace avml {

    namespace impl {

        class alignas(16) Base4D {
        public:

            //=============================================
            // -ctors
            //=============================================

            Base4D(float w, float x, float y, float z) :
                elems() {
                elems[0] = w;
                elems[1] = x;
                elems[2] = y;
                elems[3] = y;
            }

            Base4D() = default;

            Base4D(const Base4D&) = default;

            Base4D(Base4D&&) = default;

            ~Base4D() = default;

            //=============================================
            // Assignment Operators
            //=============================================

            Base4D& operator=(const Base4D&) = default;

            Base4D& operator=(Base4D&&) = default;

            //=================================================
            // Accessors
            //=================================================

            const float& operator[](unsigned i) const {
                return elems[i % 4];
            }

            //=================================================
            // Conversion operators
            //=================================================

            explicit operator const float*() const {
                return elems;
            }

            //=============================================
            // Instance members
            //=============================================

        protected:

            float elems[4];

        };

        class Base4D_accessible : public Base4D {
        public:

            using Base4D::Base4D;

            float& operator[](unsigned i) {
                return elems[i % 4];
            }

            explicit operator float*() {
                return elems;
            }

        };

    }

    class Unit_vec4 : public impl::Base4D {
    public:

        //=================================================
        // -ctors
        //=================================================

        using impl::Base4D::Base4D;

        Unit_vec4(float w, float x, float y, float z):
            Base4D(w, x, y, z) {
            float length = std::sqrt(
                elems[0] * elems[0] +
                elems[1] * elems[1] +
                elems[2] * elems[2] +
                elems[3] * elems[3]);

            elems[0] /= length;
            elems[1] /= length;
            elems[2] /= length;
            elems[3] /= length;
        }

    };

    class Vec4 : public impl::Base4D_accessible {
    public:

        //=================================================
        // -ctors
        //=================================================

        using impl::Base4D_accessible::Base4D_accessible;

        explicit Vec4(float x):
            Base4D_accessible(x, x, x, x) {}

        explicit Vec4(Vec3 v):
            Base4D_accessible(v[0], v[1], v[2], 0.0f) {}

        explicit Vec4(Point3 p):
            Base4D_accessible(p[0], p[1], p[2], 1.0f) {}

        Vec4(Unit_vec4 vec):
            Base4D_accessible(vec[0], vec[1], vec[2], vec[4]) {}

        Vec4() = default;
        Vec4(const Vec4&) = default;
        Vec4(Vec4&&) = default;
        ~Vec4() = default;

        //=================================================
        // Assignment operators
        //=================================================

        Vec4& operator=(const Vec4&) = default;
        Vec4& operator=(Vec4&&) = default;

        Vec4& operator=(float x) {
            elems[0] = x;
            elems[1] = x;
            elems[2] = x;
            elems[3] = x;
            return *this;
        }

        //=================================================
        // Arithmetic assignment operators
        //=================================================

        Vec4& operator+=(const Vec4& v) {
            elems[0] += v.elems[0];
            elems[1] += v.elems[1];
            elems[2] += v.elems[2];
            elems[3] += v.elems[3];
            return *this;
        }

        Vec4& operator-=(const Vec4& v) {
            elems[0] -= v.elems[0];
            elems[1] -= v.elems[1];
            elems[2] -= v.elems[2];
            elems[3] -= v.elems[3];
            return *this;
        }

        Vec4& operator*=(const float v) {
            elems[0] *= v;
            elems[1] *= v;
            elems[2] *= v;
            elems[3] *= v;
            return *this;
        }

        Vec4& operator/=(const float v) {
            elems[0] /= v;
            elems[1] /= v;
            elems[2] /= v;
            elems[3] /= v;
            return *this;
        }

        //=================================================
        // Query methods
        //=================================================

        float length2() const {
            return
                elems[0] * elems[0] +
                elems[1] * elems[1] +
                elems[2] * elems[2] +
                elems[3] * elems[3];
        }

        float length() const {
            return std::sqrt(length2());
        }

        Unit_vec4 normalize() const {
            Vec4 ret = *this;
            ret /= ret.length();
            return Unit_vec4{ret[0], ret[1], ret[2], ret[3]};
        }

    };;

    //=====================================================
    // Arithmetic operators
    //=====================================================

    Vec4 operator+(Vec4 lhs, Vec4 rhs) {
        lhs += rhs;
        return lhs;
    }

    Vec4 operator-(Vec4 lhs, Vec4 rhs) {
        lhs -= rhs;
        return lhs;
    }

    Vec4 operator*(Vec4 v, float s) {
        v *= s;
        return v;
    }

    Vec4 operator/(Vec4 v, float s) {
        v /= s;
        return v;
    }

    //=====================================================
    // Math functions
    //=====================================================

    float dot(Vec4 a, Vec4 b) {
        return a[0] * b[0] + a[1] * b[1] + a[2] * b[2] + a[3] * b[3];
    }
    
    class Point4 : public impl::Base4D_accessible {
    public:

        using impl::Base4D_accessible::Base4D_accessible;

        //=================================================
        // Arithmetic assignment operators
        //=================================================

        Point4& operator+=(Vec4 vec) {
            elems[0] += vec[0];
            elems[1] += vec[1];
            elems[2] += vec[2];
            elems[3] += vec[3];
            return *this;
        }

        Point4& operator-=(Vec4 vec) {
            elems[0] += vec[0];
            elems[1] += vec[1];
            elems[2] += vec[2];
            elems[3] += vec[3];
            return *this;
        }

        //=================================================
        // Arithmetic operators
        //=================================================

        Point4 operator+(Vec4 vec) {
            auto ret = *this;
            ret[0] += vec[0];
            ret[1] += vec[1];
            ret[2] += vec[2];
            ret[3] += vec[3];
            return ret;
        }

        friend Point4 operator+(Vec4 vec, Point4 p) {
            return p += vec;
        }

        Point4 operator-(Vec4 vec) {
            auto ret = *this;
            ret[0] -= vec[0];
            ret[1] -= vec[1];
            ret[2] -= vec[2];
            ret[3] -= vec[3];
            return ret;
        }

        friend Point4 operator-(Vec4 vec, Point4 p) {
            return p -= vec;
        }

        Vec4 operator-(Point4 p) {
            return Vec4{
                elems[0] - p[0],
                elems[1] - p[1],
                elems[2] - p[2],
                elems[3] - p[3]
            };
        }

    };

}

#endif //AVML_VEC4_HPP
