#ifndef AVML_DEF_VEC2F_IPP
#define AVML_DEF_VEC2F_IPP

namespace avml {

    template<>
    class alignas(alignof(float) * 2) Vector2<float> {
    public:

        using scalar = float;

        static constexpr unsigned width = 2;

        //=================================================
        // Creation functions
        //=================================================

        AVML_FINL static Vector2 read(const float* p) {
            return Vector2{p[0], p[1]};
        }

        AVML_FINL static Vector2 read_aligned(const float* p) {
            return Vector2{p[0], p[1]};
        }

        //=================================================
        // -ctors
        //=================================================

        AVML_FINL Vector2(float v):
            elements{v, v} {}

        AVML_FINL Vector2(float x, float y):
            elements{x, y} {}

        AVML_FINL Vector2(uvec2f v):
            elements{v[0], v[1]} {}

        Vector2() = default;
        Vector2(const Vector2&) = default;
        Vector2(Vector2&&) = default;
        ~Vector2() = default;

        //=================================================
        // Assignment operators
        //=================================================

        Vector2& operator=(const Vector2&) = default;
        Vector2& operator=(Vector2&&) = default;

        //=================================================
        // Unary arithmetic operators
        //=================================================

        AVML_FINL Vector2 operator+() const {
            return *this;
        }

        AVML_FINL Vector2 operator-() const {
            return Vector2{
                -elements[0],
                -elements[1]
            };
        }

        //=================================================
        // Arithmetic assignment operators
        //=================================================

        AVML_FINL Vector2& operator+=(const Vector2& rhs) {
            for (unsigned i = 0; i < width; ++i) {
                elements[i] += rhs[i];
            }
            return *this;
        }

        AVML_FINL Vector2& operator-=(const Vector2& rhs) {
            for (unsigned i = 0; i < width; ++i) {
                elements[i] -= rhs[i];
            }
            return *this;
        }

        AVML_FINL Vector2& operator*=(const Vector2 rhs) {
            for (unsigned i = 0; i < width; ++i) {
                elements[i] *= rhs[i];
            }
            return *this;
        }

        AVML_FINL Vector2& operator*=(const scalar rhs) {
            for (unsigned i = 0; i < width; ++i) {
                elements[i] *= rhs;
            }
            return *this;
        }

        AVML_FINL Vector2& operator/=(const Vector2 rhs) {
            for (unsigned i = 0; i < width; ++i) {
                elements[i] /= rhs[i];
            }
            return *this;
        }

        AVML_FINL Vector2& operator/=(const scalar rhs) {
            for (unsigned i = 0; i < width; ++i) {
                elements[i] /= rhs;
            }
            return *this;
        }

        //=================================================
        // Accessors
        //=================================================

        AVML_FINL float& operator[](unsigned i) {
            return elements[i];
        }

        AVML_FINL const float& operator[](unsigned i) const {
            return elements[i];
        }

        AVML_FINL float* data() {
            return elements;
        }

        AVML_FINL const float* data() const {
            return elements;
        }

    private:

        //=================================================
        // Instance members
        //=================================================

        float elements[width] = {0.0f, 0.0f};

    };

    //=====================================================
    // Comparison operators
    //=====================================================

    AVML_FINL bool operator==(vec2f lhs, vec2f rhs) {
        return
            (lhs[0] == rhs[0]) &&
            (lhs[1] == rhs[1]);
    }

    AVML_FINL bool operator!=(vec2f lhs, vec2f rhs) {
        return
            (lhs[0] != rhs[0]) ||
            (lhs[1] != rhs[1]);
    }

    //=====================================================
    // Arithmetic operators
    //=====================================================

    AVML_FINL vec2f operator+(vec2f lhs, vec2f rhs) {
        lhs += rhs;
        return lhs;
    }

    AVML_FINL vec2f operator-(vec2f lhs, vec2f rhs) {
        lhs -= rhs;
        return lhs;
    }

    AVML_FINL vec2f operator*(vec2f lhs, vec2f rhs) {
        lhs *= rhs;
        return lhs;
    }

    AVML_FINL vec2f operator*(vec2f lhs, float rhs) {
        lhs *= rhs;
        return lhs;
    }

    AVML_FINL vec2f operator*(float lhs, vec2f rhs) {
        rhs *= lhs;
        return rhs;
    }

    AVML_FINL vec2f operator/(vec2f lhs, float rhs) {
        lhs /= rhs;
        return lhs;
    }

    AVML_FINL vec2f operator/(vec2f lhs, vec2f rhs) {
        lhs /= rhs;
        return lhs;
    }

    //=====================================================
    // Vector math
    //=====================================================

    AVML_FINL float dot(vec2f lhs, vec2f rhs) {
        return
            lhs[0] * rhs[0] +
            lhs[1] * rhs[1];
    }

    AVML_FINL float length2(uvec2f) = delete;

    AVML_FINL float length2(vec2f v) {
        return dot(v, v);
    }

    AVML_FINL float length(uvec2f) = delete;

    AVML_FINL float length(vec2f v) {
        return std::sqrt(length2(v));
    }

    AVML_FINL uvec2f normalize(vec2f v) {
        v /= length(v);
        return uvec2f::read_aligned(v.data());
    }

    AVML_FINL uvec2f assume_normalized(vec2f v) {
        return uvec2f::read_aligned(v.data());
    }

    AVML_FINL vec2f project(vec2f a, vec2f b) {
        return (dot(a, b) / dot(b, b)) * b;
    }

    AVML_FINL vec2f project(vec2f a, uvec2f b) {
        return dot(a, b) * b;
    }

    AVML_FINL vec2f rotate(vec2f v, float angle) {
        float cos = std::cos(angle);
        float sin = std::sin(angle);

        return vec2f{
            v[0] * cos - v[1] * sin,
            v[0] * sin + v[1] * cos
        };
    }

    AVML_FINL vec2f reflect(vec2f v, uvec2f normal) {
        return 2 * dot(v, normal) * normal - v;
    }

    AVML_FINL uvec2f reflect(uvec2f v, uvec2f normal) {
        return uvec2f::read_aligned(reflect(static_cast<vec2f>(v), normal).data());
    }

    //=====================================================
    // Vectorized math
    //=====================================================

    AVML_FINL vec2f abs(vec2f v) {
        v[0] = std::abs(v[0]);
        v[1] = std::abs(v[1]);
        return v;
    }

    AVML_FINL vec2f max(vec2f u, vec2f v) {
        u[0] = std::max(u[0], v[0]);
        u[1] = std::max(u[1], v[1]);
        return u;
    }

    AVML_FINL vec2f min(vec2f u, vec2f v) {
        u[0] = std::min(u[0], v[0]);
        u[1] = std::min(u[1], v[1]);
        return u;
    }

    //=====================================================
    // Swizzling
    //=====================================================

    // Single component

    AVML_FINL float x(vec2f v) {
        return v[0];
    }

    AVML_FINL float y(vec2f v) {
        return v[1];
    }

    // Two component

    AVML_FINL vec2f xy(vec2f v) {
        return v;
    }

    AVML_FINL vec2f yx(vec2f v) {
        return {v[1], v[0]};
    }

}

#endif
