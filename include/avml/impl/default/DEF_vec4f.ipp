#ifndef AVML_VEC4F_IPP
#define AVML_VEC4F_IPP

namespace avml {

    template<>
    class alignas(alignof(float) * 4) Vector<float, 4> {
    public:

        using scalar = float;

        static constexpr unsigned width = 4;

        //=================================================
        // Creation functions
        //=================================================

        AVML_FINL static Vector read(const float* p) {
            return Vector{p[0], p[1], p[2], p[3]};
        }

        AVML_FINL static Vector read_aligned(const float* p) {
            return Vector{p[0], p[1], p[2], p[3]};
        }

        //=================================================
        // -ctors
        //=================================================

        explicit AVML_FINL Vector(float v):
            elements{v, v, v, v} {}

        AVML_FINL Vector(float x, float y, float z, float w):
            elements{x, y, z, w} {}

        AVML_FINL Vector(uvec4f v):
            elements{v[0], v[1], v[2], v[3]} {}

        AVML_FINL Vector(vec2f v, float z, float w):
            elements{v[0], v[1], z, w} {}

        AVML_FINL Vector(float x, vec2f v, float w):
            elements{x, v[0], v[1], w} {}

        AVML_FINL Vector(float x, float y, vec2f v):
            elements{x, y, v[0], v[1]} {}

        AVML_FINL Vector(vec2f v, vec2f u):
            elements{v[0], v[1], u[0], u[1]} {}

        AVML_FINL Vector(vec3f v, float w):
            elements{v[0], v[1], v[2], w} {}

        AVML_FINL Vector(float x, vec3f v):
            elements{x, v[0], v[1], v[2]} {}

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
        // Arithmetic assignment operators
        //=================================================

        AVML_FINL Vector& operator+=(const Vector& rhs) {
            for (int i = 0; i < width; ++i) {
                elements[i] += rhs[i];
            }
            return *this;
        }

        AVML_FINL Vector& operator-=(const Vector& rhs) {
            for (int i = 0; i < width; ++i) {
                elements[i] -= rhs[i];
            }
            return *this;
        }

        AVML_FINL Vector& operator*=(const scalar rhs) {
            for (int i = 0; i < width; ++i) {
                elements[i] *= rhs;
            }
            return *this;
        }

        AVML_FINL Vector& operator/=(const scalar rhs) {
            for (int i = 0; i < width; ++i) {
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

        float elements[width] = {0.0f, 0.0f, 0.0f, 0.0f};

    };

    AVML_FINL bool operator==(vec4f lhs, vec4f rhs) {
        return
            (lhs[0] == rhs[0]) &&
            (lhs[1] == rhs[1]) &&
            (lhs[2] == rhs[2]) &&
            (lhs[3] == rhs[3]);
    }

    AVML_FINL bool operator!=(vec4f lhs, vec4f rhs) {
        return
            (lhs[0] != rhs[0]) ||
            (lhs[1] != rhs[1]) ||
            (lhs[2] != rhs[2]) ||
            (lhs[3] != rhs[3]);
    }

    AVML_FINL vec4f operator+(vec4f lhs, vec4f rhs) {
        lhs[0] += rhs[0];
        lhs[1] += rhs[1];
        lhs[2] += rhs[2];
        lhs[3] += rhs[3];
        return lhs;
    }

    AVML_FINL vec4f operator-(vec4f lhs, vec4f rhs) {
        lhs[0] -= rhs[0];
        lhs[1] -= rhs[1];
        lhs[2] -= rhs[2];
        lhs[3] -= rhs[3];
        return lhs;
    }

    AVML_FINL vec4f operator*(vec4f lhs, float rhs) {
        lhs[0] *= rhs;
        lhs[1] *= rhs;
        lhs[2] *= rhs;
        lhs[3] *= rhs;
        return lhs;
    }

    AVML_FINL vec4f operator*(float lhs, vec4f rhs) {
        rhs[0] *= lhs;
        rhs[1] *= lhs;
        rhs[2] *= lhs;
        rhs[3] *= lhs;
        return rhs;
    }

    AVML_FINL vec4f operator/(vec4f lhs, float rhs) {
        lhs[0] /= rhs;
        lhs[1] /= rhs;
        lhs[2] /= rhs;
        lhs[3] /= rhs;
        return lhs;
    }

    AVML_FINL float dot(vec4f lhs, vec4f rhs) {
        return
            lhs[0] * rhs[0] +
            lhs[1] * rhs[1] +
            lhs[2] * rhs[2] +
            lhs[3] * rhs[2];
    }

    AVML_FINL float length2(uvec4f) = delete;

    AVML_FINL float length2(vec4f v) {
        return dot(v, v);
    }

    AVML_FINL float length(uvec4f) = delete;

    AVML_FINL float length(vec4f v) {
        return std::sqrt(length2(v));
    }

    AVML_FINL Unit_vector<float, 4> normalize(vec4f v) {
        v /= length(v);
        return Unit_vector<float, 4>::read_aligned(v.data());
    }

    AVML_FINL vec4f project(vec4f a, vec4f b) {
        return (dot(a, b) / dot(b, b)) * b;
    }

    AVML_FINL vec4f project(vec4f a, uvec4f b) {
        return dot(a, b) * b;
    }

    AVML_FINL vec4f reflect(vec4f v, uvec4f normal) {
        return 2 * dot(v, normal) * normal - v;
    }

    AVML_FINL uvec4f reflect(uvec4f v, uvec4f normal) {
        return uvec4f::read_aligned(reflect(static_cast<vec4f>(v), normal).data());
    }

    //=====================================================
    // Vectorized math
    //=====================================================

    AVML_FINL vec4f abs(vec4f v) {
        v[0] = std::abs(v[0]);
        v[1] = std::abs(v[1]);
        v[2] = std::abs(v[2]);
        v[3] = std::abs(v[3]);
        return v;
    }

    AVML_FINL vec4f max(vec4f u, vec4f v) {
        u[0] = std::max(u[0], v[0]);
        u[1] = std::max(u[1], v[1]);
        u[2] = std::max(u[2], v[2]);
        u[3] = std::max(u[3], v[3]);
        return u;
    }

    AVML_FINL vec4f min(vec4f u, vec4f v) {
        u[0] = std::min(u[0], v[0]);
        u[1] = std::min(u[1], v[1]);
        u[2] = std::min(u[2], v[2]);
        u[3] = std::min(u[3], v[3]);
        return u;
    }

}

#endif
