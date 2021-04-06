#ifndef AVML_VEC2_HPP
#define AVML_VEC2_HPP

#include <cmath>

namespace avml {

    namespace impl {

        class alignas(8) Base2D {
        public:

            //=============================================
            // -ctors
            //=============================================

            Base2D(const float x, const float y):
                elems() {
                elems[0] = x;
                elems[1] = y;
            }

            Base2D() = default;
            Base2D(const Base2D&) = default;
            Base2D(Base2D&&) = default;
            ~Base2D() = default;

            //=============================================
            // Assignment Operators
            //=============================================

            Base2D& operator=(const Base2D&) = default;
            Base2D& operator=(Base2D&&) = default;

            //=================================================
            // Accessors
            //=================================================

            float operator[](unsigned i) const {
                return elems[i % 2];
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

            float elems[2];

        };

        class Base2D_accessible : public Base2D {
        public:

            using Base2D::Base2D;

            float& operator[](unsigned i) {
                return elems[i % 2];
            }

            explicit operator float*() {
                return elems;
            }

        };

    }

    class Unit_vec2 : public impl::Base2D {
    public:

        //=================================================
        // -ctors
        //=================================================

        using impl::Base2D::Base2D;

        Unit_vec2(float x, float y):
            Base2D(x, y) {
            float length = std::hypot(elems[0], elems[1]);
            elems[0] /= length;
            elems[1] /= length;
        }

    };

    class Vec2 : public impl::Base2D_accessible {
    public:

        //=================================================
        // -ctors
        //=================================================

        using impl::Base2D_accessible::Base2D_accessible;

        explicit Vec2(float x):
            Base2D_accessible(x, x) {}

        Vec2(Unit_vec2 vec):
            Base2D_accessible(vec[0], vec[1]) {}

        Vec2() = default;
        Vec2(const Vec2&) = default;
        Vec2(Vec2&&) = default;
        ~Vec2() = default;

        //=================================================
        // Assignment operators
        //=================================================

        Vec2& operator=(const Vec2&) = default;
        Vec2& operator=(Vec2&&) = default;

        Vec2& operator=(float x) {
            elems[0] = x;
            elems[1] = x;
            return *this;
        }

        //=================================================
        // Arithmetic assignment operators
        //=================================================

        Vec2& operator+=(const Vec2& v) {
            elems[0] += v.elems[0];
            elems[1] += v.elems[1];
            return *this;
        }

        Vec2& operator-=(const Vec2& v) {
            elems[0] -= v.elems[0];
            elems[1] -= v.elems[1];
            return *this;
        }

        Vec2& operator*=(const float v) {
            elems[0] *= v;
            elems[1] *= v;
            return *this;
        }

        Vec2& operator/=(const float v) {
            elems[0] /= v;
            elems[1] /= v;
            return *this;
        }

        //=================================================
        // Arithmetic operators
        //=================================================

        Vec2 operator+(Vec2 v) {
            auto ret = *this;
            ret += v;
            return ret;
        }

        Vec2 operator-(Vec2 v) {
            auto ret = *this;
            ret -= v;
            return ret;
        }

        Vec2 operator*(float s) {
            auto ret = *this;
            ret *= s;
            return ret;
        }

        Vec2 operator/(float s) {
            auto ret = *this;
            ret /= s;
            return ret;
        }

        //=================================================
        // Query methods
        //=================================================

        float length2() const {
            return
                elems[0] * elems[0] +
                elems[1] * elems[1];
        }

        float length() const {
            return std::hypot(elems[0], elems[1]);
        }

        Unit_vec2 normalize() const {
            Vec2 ret = *this;
            ret /= ret.length();
            return Unit_vec2{ret[0], ret[1]};
        }

    };

    float dot(Vec2 a, Vec2 b) {
        return a[0] * b[0] + a[1] * b[1];
    }

    Vec2 rotate(Vec2 v, float angle) {
        float c = std::cos(angle);
        float s = std::sin(angle);

        return Vec2{
            (v[0] * c - v[1] * s),
            (v[0] * s + v[1] * c)
        };
    }

    class Point2 : public impl::Base2D_accessible {
    public:

        using impl::Base2D_accessible::Base2D_accessible;

        //=================================================
        // Arithmetic assignment operators
        //=================================================

        Point2& operator+=(Vec2 vec) {
            elems[0] += vec[0];
            elems[1] += vec[1];
            return *this;
        }

        Point2& operator-=(Vec2 vec) {
            elems[0] += vec[0];
            elems[1] += vec[1];
            return *this;
        }

        //=================================================
        // Arithmetic operators
        //=================================================

        Point2 operator+(Vec2 vec) {
            auto ret = *this;
            ret[0] += vec[0];
            ret[1] += vec[1];
            return ret;
        }

        friend Point2 operator+(Vec2 vec, Point2 p) {
            return p += vec;
        }

        Point2 operator-(Vec2 vec) {
            auto ret = *this;
            ret[0] -= vec[0];
            ret[1] -= vec[1];
            return ret;
        }

        friend Point2 operator-(Vec2 vec, Point2 p) {
            return p -= vec;
        }

        Vec2 operator-(Point2 p) {
            return Vec2{
                elems[0] - p[0],
                elems[1] - p[1],
            };
        }

    };

    Point2 rotate(Point2 p, Point2 o, float angle) {
        return o + rotate(p - o, angle);
    }

    class alignas(16) Ray2 {
    private:
        Point2 start;
        Unit_vec2 offset;

        //=================================================
        //
        //=================================================



    };

    class alignas(16) Line_segment2 {
    private:
        Point2 start;
        Point2 end;
    };

}

#endif //AVML_VEC2_HPP
