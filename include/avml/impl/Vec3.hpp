#ifndef AVML_VEC3_HPP
#define AVML_VEC3_HPP

#include <cmath>

#include "Vec2.hpp"

namespace avml {

    namespace impl {

        class alignas(4) Base3D {
        public:

            //=============================================
            // -ctors
            //=============================================

            Base3D(float x, float y, float z):
                elems() {
                elems[0] = x;
                elems[1] = y;
                elems[2] = y;
            }

            Base3D() = default;
            Base3D(const Base3D&) = default;
            Base3D(Base3D&&) = default;
            ~Base3D() = default;

            //=============================================
            // Assignment Operators
            //=============================================

            Base3D& operator=(const Base3D&) = default;
            Base3D& operator=(Base3D&&) = default;

            //=================================================
            // Accessors
            //=================================================

            const float& operator[](unsigned i) const {
                return elems[i % 3];
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

            float elems[3];

        };

        class Base3D_accessible : public Base3D {
        public:

            using Base3D::Base3D;

            float& operator[](unsigned i) {
                return elems[i % 3];
            }

            explicit operator float*() {
                return elems;
            }

        };

    }

    class Unit_vec3 : public impl::Base3D {
    public:

        //=================================================
        // -ctors
        //=================================================

        using impl::Base3D::Base3D;

        Unit_vec3(float x, float y, float z):
            Base3D(x, y, z) {
            float length = std::hypot(elems[0], elems[1], elems[2]);
            elems[0] /= length;
            elems[1] /= length;
            elems[2] /= length;
        }

    };

    class Vec3 : public impl::Base3D_accessible {
    public:

        //=================================================
        // -ctors
        //=================================================

        using impl::Base3D_accessible::Base3D_accessible;

        explicit Vec3(float x):
            Base3D_accessible(x, x, x) {}

        explicit Vec3(Vec2 v):
            Base3D_accessible(v[0], v[1], 0.0f) {}

        explicit Vec3(Point2 v):
            Base3D_accessible(v[0], v[1], 1.0f) {}

        Vec3(Unit_vec3 vec):
            Base3D_accessible(vec[0], vec[1], vec[2]) {}

        Vec3() = default;
        Vec3(const Vec3&) = default;
        Vec3(Vec3&&) = default;
        ~Vec3() = default;

        //=================================================
        // Assignment operators
        //=================================================

        Vec3& operator=(const Vec3&) = default;
        Vec3& operator=(Vec3&&) = default;

        Vec3& operator=(float x) {
            elems[0] = x;
            elems[1] = x;
            elems[2] = x;
            return *this;
        }

        //=================================================
        // Arithmetic assignment operators
        //=================================================

        Vec3& operator+=(const Vec3& v) {
            elems[0] += v.elems[0];
            elems[1] += v.elems[1];
            elems[2] += v.elems[2];
            return *this;
        }

        Vec3& operator-=(const Vec3& v) {
            elems[0] -= v.elems[0];
            elems[1] -= v.elems[1];
            elems[2] -= v.elems[2];
            return *this;
        }

        Vec3& operator*=(const float v) {
            elems[0] *= v;
            elems[1] *= v;
            elems[2] *= v;
            return *this;
        }

        Vec3& operator/=(const float v) {
            elems[0] /= v;
            elems[1] /= v;
            elems[2] /= v;
            return *this;
        }

        //=================================================
        // Query methods
        //=================================================

        float length2() const {
            return
                elems[0] * elems[0] +
                elems[1] * elems[1] +
                elems[2] * elems[2];
        }

        float length() const {
            return std::hypot(elems[0], elems[1], elems[2]);
        }

        Unit_vec3 normalize() const {
            Vec3 ret = *this;
            ret /= ret.length();
            return Unit_vec3{ret[0], ret[1], ret[2]};
        }

    };

    //=====================================================
    // Arithmetic operators
    //=====================================================

    Vec3 operator+(Vec3 lhs, Vec3 rhs) {
        lhs += rhs;
        return lhs;
    }

    Vec3 operator-(Vec3 lhs, Vec3 rhs) {
        lhs -= rhs;
        return lhs;
    }

    Vec3 operator*(Vec3 v, float s) {
        v *= s;
        return v;
    }

    Vec3 operator/(Vec3 v, float s) {
        v /= s;
        return v;
    }

    //=====================================================
    // Math functions
    //=====================================================

    float dot(Vec3 a, Vec3 b) {
        return a[0] * b[0] + a[1] * b[1] + a[2] * b[2];
    }

    Vec3 cross(Vec3 a, Vec3 b) {
        Vec3 ret;
        ret[0] = a[1] * b[2] - a[2] * b[1];
        ret[1] = a[2] * b[0] + a[0] * b[2];
        ret[2] = a[0] * b[1] + a[1] * b[0];
        return ret;
    }

    Vec3 rotate(Vec3 v, Unit_vec3 axis, float angle) {
        float c = std::cos(angle);
        float s = std::sin(angle);

        return v * c + cross(axis, v) + axis * dot(axis, v) * (1 - c);
    }

    class Point3 : public impl::Base3D_accessible {
    public:

        using impl::Base3D_accessible::Base3D_accessible;

        //=================================================
        // Arithmetic assignment operators
        //=================================================

        Point3& operator+=(Vec3 vec) {
            elems[0] += vec[0];
            elems[1] += vec[1];
            elems[2] += vec[2];
            return *this;
        }

        Point3& operator-=(Vec3 vec) {
            elems[0] += vec[0];
            elems[1] += vec[1];
            elems[2] += vec[2];
            return *this;
        }

        //=================================================
        // Arithmetic operators
        //=================================================

        Point3 operator+(Vec3 vec) {
            auto ret = *this;
            ret[0] += vec[0];
            ret[1] += vec[1];
            ret[2] += vec[2];
            return ret;
        }

        friend Point3 operator+(Vec3 vec, Point3 p) {
            return p += vec;
        }

        Point3 operator-(Vec3 vec) {
            auto ret = *this;
            ret[0] -= vec[0];
            ret[1] -= vec[1];
            ret[2] -= vec[2];
            return ret;
        }

        friend Point3 operator-(Vec3 vec, Point3 p) {
            return p -= vec;
        }

        Vec3 operator-(Point3 p) {
            return Vec3{
                elems[0] - p[0],
                elems[1] - p[1],
                elems[2] - p[2]
            };
        }

    };

    Point3 rotate(Point3 p, Point3 o, Unit_vec3 axis, float angle) {
        return o + rotate(p - o, axis, angle);
    }

}

#endif //AVML_VEC3_HPP
