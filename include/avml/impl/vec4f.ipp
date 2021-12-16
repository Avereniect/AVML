#ifndef AVML_VEC4F_IPP
#define AVML_VEC4F_IPP

namespace avml {

    template<>
    class alignas(alignof(float) * 4) Vector4R<float> {
    public:

        using scalar = float;

        static constexpr unsigned width = 4;

        //=================================================
        // Creation functions
        //=================================================

        AVML_FINL static Vector4R read(const float* p) {
            return Vector4R{p[0], p[1], p[2], p[3]};
        }

        AVML_FINL static Vector4R read_aligned(const float* p) {
            return Vector4R{p[0], p[1], p[2], p[3]};
        }

        //=================================================
        // -ctors
        //=================================================

        explicit AVML_FINL Vector4R(float v):
            elements{v, v, v, v} {}

        AVML_FINL Vector4R(float x, float y, float z, float w):
            elements{x, y, z, w} {}

        AVML_FINL Vector4R(uvec4f v):
            elements{v[0], v[1], v[2], v[3]} {}

        AVML_FINL Vector4R(vec2f v, float z, float w):
            elements{v[0], v[1], z, w} {}

        AVML_FINL Vector4R(float x, vec2f v, float w):
            elements{x, v[0], v[1], w} {}

        AVML_FINL Vector4R(float x, float y, vec2f v):
            elements{x, y, v[0], v[1]} {}

        AVML_FINL Vector4R(vec2f v, vec2f u):
            elements{v[0], v[1], u[0], u[1]} {}

        AVML_FINL Vector4R(vec3f v, float w):
            elements{v[0], v[1], v[2], w} {}

        AVML_FINL Vector4R(float x, vec3f v):
            elements{x, v[0], v[1], v[2]} {}

        Vector4R() = default;
        Vector4R(const Vector4R&) = default;
        Vector4R(Vector4R&&) = default;
        ~Vector4R() = default;

        //=================================================
        // Assignment operators
        //=================================================

        Vector4R& operator=(const Vector4R&) = default;
        Vector4R& operator=(Vector4R&&) = default;

        //=================================================
        // Unary arithmetic operators
        //=================================================

        AVML_FINL Vector4R operator+() const {
            return *this;
        }

        AVML_FINL Vector4R operator-() const {
            return Vector4R{
                -elements[0],
                -elements[1],
                -elements[2],
                -elements[3]
            };
        }

        //=================================================
        // Arithmetic assignment operators
        //=================================================

        AVML_FINL Vector4R& operator+=(const Vector4R& rhs) {
            for (unsigned i = 0; i < width; ++i) {
                elements[i] += rhs[i];
            }
            return *this;
        }

        AVML_FINL Vector4R& operator-=(const Vector4R& rhs) {
            for (unsigned i = 0; i < width; ++i) {
                elements[i] -= rhs[i];
            }
            return *this;
        }

        AVML_FINL Vector4R& operator*=(const scalar rhs) {
            for (unsigned i = 0; i < width; ++i) {
                elements[i] *= rhs;
            }
            return *this;
        }

        AVML_FINL Vector4R& operator*=(const Vector4R rhs) {
            for (unsigned i = 0; i < width; ++i) {
                elements[i] *= rhs[i];
            }
            return *this;
        }

        AVML_FINL Vector4R& operator/=(const Vector4R rhs) {
            for (unsigned i = 0; i < width; ++i) {
                elements[i] /= rhs[i];
            }
            return *this;
        }

        AVML_FINL Vector4R& operator/=(const scalar rhs) {
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

        float elements[width] = {0.0f, 0.0f, 0.0f, 0.0f};

    };

    //=====================================================
    // Comparison operators
    //=====================================================

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

    //=====================================================
    // Arithmetic operators
    //=====================================================

    AVML_FINL vec4f operator+(vec4f lhs, vec4f rhs) {
        lhs += rhs;
        return lhs;
    }

    AVML_FINL vec4f operator-(vec4f lhs, vec4f rhs) {
        lhs -= rhs;
        return lhs;
    }

    AVML_FINL vec4f operator*(vec4f lhs, vec4f rhs) {
        lhs *= rhs;
        return lhs;
    }

    AVML_FINL vec4f operator*(vec4f lhs, float rhs) {
        lhs *= rhs;
        return lhs;
    }

    AVML_FINL vec4f operator*(float lhs, vec4f rhs) {
        rhs *= lhs;
        return rhs;
    }

    AVML_FINL vec4f operator/(vec4f lhs, float rhs) {
        lhs /= rhs;
        return lhs;
    }

    AVML_FINL vec4f operator/(vec4f lhs, vec4f rhs) {
        lhs /= rhs;
        return lhs;
    }

    //=====================================================
    // Vector math
    //=====================================================

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

    AVML_FINL uvec4f assume_normalized(vec4f v) {
        return uvec4f::read_aligned(v.data());
    }

    AVML_FINL uvec4f normalize(vec4f v) {
        v /= length(v);
        return assume_normalized(v);
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

    //=====================================================
    // Swizzling
    //=====================================================

    // Single component

    AVML_FINL float x(vec4f v) {
        return v[0];
    }

    AVML_FINL float y(vec4f v) {
        return v[1];
    }

    AVML_FINL float z(vec4f v) {
        return v[2];
    }

    AVML_FINL float w(vec4f v) {
        return v[3];
    }

    // Two components

    AVML_FINL vec2f xx(vec4f v) {
        return {v[0], v[0]};
    }

    AVML_FINL vec2f xy(vec4f v) {
        return {v[0], v[1]};
    }

    AVML_FINL vec2f xz(vec4f v) {
        return {v[0], v[2]};
    }

    AVML_FINL vec2f xw(vec4f v) {
        return {v[0], v[3]};
    }

    AVML_FINL vec2f yx(vec4f v) {
        return {v[1], v[0]};
    }

    AVML_FINL vec2f yy(vec4f v) {
        return {v[1], v[1]};
    }

    AVML_FINL vec2f yz(vec4f v) {
        return {v[1], v[2]};
    }

    AVML_FINL vec2f yw(vec4f v) {
        return {v[1], v[3]};
    }

    AVML_FINL vec2f zx(vec4f v) {
        return {v[2], v[0]};
    }

    AVML_FINL vec2f zy(vec4f v) {
        return {v[2], v[1]};
    }

    AVML_FINL vec2f zz(vec4f v) {
        return {v[2], v[2]};
    }

    AVML_FINL vec2f zw(vec4f v) {
        return {v[2], v[2]};
    }

    AVML_FINL vec2f wx(vec4f v) {
        return {v[3], v[0]};
    }

    AVML_FINL vec2f wy(vec4f v) {
        return {v[3], v[1]};
    }

    AVML_FINL vec2f wz(vec4f v) {
        return {v[3], v[2]};
    }

    AVML_FINL vec2f ww(vec4f v) {
        return {v[3], v[2]};
    }

    // Three component

    // Generated by
//    #include <iostream>
//
//    char index_to_char(unsigned x) {
//        switch (x) {
//            case 0: return 'x';
//            case 1: return 'y';
//            case 2: return 'z';
//            case 3: return 'w';
//        }
//
//        return 0;
//    }
//
//    int main() {
//        for (int i = 0; i < 4; ++i) {
//            for (int j = 0; j < 4; ++j) {
//                for (int k = 0; k < 4; ++k) {
//                    std::string code = "    vec3f ";
//
//                    code += index_to_char(i);
//                    code += index_to_char(j);
//                    code += index_to_char(k);
//
//                    code += "(vec4f v) {\n        return {";
//                    code += "v[" + std::to_string(i) + "], ";
//                    code += "v[" + std::to_string(j) + "], ";
//                    code += "v[" + std::to_string(k) + "]";
//
//                    code += "};\n    }\n";
//
//                    std::cout << code << std::endl;
//                }
//            }
//        }
//
//        return 0;
//    }


    AVML_FINL vec3f xxx(vec4f v) {
        return {v[0], v[0], v[0]};
    }

    AVML_FINL vec3f xxy(vec4f v) {
        return {v[0], v[0], v[1]};
    }

    AVML_FINL vec3f xxz(vec4f v) {
        return {v[0], v[0], v[2]};
    }

    AVML_FINL vec3f xxw(vec4f v) {
        return {v[0], v[0], v[3]};
    }

    AVML_FINL vec3f xyx(vec4f v) {
        return {v[0], v[1], v[0]};
    }

    AVML_FINL vec3f xyy(vec4f v) {
        return {v[0], v[1], v[1]};
    }

    AVML_FINL vec3f xyz(vec4f v) {
        return {v[0], v[1], v[2]};
    }

    AVML_FINL vec3f xyw(vec4f v) {
        return {v[0], v[1], v[3]};
    }

    AVML_FINL vec3f xzx(vec4f v) {
        return {v[0], v[2], v[0]};
    }

    AVML_FINL vec3f xzy(vec4f v) {
        return {v[0], v[2], v[1]};
    }

    AVML_FINL vec3f xzz(vec4f v) {
        return {v[0], v[2], v[2]};
    }

    AVML_FINL vec3f xzw(vec4f v) {
        return {v[0], v[2], v[3]};
    }

    AVML_FINL vec3f xwx(vec4f v) {
        return {v[0], v[3], v[0]};
    }

    AVML_FINL vec3f xwy(vec4f v) {
        return {v[0], v[3], v[1]};
    }

    AVML_FINL vec3f xwz(vec4f v) {
        return {v[0], v[3], v[2]};
    }

    AVML_FINL vec3f xww(vec4f v) {
        return {v[0], v[3], v[3]};
    }

    AVML_FINL vec3f yxx(vec4f v) {
        return {v[1], v[0], v[0]};
    }

    AVML_FINL vec3f yxy(vec4f v) {
        return {v[1], v[0], v[1]};
    }

    AVML_FINL vec3f yxz(vec4f v) {
        return {v[1], v[0], v[2]};
    }

    AVML_FINL vec3f yxw(vec4f v) {
        return {v[1], v[0], v[3]};
    }

    AVML_FINL vec3f yyx(vec4f v) {
        return {v[1], v[1], v[0]};
    }

    AVML_FINL vec3f yyy(vec4f v) {
        return {v[1], v[1], v[1]};
    }

    AVML_FINL vec3f yyz(vec4f v) {
        return {v[1], v[1], v[2]};
    }

    AVML_FINL vec3f yyw(vec4f v) {
        return {v[1], v[1], v[3]};
    }

    AVML_FINL vec3f yzx(vec4f v) {
        return {v[1], v[2], v[0]};
    }

    AVML_FINL vec3f yzy(vec4f v) {
        return {v[1], v[2], v[1]};
    }

    AVML_FINL vec3f yzz(vec4f v) {
        return {v[1], v[2], v[2]};
    }

    AVML_FINL vec3f yzw(vec4f v) {
        return {v[1], v[2], v[3]};
    }

    AVML_FINL vec3f ywx(vec4f v) {
        return {v[1], v[3], v[0]};
    }

    AVML_FINL vec3f ywy(vec4f v) {
        return {v[1], v[3], v[1]};
    }

    AVML_FINL vec3f ywz(vec4f v) {
        return {v[1], v[3], v[2]};
    }

    AVML_FINL vec3f yww(vec4f v) {
        return {v[1], v[3], v[3]};
    }

    AVML_FINL vec3f zxx(vec4f v) {
        return {v[2], v[0], v[0]};
    }

    AVML_FINL vec3f zxy(vec4f v) {
        return {v[2], v[0], v[1]};
    }

    AVML_FINL vec3f zxz(vec4f v) {
        return {v[2], v[0], v[2]};
    }

    AVML_FINL vec3f zxw(vec4f v) {
        return {v[2], v[0], v[3]};
    }

    AVML_FINL vec3f zyx(vec4f v) {
        return {v[2], v[1], v[0]};
    }

    AVML_FINL vec3f zyy(vec4f v) {
        return {v[2], v[1], v[1]};
    }

    AVML_FINL vec3f zyz(vec4f v) {
        return {v[2], v[1], v[2]};
    }

    AVML_FINL vec3f zyw(vec4f v) {
        return {v[2], v[1], v[3]};
    }

    AVML_FINL vec3f zzx(vec4f v) {
        return {v[2], v[2], v[0]};
    }

    AVML_FINL vec3f zzy(vec4f v) {
        return {v[2], v[2], v[1]};
    }

    AVML_FINL vec3f zzz(vec4f v) {
        return {v[2], v[2], v[2]};
    }

    AVML_FINL vec3f zzw(vec4f v) {
        return {v[2], v[2], v[3]};
    }

    AVML_FINL vec3f zwx(vec4f v) {
        return {v[2], v[3], v[0]};
    }

    AVML_FINL vec3f zwy(vec4f v) {
        return {v[2], v[3], v[1]};
    }

    AVML_FINL vec3f zwz(vec4f v) {
        return {v[2], v[3], v[2]};
    }

    AVML_FINL vec3f zww(vec4f v) {
        return {v[2], v[3], v[3]};
    }

    AVML_FINL vec3f wxx(vec4f v) {
        return {v[3], v[0], v[0]};
    }

    AVML_FINL vec3f wxy(vec4f v) {
        return {v[3], v[0], v[1]};
    }

    AVML_FINL vec3f wxz(vec4f v) {
        return {v[3], v[0], v[2]};
    }

    AVML_FINL vec3f wxw(vec4f v) {
        return {v[3], v[0], v[3]};
    }

    AVML_FINL vec3f wyx(vec4f v) {
        return {v[3], v[1], v[0]};
    }

    AVML_FINL vec3f wyy(vec4f v) {
        return {v[3], v[1], v[1]};
    }

    AVML_FINL vec3f wyz(vec4f v) {
        return {v[3], v[1], v[2]};
    }

    AVML_FINL vec3f wyw(vec4f v) {
        return {v[3], v[1], v[3]};
    }

    AVML_FINL vec3f wzx(vec4f v) {
        return {v[3], v[2], v[0]};
    }

    AVML_FINL vec3f wzy(vec4f v) {
        return {v[3], v[2], v[1]};
    }

    AVML_FINL vec3f wzz(vec4f v) {
        return {v[3], v[2], v[2]};
    }

    AVML_FINL vec3f wzw(vec4f v) {
        return {v[3], v[2], v[3]};
    }

    AVML_FINL vec3f wwx(vec4f v) {
        return {v[3], v[3], v[0]};
    }

    AVML_FINL vec3f wwy(vec4f v) {
        return {v[3], v[3], v[1]};
    }

    AVML_FINL vec3f wwz(vec4f v) {
        return {v[3], v[3], v[2]};
    }

    AVML_FINL vec3f www(vec4f v) {
        return {v[3], v[3], v[3]};
    }

    // Four component

    //Generated by:
    //#include <iostream>
    //
    //char index_to_char(unsigned x) {
    //    switch (x) {
    //        case 0: return 'x';
    //        case 1: return 'y';
    //        case 2: return 'z';
    //        case 3: return 'w';
    //    }
    //
    //    return 0;
    //}
    //
    //int main() {
    //    for (int i = 0; i < 4; ++i) {
    //        for (int j = 0; j < 4; ++j) {
    //            for (int k = 0; k < 4; ++k) {
    //                for (int l = 0; l < 4; ++l) {
    //                    std::string code = "    vec4f ";
    //
    //                    code += index_to_char(i);
    //                    code += index_to_char(j);
    //                    code += index_to_char(k);
    //                    code += index_to_char(l);
    //
    //                    code += "(vec4f v) {\n        return {";
    //                    code += "v[" + std::to_string(i) + "], ";
    //                    code += "v[" + std::to_string(j) + "], ";
    //                    code += "v[" + std::to_string(k) + "], ";
    //                    code += "v[" + std::to_string(l) + "]";
    //
    //                    code += "};\n    }\n";
    //
    //                    std::cout << code << std::endl;
    //                }
    //            }
    //        }
    //    }
    //
    //    return 0;
    //}

    AVML_FINL vec4f xxxx(vec4f v) {
        return {v[0], v[0], v[0], v[0]};
    }

    AVML_FINL vec4f xxxy(vec4f v) {
        return {v[0], v[0], v[0], v[1]};
    }

    AVML_FINL vec4f xxxz(vec4f v) {
        return {v[0], v[0], v[0], v[2]};
    }

    AVML_FINL vec4f xxxw(vec4f v) {
        return {v[0], v[0], v[0], v[3]};
    }

    AVML_FINL vec4f xxyx(vec4f v) {
        return {v[0], v[0], v[1], v[0]};
    }

    AVML_FINL vec4f xxyy(vec4f v) {
        return {v[0], v[0], v[1], v[1]};
    }

    AVML_FINL vec4f xxyz(vec4f v) {
        return {v[0], v[0], v[1], v[2]};
    }

    AVML_FINL vec4f xxyw(vec4f v) {
        return {v[0], v[0], v[1], v[3]};
    }

    AVML_FINL vec4f xxzx(vec4f v) {
        return {v[0], v[0], v[2], v[0]};
    }

    AVML_FINL vec4f xxzy(vec4f v) {
        return {v[0], v[0], v[2], v[1]};
    }

    AVML_FINL vec4f xxzz(vec4f v) {
        return {v[0], v[0], v[2], v[2]};
    }

    AVML_FINL vec4f xxzw(vec4f v) {
        return {v[0], v[0], v[2], v[3]};
    }

    AVML_FINL vec4f xxwx(vec4f v) {
        return {v[0], v[0], v[3], v[0]};
    }

    AVML_FINL vec4f xxwy(vec4f v) {
        return {v[0], v[0], v[3], v[1]};
    }

    AVML_FINL vec4f xxwz(vec4f v) {
        return {v[0], v[0], v[3], v[2]};
    }

    AVML_FINL vec4f xxww(vec4f v) {
        return {v[0], v[0], v[3], v[3]};
    }

    AVML_FINL vec4f xyxx(vec4f v) {
        return {v[0], v[1], v[0], v[0]};
    }

    AVML_FINL vec4f xyxy(vec4f v) {
        return {v[0], v[1], v[0], v[1]};
    }

    AVML_FINL vec4f xyxz(vec4f v) {
        return {v[0], v[1], v[0], v[2]};
    }

    AVML_FINL vec4f xyxw(vec4f v) {
        return {v[0], v[1], v[0], v[3]};
    }

    AVML_FINL vec4f xyyx(vec4f v) {
        return {v[0], v[1], v[1], v[0]};
    }

    AVML_FINL vec4f xyyy(vec4f v) {
        return {v[0], v[1], v[1], v[1]};
    }

    AVML_FINL vec4f xyyz(vec4f v) {
        return {v[0], v[1], v[1], v[2]};
    }

    AVML_FINL vec4f xyyw(vec4f v) {
        return {v[0], v[1], v[1], v[3]};
    }

    AVML_FINL vec4f xyzx(vec4f v) {
        return {v[0], v[1], v[2], v[0]};
    }

    AVML_FINL vec4f xyzy(vec4f v) {
        return {v[0], v[1], v[2], v[1]};
    }

    AVML_FINL vec4f xyzz(vec4f v) {
        return {v[0], v[1], v[2], v[2]};
    }

    AVML_FINL vec4f xyzw(vec4f v) {
        return {v[0], v[1], v[2], v[3]};
    }

    AVML_FINL vec4f xywx(vec4f v) {
        return {v[0], v[1], v[3], v[0]};
    }

    AVML_FINL vec4f xywy(vec4f v) {
        return {v[0], v[1], v[3], v[1]};
    }

    AVML_FINL vec4f xywz(vec4f v) {
        return {v[0], v[1], v[3], v[2]};
    }

    AVML_FINL vec4f xyww(vec4f v) {
        return {v[0], v[1], v[3], v[3]};
    }

    AVML_FINL vec4f xzxx(vec4f v) {
        return {v[0], v[2], v[0], v[0]};
    }

    AVML_FINL vec4f xzxy(vec4f v) {
        return {v[0], v[2], v[0], v[1]};
    }

    AVML_FINL vec4f xzxz(vec4f v) {
        return {v[0], v[2], v[0], v[2]};
    }

    AVML_FINL vec4f xzxw(vec4f v) {
        return {v[0], v[2], v[0], v[3]};
    }

    AVML_FINL vec4f xzyx(vec4f v) {
        return {v[0], v[2], v[1], v[0]};
    }

    AVML_FINL vec4f xzyy(vec4f v) {
        return {v[0], v[2], v[1], v[1]};
    }

    AVML_FINL vec4f xzyz(vec4f v) {
        return {v[0], v[2], v[1], v[2]};
    }

    AVML_FINL vec4f xzyw(vec4f v) {
        return {v[0], v[2], v[1], v[3]};
    }

    AVML_FINL vec4f xzzx(vec4f v) {
        return {v[0], v[2], v[2], v[0]};
    }

    AVML_FINL vec4f xzzy(vec4f v) {
        return {v[0], v[2], v[2], v[1]};
    }

    AVML_FINL vec4f xzzz(vec4f v) {
        return {v[0], v[2], v[2], v[2]};
    }

    AVML_FINL vec4f xzzw(vec4f v) {
        return {v[0], v[2], v[2], v[3]};
    }

    AVML_FINL vec4f xzwx(vec4f v) {
        return {v[0], v[2], v[3], v[0]};
    }

    AVML_FINL vec4f xzwy(vec4f v) {
        return {v[0], v[2], v[3], v[1]};
    }

    AVML_FINL vec4f xzwz(vec4f v) {
        return {v[0], v[2], v[3], v[2]};
    }

    AVML_FINL vec4f xzww(vec4f v) {
        return {v[0], v[2], v[3], v[3]};
    }

    AVML_FINL vec4f xwxx(vec4f v) {
        return {v[0], v[3], v[0], v[0]};
    }

    AVML_FINL vec4f xwxy(vec4f v) {
        return {v[0], v[3], v[0], v[1]};
    }

    AVML_FINL vec4f xwxz(vec4f v) {
        return {v[0], v[3], v[0], v[2]};
    }

    AVML_FINL vec4f xwxw(vec4f v) {
        return {v[0], v[3], v[0], v[3]};
    }

    AVML_FINL vec4f xwyx(vec4f v) {
        return {v[0], v[3], v[1], v[0]};
    }

    AVML_FINL vec4f xwyy(vec4f v) {
        return {v[0], v[3], v[1], v[1]};
    }

    AVML_FINL vec4f xwyz(vec4f v) {
        return {v[0], v[3], v[1], v[2]};
    }

    AVML_FINL vec4f xwyw(vec4f v) {
        return {v[0], v[3], v[1], v[3]};
    }

    AVML_FINL vec4f xwzx(vec4f v) {
        return {v[0], v[3], v[2], v[0]};
    }

    AVML_FINL vec4f xwzy(vec4f v) {
        return {v[0], v[3], v[2], v[1]};
    }

    AVML_FINL vec4f xwzz(vec4f v) {
        return {v[0], v[3], v[2], v[2]};
    }

    AVML_FINL vec4f xwzw(vec4f v) {
        return {v[0], v[3], v[2], v[3]};
    }

    AVML_FINL vec4f xwwx(vec4f v) {
        return {v[0], v[3], v[3], v[0]};
    }

    AVML_FINL vec4f xwwy(vec4f v) {
        return {v[0], v[3], v[3], v[1]};
    }

    AVML_FINL vec4f xwwz(vec4f v) {
        return {v[0], v[3], v[3], v[2]};
    }

    AVML_FINL vec4f xwww(vec4f v) {
        return {v[0], v[3], v[3], v[3]};
    }

    AVML_FINL vec4f yxxx(vec4f v) {
        return {v[1], v[0], v[0], v[0]};
    }

    AVML_FINL vec4f yxxy(vec4f v) {
        return {v[1], v[0], v[0], v[1]};
    }

    AVML_FINL vec4f yxxz(vec4f v) {
        return {v[1], v[0], v[0], v[2]};
    }

    AVML_FINL vec4f yxxw(vec4f v) {
        return {v[1], v[0], v[0], v[3]};
    }

    AVML_FINL vec4f yxyx(vec4f v) {
        return {v[1], v[0], v[1], v[0]};
    }

    AVML_FINL vec4f yxyy(vec4f v) {
        return {v[1], v[0], v[1], v[1]};
    }

    AVML_FINL vec4f yxyz(vec4f v) {
        return {v[1], v[0], v[1], v[2]};
    }

    AVML_FINL vec4f yxyw(vec4f v) {
        return {v[1], v[0], v[1], v[3]};
    }

    AVML_FINL vec4f yxzx(vec4f v) {
        return {v[1], v[0], v[2], v[0]};
    }

    AVML_FINL vec4f yxzy(vec4f v) {
        return {v[1], v[0], v[2], v[1]};
    }

    AVML_FINL vec4f yxzz(vec4f v) {
        return {v[1], v[0], v[2], v[2]};
    }

    AVML_FINL vec4f yxzw(vec4f v) {
        return {v[1], v[0], v[2], v[3]};
    }

    AVML_FINL vec4f yxwx(vec4f v) {
        return {v[1], v[0], v[3], v[0]};
    }

    AVML_FINL vec4f yxwy(vec4f v) {
        return {v[1], v[0], v[3], v[1]};
    }

    AVML_FINL vec4f yxwz(vec4f v) {
        return {v[1], v[0], v[3], v[2]};
    }

    AVML_FINL vec4f yxww(vec4f v) {
        return {v[1], v[0], v[3], v[3]};
    }

    AVML_FINL vec4f yyxx(vec4f v) {
        return {v[1], v[1], v[0], v[0]};
    }

    AVML_FINL vec4f yyxy(vec4f v) {
        return {v[1], v[1], v[0], v[1]};
    }

    AVML_FINL vec4f yyxz(vec4f v) {
        return {v[1], v[1], v[0], v[2]};
    }

    AVML_FINL vec4f yyxw(vec4f v) {
        return {v[1], v[1], v[0], v[3]};
    }

    AVML_FINL vec4f yyyx(vec4f v) {
        return {v[1], v[1], v[1], v[0]};
    }

    AVML_FINL vec4f yyyy(vec4f v) {
        return {v[1], v[1], v[1], v[1]};
    }

    AVML_FINL vec4f yyyz(vec4f v) {
        return {v[1], v[1], v[1], v[2]};
    }

    AVML_FINL vec4f yyyw(vec4f v) {
        return {v[1], v[1], v[1], v[3]};
    }

    AVML_FINL vec4f yyzx(vec4f v) {
        return {v[1], v[1], v[2], v[0]};
    }

    AVML_FINL vec4f yyzy(vec4f v) {
        return {v[1], v[1], v[2], v[1]};
    }

    AVML_FINL vec4f yyzz(vec4f v) {
        return {v[1], v[1], v[2], v[2]};
    }

    AVML_FINL vec4f yyzw(vec4f v) {
        return {v[1], v[1], v[2], v[3]};
    }

    AVML_FINL vec4f yywx(vec4f v) {
        return {v[1], v[1], v[3], v[0]};
    }

    AVML_FINL vec4f yywy(vec4f v) {
        return {v[1], v[1], v[3], v[1]};
    }

    AVML_FINL vec4f yywz(vec4f v) {
        return {v[1], v[1], v[3], v[2]};
    }

    AVML_FINL vec4f yyww(vec4f v) {
        return {v[1], v[1], v[3], v[3]};
    }

    AVML_FINL vec4f yzxx(vec4f v) {
        return {v[1], v[2], v[0], v[0]};
    }

    AVML_FINL vec4f yzxy(vec4f v) {
        return {v[1], v[2], v[0], v[1]};
    }

    AVML_FINL vec4f yzxz(vec4f v) {
        return {v[1], v[2], v[0], v[2]};
    }

    AVML_FINL vec4f yzxw(vec4f v) {
        return {v[1], v[2], v[0], v[3]};
    }

    AVML_FINL vec4f yzyx(vec4f v) {
        return {v[1], v[2], v[1], v[0]};
    }

    AVML_FINL vec4f yzyy(vec4f v) {
        return {v[1], v[2], v[1], v[1]};
    }

    AVML_FINL vec4f yzyz(vec4f v) {
        return {v[1], v[2], v[1], v[2]};
    }

    AVML_FINL vec4f yzyw(vec4f v) {
        return {v[1], v[2], v[1], v[3]};
    }

    AVML_FINL vec4f yzzx(vec4f v) {
        return {v[1], v[2], v[2], v[0]};
    }

    AVML_FINL vec4f yzzy(vec4f v) {
        return {v[1], v[2], v[2], v[1]};
    }

    AVML_FINL vec4f yzzz(vec4f v) {
        return {v[1], v[2], v[2], v[2]};
    }

    AVML_FINL vec4f yzzw(vec4f v) {
        return {v[1], v[2], v[2], v[3]};
    }

    AVML_FINL vec4f yzwx(vec4f v) {
        return {v[1], v[2], v[3], v[0]};
    }

    AVML_FINL vec4f yzwy(vec4f v) {
        return {v[1], v[2], v[3], v[1]};
    }

    AVML_FINL vec4f yzwz(vec4f v) {
        return {v[1], v[2], v[3], v[2]};
    }

    AVML_FINL vec4f yzww(vec4f v) {
        return {v[1], v[2], v[3], v[3]};
    }

    AVML_FINL vec4f ywxx(vec4f v) {
        return {v[1], v[3], v[0], v[0]};
    }

    AVML_FINL vec4f ywxy(vec4f v) {
        return {v[1], v[3], v[0], v[1]};
    }

    AVML_FINL vec4f ywxz(vec4f v) {
        return {v[1], v[3], v[0], v[2]};
    }

    AVML_FINL vec4f ywxw(vec4f v) {
        return {v[1], v[3], v[0], v[3]};
    }

    AVML_FINL vec4f ywyx(vec4f v) {
        return {v[1], v[3], v[1], v[0]};
    }

    AVML_FINL vec4f ywyy(vec4f v) {
        return {v[1], v[3], v[1], v[1]};
    }

    AVML_FINL vec4f ywyz(vec4f v) {
        return {v[1], v[3], v[1], v[2]};
    }

    AVML_FINL vec4f ywyw(vec4f v) {
        return {v[1], v[3], v[1], v[3]};
    }

    AVML_FINL vec4f ywzx(vec4f v) {
        return {v[1], v[3], v[2], v[0]};
    }

    AVML_FINL vec4f ywzy(vec4f v) {
        return {v[1], v[3], v[2], v[1]};
    }

    AVML_FINL vec4f ywzz(vec4f v) {
        return {v[1], v[3], v[2], v[2]};
    }

    AVML_FINL vec4f ywzw(vec4f v) {
        return {v[1], v[3], v[2], v[3]};
    }

    AVML_FINL vec4f ywwx(vec4f v) {
        return {v[1], v[3], v[3], v[0]};
    }

    AVML_FINL vec4f ywwy(vec4f v) {
        return {v[1], v[3], v[3], v[1]};
    }

    AVML_FINL vec4f ywwz(vec4f v) {
        return {v[1], v[3], v[3], v[2]};
    }

    AVML_FINL vec4f ywww(vec4f v) {
        return {v[1], v[3], v[3], v[3]};
    }

    AVML_FINL vec4f zxxx(vec4f v) {
        return {v[2], v[0], v[0], v[0]};
    }

    AVML_FINL vec4f zxxy(vec4f v) {
        return {v[2], v[0], v[0], v[1]};
    }

    AVML_FINL vec4f zxxz(vec4f v) {
        return {v[2], v[0], v[0], v[2]};
    }

    AVML_FINL vec4f zxxw(vec4f v) {
        return {v[2], v[0], v[0], v[3]};
    }

    AVML_FINL vec4f zxyx(vec4f v) {
        return {v[2], v[0], v[1], v[0]};
    }

    AVML_FINL vec4f zxyy(vec4f v) {
        return {v[2], v[0], v[1], v[1]};
    }

    AVML_FINL vec4f zxyz(vec4f v) {
        return {v[2], v[0], v[1], v[2]};
    }

    AVML_FINL vec4f zxyw(vec4f v) {
        return {v[2], v[0], v[1], v[3]};
    }

    AVML_FINL vec4f zxzx(vec4f v) {
        return {v[2], v[0], v[2], v[0]};
    }

    AVML_FINL vec4f zxzy(vec4f v) {
        return {v[2], v[0], v[2], v[1]};
    }

    AVML_FINL vec4f zxzz(vec4f v) {
        return {v[2], v[0], v[2], v[2]};
    }

    AVML_FINL vec4f zxzw(vec4f v) {
        return {v[2], v[0], v[2], v[3]};
    }

    AVML_FINL vec4f zxwx(vec4f v) {
        return {v[2], v[0], v[3], v[0]};
    }

    AVML_FINL vec4f zxwy(vec4f v) {
        return {v[2], v[0], v[3], v[1]};
    }

    AVML_FINL vec4f zxwz(vec4f v) {
        return {v[2], v[0], v[3], v[2]};
    }

    AVML_FINL vec4f zxww(vec4f v) {
        return {v[2], v[0], v[3], v[3]};
    }

    AVML_FINL vec4f zyxx(vec4f v) {
        return {v[2], v[1], v[0], v[0]};
    }

    AVML_FINL vec4f zyxy(vec4f v) {
        return {v[2], v[1], v[0], v[1]};
    }

    AVML_FINL vec4f zyxz(vec4f v) {
        return {v[2], v[1], v[0], v[2]};
    }

    AVML_FINL vec4f zyxw(vec4f v) {
        return {v[2], v[1], v[0], v[3]};
    }

    AVML_FINL vec4f zyyx(vec4f v) {
        return {v[2], v[1], v[1], v[0]};
    }

    AVML_FINL vec4f zyyy(vec4f v) {
        return {v[2], v[1], v[1], v[1]};
    }

    AVML_FINL vec4f zyyz(vec4f v) {
        return {v[2], v[1], v[1], v[2]};
    }

    AVML_FINL vec4f zyyw(vec4f v) {
        return {v[2], v[1], v[1], v[3]};
    }

    AVML_FINL vec4f zyzx(vec4f v) {
        return {v[2], v[1], v[2], v[0]};
    }

    AVML_FINL vec4f zyzy(vec4f v) {
        return {v[2], v[1], v[2], v[1]};
    }

    AVML_FINL vec4f zyzz(vec4f v) {
        return {v[2], v[1], v[2], v[2]};
    }

    AVML_FINL vec4f zyzw(vec4f v) {
        return {v[2], v[1], v[2], v[3]};
    }

    AVML_FINL vec4f zywx(vec4f v) {
        return {v[2], v[1], v[3], v[0]};
    }

    AVML_FINL vec4f zywy(vec4f v) {
        return {v[2], v[1], v[3], v[1]};
    }

    AVML_FINL vec4f zywz(vec4f v) {
        return {v[2], v[1], v[3], v[2]};
    }

    AVML_FINL vec4f zyww(vec4f v) {
        return {v[2], v[1], v[3], v[3]};
    }

    AVML_FINL vec4f zzxx(vec4f v) {
        return {v[2], v[2], v[0], v[0]};
    }

    AVML_FINL vec4f zzxy(vec4f v) {
        return {v[2], v[2], v[0], v[1]};
    }

    AVML_FINL vec4f zzxz(vec4f v) {
        return {v[2], v[2], v[0], v[2]};
    }

    AVML_FINL vec4f zzxw(vec4f v) {
        return {v[2], v[2], v[0], v[3]};
    }

    AVML_FINL vec4f zzyx(vec4f v) {
        return {v[2], v[2], v[1], v[0]};
    }

    AVML_FINL vec4f zzyy(vec4f v) {
        return {v[2], v[2], v[1], v[1]};
    }

    AVML_FINL vec4f zzyz(vec4f v) {
        return {v[2], v[2], v[1], v[2]};
    }

    AVML_FINL vec4f zzyw(vec4f v) {
        return {v[2], v[2], v[1], v[3]};
    }

    AVML_FINL vec4f zzzx(vec4f v) {
        return {v[2], v[2], v[2], v[0]};
    }

    AVML_FINL vec4f zzzy(vec4f v) {
        return {v[2], v[2], v[2], v[1]};
    }

    AVML_FINL vec4f zzzz(vec4f v) {
        return {v[2], v[2], v[2], v[2]};
    }

    AVML_FINL vec4f zzzw(vec4f v) {
        return {v[2], v[2], v[2], v[3]};
    }

    AVML_FINL vec4f zzwx(vec4f v) {
        return {v[2], v[2], v[3], v[0]};
    }

    AVML_FINL vec4f zzwy(vec4f v) {
        return {v[2], v[2], v[3], v[1]};
    }

    AVML_FINL vec4f zzwz(vec4f v) {
        return {v[2], v[2], v[3], v[2]};
    }

    AVML_FINL vec4f zzww(vec4f v) {
        return {v[2], v[2], v[3], v[3]};
    }

    AVML_FINL vec4f zwxx(vec4f v) {
        return {v[2], v[3], v[0], v[0]};
    }

    AVML_FINL vec4f zwxy(vec4f v) {
        return {v[2], v[3], v[0], v[1]};
    }

    AVML_FINL vec4f zwxz(vec4f v) {
        return {v[2], v[3], v[0], v[2]};
    }

    AVML_FINL vec4f zwxw(vec4f v) {
        return {v[2], v[3], v[0], v[3]};
    }

    AVML_FINL vec4f zwyx(vec4f v) {
        return {v[2], v[3], v[1], v[0]};
    }

    AVML_FINL vec4f zwyy(vec4f v) {
        return {v[2], v[3], v[1], v[1]};
    }

    AVML_FINL vec4f zwyz(vec4f v) {
        return {v[2], v[3], v[1], v[2]};
    }

    AVML_FINL vec4f zwyw(vec4f v) {
        return {v[2], v[3], v[1], v[3]};
    }

    AVML_FINL vec4f zwzx(vec4f v) {
        return {v[2], v[3], v[2], v[0]};
    }

    AVML_FINL vec4f zwzy(vec4f v) {
        return {v[2], v[3], v[2], v[1]};
    }

    AVML_FINL vec4f zwzz(vec4f v) {
        return {v[2], v[3], v[2], v[2]};
    }

    AVML_FINL vec4f zwzw(vec4f v) {
        return {v[2], v[3], v[2], v[3]};
    }

    AVML_FINL vec4f zwwx(vec4f v) {
        return {v[2], v[3], v[3], v[0]};
    }

    AVML_FINL vec4f zwwy(vec4f v) {
        return {v[2], v[3], v[3], v[1]};
    }

    AVML_FINL vec4f zwwz(vec4f v) {
        return {v[2], v[3], v[3], v[2]};
    }

    AVML_FINL vec4f zwww(vec4f v) {
        return {v[2], v[3], v[3], v[3]};
    }

    AVML_FINL vec4f wxxx(vec4f v) {
        return {v[3], v[0], v[0], v[0]};
    }

    AVML_FINL vec4f wxxy(vec4f v) {
        return {v[3], v[0], v[0], v[1]};
    }

    AVML_FINL vec4f wxxz(vec4f v) {
        return {v[3], v[0], v[0], v[2]};
    }

    AVML_FINL vec4f wxxw(vec4f v) {
        return {v[3], v[0], v[0], v[3]};
    }

    AVML_FINL vec4f wxyx(vec4f v) {
        return {v[3], v[0], v[1], v[0]};
    }

    AVML_FINL vec4f wxyy(vec4f v) {
        return {v[3], v[0], v[1], v[1]};
    }

    AVML_FINL vec4f wxyz(vec4f v) {
        return {v[3], v[0], v[1], v[2]};
    }

    AVML_FINL vec4f wxyw(vec4f v) {
        return {v[3], v[0], v[1], v[3]};
    }

    AVML_FINL vec4f wxzx(vec4f v) {
        return {v[3], v[0], v[2], v[0]};
    }

    AVML_FINL vec4f wxzy(vec4f v) {
        return {v[3], v[0], v[2], v[1]};
    }

    AVML_FINL vec4f wxzz(vec4f v) {
        return {v[3], v[0], v[2], v[2]};
    }

    AVML_FINL vec4f wxzw(vec4f v) {
        return {v[3], v[0], v[2], v[3]};
    }

    AVML_FINL vec4f wxwx(vec4f v) {
        return {v[3], v[0], v[3], v[0]};
    }

    AVML_FINL vec4f wxwy(vec4f v) {
        return {v[3], v[0], v[3], v[1]};
    }

    AVML_FINL vec4f wxwz(vec4f v) {
        return {v[3], v[0], v[3], v[2]};
    }

    AVML_FINL vec4f wxww(vec4f v) {
        return {v[3], v[0], v[3], v[3]};
    }

    AVML_FINL vec4f wyxx(vec4f v) {
        return {v[3], v[1], v[0], v[0]};
    }

    AVML_FINL vec4f wyxy(vec4f v) {
        return {v[3], v[1], v[0], v[1]};
    }

    AVML_FINL vec4f wyxz(vec4f v) {
        return {v[3], v[1], v[0], v[2]};
    }

    AVML_FINL vec4f wyxw(vec4f v) {
        return {v[3], v[1], v[0], v[3]};
    }

    AVML_FINL vec4f wyyx(vec4f v) {
        return {v[3], v[1], v[1], v[0]};
    }

    AVML_FINL vec4f wyyy(vec4f v) {
        return {v[3], v[1], v[1], v[1]};
    }

    AVML_FINL vec4f wyyz(vec4f v) {
        return {v[3], v[1], v[1], v[2]};
    }

    AVML_FINL vec4f wyyw(vec4f v) {
        return {v[3], v[1], v[1], v[3]};
    }

    AVML_FINL vec4f wyzx(vec4f v) {
        return {v[3], v[1], v[2], v[0]};
    }

    AVML_FINL vec4f wyzy(vec4f v) {
        return {v[3], v[1], v[2], v[1]};
    }

    AVML_FINL vec4f wyzz(vec4f v) {
        return {v[3], v[1], v[2], v[2]};
    }

    AVML_FINL vec4f wyzw(vec4f v) {
        return {v[3], v[1], v[2], v[3]};
    }

    AVML_FINL vec4f wywx(vec4f v) {
        return {v[3], v[1], v[3], v[0]};
    }

    AVML_FINL vec4f wywy(vec4f v) {
        return {v[3], v[1], v[3], v[1]};
    }

    AVML_FINL vec4f wywz(vec4f v) {
        return {v[3], v[1], v[3], v[2]};
    }

    AVML_FINL vec4f wyww(vec4f v) {
        return {v[3], v[1], v[3], v[3]};
    }

    AVML_FINL vec4f wzxx(vec4f v) {
        return {v[3], v[2], v[0], v[0]};
    }

    AVML_FINL vec4f wzxy(vec4f v) {
        return {v[3], v[2], v[0], v[1]};
    }

    AVML_FINL vec4f wzxz(vec4f v) {
        return {v[3], v[2], v[0], v[2]};
    }

    AVML_FINL vec4f wzxw(vec4f v) {
        return {v[3], v[2], v[0], v[3]};
    }

    AVML_FINL vec4f wzyx(vec4f v) {
        return {v[3], v[2], v[1], v[0]};
    }

    AVML_FINL vec4f wzyy(vec4f v) {
        return {v[3], v[2], v[1], v[1]};
    }

    AVML_FINL vec4f wzyz(vec4f v) {
        return {v[3], v[2], v[1], v[2]};
    }

    AVML_FINL vec4f wzyw(vec4f v) {
        return {v[3], v[2], v[1], v[3]};
    }

    AVML_FINL vec4f wzzx(vec4f v) {
        return {v[3], v[2], v[2], v[0]};
    }

    AVML_FINL vec4f wzzy(vec4f v) {
        return {v[3], v[2], v[2], v[1]};
    }

    AVML_FINL vec4f wzzz(vec4f v) {
        return {v[3], v[2], v[2], v[2]};
    }

    AVML_FINL vec4f wzzw(vec4f v) {
        return {v[3], v[2], v[2], v[3]};
    }

    AVML_FINL vec4f wzwx(vec4f v) {
        return {v[3], v[2], v[3], v[0]};
    }

    AVML_FINL vec4f wzwy(vec4f v) {
        return {v[3], v[2], v[3], v[1]};
    }

    AVML_FINL vec4f wzwz(vec4f v) {
        return {v[3], v[2], v[3], v[2]};
    }

    AVML_FINL vec4f wzww(vec4f v) {
        return {v[3], v[2], v[3], v[3]};
    }

    AVML_FINL vec4f wwxx(vec4f v) {
        return {v[3], v[3], v[0], v[0]};
    }

    AVML_FINL vec4f wwxy(vec4f v) {
        return {v[3], v[3], v[0], v[1]};
    }

    AVML_FINL vec4f wwxz(vec4f v) {
        return {v[3], v[3], v[0], v[2]};
    }

    AVML_FINL vec4f wwxw(vec4f v) {
        return {v[3], v[3], v[0], v[3]};
    }

    AVML_FINL vec4f wwyx(vec4f v) {
        return {v[3], v[3], v[1], v[0]};
    }

    AVML_FINL vec4f wwyy(vec4f v) {
        return {v[3], v[3], v[1], v[1]};
    }

    AVML_FINL vec4f wwyz(vec4f v) {
        return {v[3], v[3], v[1], v[2]};
    }

    AVML_FINL vec4f wwyw(vec4f v) {
        return {v[3], v[3], v[1], v[3]};
    }

    AVML_FINL vec4f wwzx(vec4f v) {
        return {v[3], v[3], v[2], v[0]};
    }

    AVML_FINL vec4f wwzy(vec4f v) {
        return {v[3], v[3], v[2], v[1]};
    }

    AVML_FINL vec4f wwzz(vec4f v) {
        return {v[3], v[3], v[2], v[2]};
    }

    AVML_FINL vec4f wwzw(vec4f v) {
        return {v[3], v[3], v[2], v[3]};
    }

    AVML_FINL vec4f wwwx(vec4f v) {
        return {v[3], v[3], v[3], v[0]};
    }

    AVML_FINL vec4f wwwy(vec4f v) {
        return {v[3], v[3], v[3], v[1]};
    }

    AVML_FINL vec4f wwwz(vec4f v) {
        return {v[3], v[3], v[3], v[2]};
    }

    AVML_FINL vec4f wwww(vec4f v) {
        return {v[3], v[3], v[3], v[3]};
    }

}

#endif
