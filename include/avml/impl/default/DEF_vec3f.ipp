#ifndef AVML_DEF_VEC3F_IPP
#define AVML_DEF_VEC3F_IPP

#define AVML_VEC3_2_SWIZZLE(x, y) \
    vec2f

namespace avml {

    template<>
    class alignas(sizeof(float) * 1) Vector<float, 3> {
    public:

        using scalar = float;

        static constexpr unsigned width = 3;

        //=================================================
        // Creation functions
        //=================================================

        AVML_FINL static Vector read(const float* p) {
            return Vector{p[0], p[1], p[2]};
        }

        AVML_FINL static Vector read_aligned(const float* p) {
            return Vector{p[0], p[1], p[2]};
        }

        //=================================================
        // -ctors
        //=================================================

        AVML_FINL Vector(float v):
            elements{v, v, v} {}

        AVML_FINL Vector(float x, float y, float z):
            elements{x, y, z} {}

        AVML_FINL Vector(Unit_vector<float, 3> v):
            elements{v[0], v[1], v[2]} {}

        AVML_FINL Vector(Vector<float, 2> v, float z):
            elements{v[0], v[1], z} {}

        AVML_FINL Vector(float w, Vector<float, 2> v):
            elements{w, v[0], v[1]} {}

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
        // Unary arithmetic operators
        //=================================================

        AVML_FINL Vector operator+() const {
            return *this;
        }

        AVML_FINL Vector operator-() const {
            return Vector{
                -elements[0],
                -elements[1],
                -elements[2],
            };
        }

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

        AVML_FINL Vector& operator*=(const Vector rhs) {
            for (int i = 0; i < width; ++i) {
                elements[i] *= rhs[i];
            }
            return *this;
        }

        AVML_FINL Vector& operator/=(const Vector rhs) {
            for (int i = 0; i < width; ++i) {
                elements[i] /= rhs[i];
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

        float elements[width] = {0.0f, 0.0f, 0.0f};

    };

    //=====================================================
    // Comparison operators
    //=====================================================

    AVML_FINL bool operator==(vec3f lhs, vec3f rhs) {
        return
            (lhs[0] == rhs[0]) &&
            (lhs[1] == rhs[1]) &&
            (lhs[2] == rhs[2]);
    }

    AVML_FINL bool operator!=(vec3f lhs, vec3f rhs) {
        return
            (lhs[0] != rhs[0]) ||
            (lhs[1] != rhs[1]) ||
            (lhs[2] != rhs[2]);
    }

    //=====================================================
    // Arithmetic operators
    //=====================================================

    AVML_FINL vec3f operator+(vec3f lhs, vec3f rhs) {
        lhs += rhs;
        return lhs;
    }

    AVML_FINL vec3f operator-(vec3f lhs, vec3f rhs) {
        lhs -= rhs;
        return lhs;
    }

    AVML_FINL vec3f operator*(vec3f lhs, vec3f rhs) {
        lhs *= rhs;
        return lhs;
    }

    AVML_FINL vec3f operator*(vec3f lhs, float rhs) {
        lhs *= rhs;
        return lhs;
    }

    AVML_FINL vec3f operator*(float lhs, vec3f rhs) {
        rhs *= lhs;
        return rhs;
    }

    AVML_FINL vec3f operator/(vec3f lhs, float rhs) {
        lhs /= rhs;
        return lhs;
    }

    AVML_FINL vec3f operator/(vec3f lhs, vec3f rhs) {
        lhs /= rhs;
        return lhs;
    }

    //=====================================================
    // Vector math
    //=====================================================

    AVML_FINL float dot(vec3f lhs, vec3f rhs) {
        return
            lhs[0] * rhs[0] +
            lhs[1] * rhs[1] +
            lhs[2] * rhs[2];
    }

    AVML_FINL float length2(uvec3f) = delete;

    AVML_FINL float length2(vec3f v) {
        return dot(v, v);
    }

    AVML_FINL float length(uvec3f) = delete;

    AVML_FINL float length(vec3f v) {
        return std::sqrt(length2(v));
    }

    AVML_FINL uvec3f assume_normalized(vec3f v) {
        return uvec3f::read_aligned(v.data());
    }

    AVML_FINL uvec3f normalize(vec3f v) {
        v /= length(v);
        return assume_normalized(v);
    }

    AVML_FINL vec3f cross(vec3f lhs, vec3f rhs) {
        return vec3f {
            lhs[1] * rhs[2] - lhs[2] * rhs[1],
            lhs[2] * rhs[0] - lhs[0] * rhs[2],
            lhs[0] * rhs[1] - lhs[1] * rhs[0]
        };
    }

    AVML_FINL vec3f project(vec3f a, vec3f b) {
        return (dot(a, b) / dot(b, b)) * b;
    }

    AVML_FINL vec3f project(vec3f a, uvec3f b) {
        return dot(a, b) * b;
    }

    AVML_FINL vec3f project_onto_plane(vec3f v, uvec3f normal) {
        return (v - project(v, normal));
    }

    AVML_FINL vec3f rotate(vec3f v, float angle, uvec3f axis) {
        float s = std::sin(angle);
        float c = std::cos(angle);

        return (v * c) + (cross(axis, v) * s) + (axis * dot(axis, v) * (1 - c));
    }

    AVML_FINL uvec3f rotate(uvec3f v, float angle, uvec3f axis) {
        return uvec3f::read_aligned(rotate(static_cast<vec3f>(v), angle, axis).data());
    }

    AVML_FINL vec3f rotate_x(vec3f v, float angle) {
        float s = std::sin(angle);
        float c = std::cos(angle);

        v[1] = v[1] * c - v[2] * s;
        v[2] = v[1] * s + v[2] * c;

        return assume_normalized(v);
    }

    AVML_FINL vec3f rotate_y(vec3f v, float angle) {
        float s = std::sin(angle);
        float c = std::cos(angle);

        v[0] = v[0] * c + v[2] * s;
        v[2] = v[2] * c - v[0] * s;

        return assume_normalized(v);
    }

    AVML_FINL vec3f rotate_z(vec3f v, float angle) {
        float s = std::sin(angle);
        float c = std::cos(angle);

        v[0] = v[0] * c - v[1] * s;
        v[1] = v[0] * s + v[1] * c;

        return assume_normalized(v);
    }

    AVML_FINL vec3f reflect(vec3f v, uvec3f normal) {
        return 2 * dot(v, normal) * normal - v;
    }

    AVML_FINL uvec3f reflect(uvec3f v, uvec3f normal) {
        return uvec3f::read_aligned(reflect(static_cast<vec3f>(v), normal).data());
    }

    //=====================================================
    // Vectorized math
    //=====================================================

    AVML_FINL vec3f abs(vec3f v) {
        v[0] = std::abs(v[0]);
        v[1] = std::abs(v[1]);
        v[2] = std::abs(v[2]);
        return v;
    }

    AVML_FINL vec3f max(vec3f u, vec3f v) {
        u[0] = std::max(u[0], v[0]);
        u[1] = std::max(u[1], v[1]);
        u[2] = std::max(u[2], v[2]);
        return u;
    }

    AVML_FINL vec3f min(vec3f u, vec3f v) {
        u[0] = std::min(u[0], v[0]);
        u[1] = std::min(u[1], v[1]);
        u[2] = std::min(u[2], v[2]);
        return u;
    }

    //=====================================================
    // Swizzling
    //=====================================================

    // Single component

    float x(vec3f v) {
        return v[0];
    }

    float y(vec3f v) {
        return v[1];
    }

    float z(vec3f v) {
        return v[2];
    }

    // Two components

    vec2f xx(vec3f v) {
        return {v[0], v[0]};
    }

    vec2f xy(vec3f v) {
        return {v[0], v[1]};
    }

    vec2f xz(vec3f v) {
        return {v[0], v[2]};
    }

    vec2f yx(vec3f v) {
        return {v[1], v[0]};
    }

    vec2f yy(vec3f v) {
        return {v[1], v[1]};
    }

    vec2f yz(vec3f v) {
        return {v[1], v[2]};
    }

    vec2f zx(vec3f v) {
        return {v[2], v[0]};
    }

    vec2f zy(vec3f v) {
        return {v[2], v[1]};
    }

    vec2f zz(vec3f v) {
        return {v[2], v[2]};
    }

    // Three components

    vec3f xxx(vec3f v) {
        return {v[0], v[0], v[0]};
    }

    vec3f xxy(vec3f v) {
        return {v[0], v[0], v[1]};
    }

    vec3f xxz(vec3f v) {
        return {v[0], v[0], v[2]};
    }

    vec3f xyx(vec3f v) {
        return {v[0], v[1], v[0]};
    }

    vec3f xyy(vec3f v) {
        return {v[0], v[1], v[1]};
    }

    vec3f xyz(vec3f v) {
        return {v[0], v[1], v[2]};
    }

    vec3f xzx(vec3f v) {
        return {v[0], v[2], v[0]};
    }

    vec3f xzy(vec3f v) {
        return {v[0], v[2], v[1]};
    }

    vec3f xzz(vec3f v) {
        return {v[0], v[2], v[2]};
    }

    vec3f yxx(vec3f v) {
        return {v[1], v[0], v[0]};
    }

    vec3f yxy(vec3f v) {
        return {v[1], v[0], v[1]};
    }

    vec3f yxz(vec3f v) {
        return {v[1], v[0], v[2]};
    }

    vec3f yyx(vec3f v) {
        return {v[1], v[1], v[0]};
    }

    vec3f yyy(vec3f v) {
        return {v[1], v[1], v[1]};
    }

    vec3f yyz(vec3f v) {
        return {v[1], v[1], v[2]};
    }

    vec3f yzx(vec3f v) {
        return {v[1], v[2], v[0]};
    }

    vec3f yzy(vec3f v) {
        return {v[1], v[2], v[1]};
    }

    vec3f yzz(vec3f v) {
        return {v[1], v[2], v[2]};
    }

    vec3f zxx(vec3f v) {
        return {v[2], v[0], v[0]};
    }

    vec3f zxy(vec3f v) {
        return {v[2], v[0], v[1]};
    }

    vec3f zxz(vec3f v) {
        return {v[2], v[0], v[2]};
    }

    vec3f zyx(vec3f v) {
        return {v[2], v[1], v[0]};
    }

    vec3f zyy(vec3f v) {
        return {v[2], v[1], v[1]};
    }

    vec3f zyz(vec3f v) {
        return {v[2], v[1], v[2]};
    }

    vec3f zzx(vec3f v) {
        return {v[2], v[2], v[0]};
    }

    vec3f zzy(vec3f v) {
        return {v[2], v[2], v[1]};
    }

    vec3f zzz(vec3f v) {
        return {v[2], v[2], v[2]};
    }

}

#endif
