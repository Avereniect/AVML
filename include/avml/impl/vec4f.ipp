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

        AVML_FINL Vector4R(Unit_vector4R<float> v):
            elements{v[0], v[1], v[2], v[3]} {}

        AVML_FINL Vector4R(Vector2R<float> v, float z, float w):
            elements{v[0], v[1], z, w} {}

        AVML_FINL Vector4R(float x, Vector2R<float> v, float w):
            elements{x, v[0], v[1], w} {}

        AVML_FINL Vector4R(float x, float y, Vector2R<float> v):
            elements{x, y, v[0], v[1]} {}

        AVML_FINL Vector4R(Vector2R<float> v, Vector2R<float> u):
            elements{v[0], v[1], u[0], u[1]} {}

        AVML_FINL Vector4R(Vector3R<float> v, float w):
            elements{v[0], v[1], v[2], w} {}

        AVML_FINL Vector4R(float x, Vector3R<float> v):
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

        float elements[width];

    };

    //=====================================================
    // Comparison operators
    //=====================================================

    AVML_FINL bool operator==(Vector4R<float> lhs, Vector4R<float> rhs) {
        return
            (lhs[0] == rhs[0]) &&
            (lhs[1] == rhs[1]) &&
            (lhs[2] == rhs[2]) &&
            (lhs[3] == rhs[3]);
    }

    AVML_FINL bool operator!=(Vector4R<float> lhs, Vector4R<float> rhs) {
        return
            (lhs[0] != rhs[0]) ||
            (lhs[1] != rhs[1]) ||
            (lhs[2] != rhs[2]) ||
            (lhs[3] != rhs[3]);
    }

    //=====================================================
    // Arithmetic operators
    //=====================================================

    AVML_FINL Vector4R<float> operator+(Vector4R<float> lhs, Vector4R<float> rhs) {
        lhs += rhs;
        return lhs;
    }

    AVML_FINL Vector4R<float> operator-(Vector4R<float> lhs, Vector4R<float> rhs) {
        lhs -= rhs;
        return lhs;
    }

    AVML_FINL Vector4R<float> operator*(Vector4R<float> lhs, Vector4R<float> rhs) {
        lhs *= rhs;
        return lhs;
    }

    AVML_FINL Vector4R<float> operator*(Vector4R<float> lhs, float rhs) {
        lhs *= rhs;
        return lhs;
    }

    AVML_FINL Vector4R<float> operator*(float lhs, Vector4R<float> rhs) {
        rhs *= lhs;
        return rhs;
    }

    AVML_FINL Vector4R<float> operator/(Vector4R<float> lhs, float rhs) {
        lhs /= rhs;
        return lhs;
    }

    AVML_FINL Vector4R<float> operator/(Vector4R<float> lhs, Vector4R<float> rhs) {
        lhs /= rhs;
        return lhs;
    }

    //=====================================================
    // Vector math
    //=====================================================

    AVML_FINL float dot(Vector4R<float> lhs, Vector4R<float> rhs) {
        return
            lhs[0] * rhs[0] +
            lhs[1] * rhs[1] +
            lhs[2] * rhs[2] +
            lhs[3] * rhs[2];
    }

    AVML_FINL float length2(Unit_vector4R<float>) = delete;

    AVML_FINL float length2(Vector4R<float> v) {
        return dot(v, v);
    }

    AVML_FINL float length(Unit_vector4R<float>) = delete;

    AVML_FINL float length(Vector4R<float> v) {
        return std::sqrt(length2(v));
    }

    AVML_FINL Unit_vector4R<float> assume_normalized(Vector4R<float> v) {
        return Unit_vector4R<float>::read_aligned(v.data());
    }

    AVML_FINL Unit_vector4R<float> normalize(Vector4R<float> v) {
        v /= length(v);
        return assume_normalized(v);
    }

    AVML_FINL Vector4R<float> project(Vector4R<float> a, Vector4R<float> b) {
        return (dot(a, b) / dot(b, b)) * b;
    }

    AVML_FINL Vector4R<float> project(Vector4R<float> a, Unit_vector4R<float> b) {
        return dot(a, b) * b;
    }

    AVML_FINL Vector4R<float> reflect(Vector4R<float> v, Unit_vector4R<float> normal) {
        return 2 * dot(v, normal) * normal - v;
    }

    AVML_FINL Unit_vector4R<float> reflect(Unit_vector4R<float> v, Unit_vector4R<float> normal) {
        return Unit_vector4R<float>::read_aligned(reflect(static_cast<Vector4R<float>>(v), normal).data());
    }

    //=====================================================
    // Vectorized math
    //=====================================================

    AVML_FINL Vector4R<float> abs(Vector4R<float> v) {
        v[0] = std::abs(v[0]);
        v[1] = std::abs(v[1]);
        v[2] = std::abs(v[2]);
        v[3] = std::abs(v[3]);
        return v;
    }

    AVML_FINL Vector4R<float> max(Vector4R<float> u, Vector4R<float> v) {
        u[0] = std::max(u[0], v[0]);
        u[1] = std::max(u[1], v[1]);
        u[2] = std::max(u[2], v[2]);
        u[3] = std::max(u[3], v[3]);
        return u;
    }

    AVML_FINL Vector4R<float> min(Vector4R<float> u, Vector4R<float> v) {
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

    AVML_FINL float x(Vector4R<float> v) {
        return v[0];
    }

    AVML_FINL float y(Vector4R<float> v) {
        return v[1];
    }

    AVML_FINL float z(Vector4R<float> v) {
        return v[2];
    }

    AVML_FINL float w(Vector4R<float> v) {
        return v[3];
    }

    // Two components

    AVML_FINL Vector2R<float> xx(Vector4R<float> v) {
        return {v[0], v[0]};
    }

    AVML_FINL Vector2R<float> xy(Vector4R<float> v) {
        return {v[0], v[1]};
    }

    AVML_FINL Vector2R<float> xz(Vector4R<float> v) {
        return {v[0], v[2]};
    }

    AVML_FINL Vector2R<float> xw(Vector4R<float> v) {
        return {v[0], v[3]};
    }

    AVML_FINL Vector2R<float> yx(Vector4R<float> v) {
        return {v[1], v[0]};
    }

    AVML_FINL Vector2R<float> yy(Vector4R<float> v) {
        return {v[1], v[1]};
    }

    AVML_FINL Vector2R<float> yz(Vector4R<float> v) {
        return {v[1], v[2]};
    }

    AVML_FINL Vector2R<float> yw(Vector4R<float> v) {
        return {v[1], v[3]};
    }

    AVML_FINL Vector2R<float> zx(Vector4R<float> v) {
        return {v[2], v[0]};
    }

    AVML_FINL Vector2R<float> zy(Vector4R<float> v) {
        return {v[2], v[1]};
    }

    AVML_FINL Vector2R<float> zz(Vector4R<float> v) {
        return {v[2], v[2]};
    }

    AVML_FINL Vector2R<float> zw(Vector4R<float> v) {
        return {v[2], v[2]};
    }

    AVML_FINL Vector2R<float> wx(Vector4R<float> v) {
        return {v[3], v[0]};
    }

    AVML_FINL Vector2R<float> wy(Vector4R<float> v) {
        return {v[3], v[1]};
    }

    AVML_FINL Vector2R<float> wz(Vector4R<float> v) {
        return {v[3], v[2]};
    }

    AVML_FINL Vector2R<float> ww(Vector4R<float> v) {
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
//                    std::string code = "    Vector3R<float> ";
//
//                    code += index_to_char(i);
//                    code += index_to_char(j);
//                    code += index_to_char(k);
//
//                    code += "(Vector4R<float> v) {\n        return {";
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


    AVML_FINL Vector3R<float> xxx(Vector4R<float> v) {
        return {v[0], v[0], v[0]};
    }

    AVML_FINL Vector3R<float> xxy(Vector4R<float> v) {
        return {v[0], v[0], v[1]};
    }

    AVML_FINL Vector3R<float> xxz(Vector4R<float> v) {
        return {v[0], v[0], v[2]};
    }

    AVML_FINL Vector3R<float> xxw(Vector4R<float> v) {
        return {v[0], v[0], v[3]};
    }

    AVML_FINL Vector3R<float> xyx(Vector4R<float> v) {
        return {v[0], v[1], v[0]};
    }

    AVML_FINL Vector3R<float> xyy(Vector4R<float> v) {
        return {v[0], v[1], v[1]};
    }

    AVML_FINL Vector3R<float> xyz(Vector4R<float> v) {
        return {v[0], v[1], v[2]};
    }

    AVML_FINL Vector3R<float> xyw(Vector4R<float> v) {
        return {v[0], v[1], v[3]};
    }

    AVML_FINL Vector3R<float> xzx(Vector4R<float> v) {
        return {v[0], v[2], v[0]};
    }

    AVML_FINL Vector3R<float> xzy(Vector4R<float> v) {
        return {v[0], v[2], v[1]};
    }

    AVML_FINL Vector3R<float> xzz(Vector4R<float> v) {
        return {v[0], v[2], v[2]};
    }

    AVML_FINL Vector3R<float> xzw(Vector4R<float> v) {
        return {v[0], v[2], v[3]};
    }

    AVML_FINL Vector3R<float> xwx(Vector4R<float> v) {
        return {v[0], v[3], v[0]};
    }

    AVML_FINL Vector3R<float> xwy(Vector4R<float> v) {
        return {v[0], v[3], v[1]};
    }

    AVML_FINL Vector3R<float> xwz(Vector4R<float> v) {
        return {v[0], v[3], v[2]};
    }

    AVML_FINL Vector3R<float> xww(Vector4R<float> v) {
        return {v[0], v[3], v[3]};
    }

    AVML_FINL Vector3R<float> yxx(Vector4R<float> v) {
        return {v[1], v[0], v[0]};
    }

    AVML_FINL Vector3R<float> yxy(Vector4R<float> v) {
        return {v[1], v[0], v[1]};
    }

    AVML_FINL Vector3R<float> yxz(Vector4R<float> v) {
        return {v[1], v[0], v[2]};
    }

    AVML_FINL Vector3R<float> yxw(Vector4R<float> v) {
        return {v[1], v[0], v[3]};
    }

    AVML_FINL Vector3R<float> yyx(Vector4R<float> v) {
        return {v[1], v[1], v[0]};
    }

    AVML_FINL Vector3R<float> yyy(Vector4R<float> v) {
        return {v[1], v[1], v[1]};
    }

    AVML_FINL Vector3R<float> yyz(Vector4R<float> v) {
        return {v[1], v[1], v[2]};
    }

    AVML_FINL Vector3R<float> yyw(Vector4R<float> v) {
        return {v[1], v[1], v[3]};
    }

    AVML_FINL Vector3R<float> yzx(Vector4R<float> v) {
        return {v[1], v[2], v[0]};
    }

    AVML_FINL Vector3R<float> yzy(Vector4R<float> v) {
        return {v[1], v[2], v[1]};
    }

    AVML_FINL Vector3R<float> yzz(Vector4R<float> v) {
        return {v[1], v[2], v[2]};
    }

    AVML_FINL Vector3R<float> yzw(Vector4R<float> v) {
        return {v[1], v[2], v[3]};
    }

    AVML_FINL Vector3R<float> ywx(Vector4R<float> v) {
        return {v[1], v[3], v[0]};
    }

    AVML_FINL Vector3R<float> ywy(Vector4R<float> v) {
        return {v[1], v[3], v[1]};
    }

    AVML_FINL Vector3R<float> ywz(Vector4R<float> v) {
        return {v[1], v[3], v[2]};
    }

    AVML_FINL Vector3R<float> yww(Vector4R<float> v) {
        return {v[1], v[3], v[3]};
    }

    AVML_FINL Vector3R<float> zxx(Vector4R<float> v) {
        return {v[2], v[0], v[0]};
    }

    AVML_FINL Vector3R<float> zxy(Vector4R<float> v) {
        return {v[2], v[0], v[1]};
    }

    AVML_FINL Vector3R<float> zxz(Vector4R<float> v) {
        return {v[2], v[0], v[2]};
    }

    AVML_FINL Vector3R<float> zxw(Vector4R<float> v) {
        return {v[2], v[0], v[3]};
    }

    AVML_FINL Vector3R<float> zyx(Vector4R<float> v) {
        return {v[2], v[1], v[0]};
    }

    AVML_FINL Vector3R<float> zyy(Vector4R<float> v) {
        return {v[2], v[1], v[1]};
    }

    AVML_FINL Vector3R<float> zyz(Vector4R<float> v) {
        return {v[2], v[1], v[2]};
    }

    AVML_FINL Vector3R<float> zyw(Vector4R<float> v) {
        return {v[2], v[1], v[3]};
    }

    AVML_FINL Vector3R<float> zzx(Vector4R<float> v) {
        return {v[2], v[2], v[0]};
    }

    AVML_FINL Vector3R<float> zzy(Vector4R<float> v) {
        return {v[2], v[2], v[1]};
    }

    AVML_FINL Vector3R<float> zzz(Vector4R<float> v) {
        return {v[2], v[2], v[2]};
    }

    AVML_FINL Vector3R<float> zzw(Vector4R<float> v) {
        return {v[2], v[2], v[3]};
    }

    AVML_FINL Vector3R<float> zwx(Vector4R<float> v) {
        return {v[2], v[3], v[0]};
    }

    AVML_FINL Vector3R<float> zwy(Vector4R<float> v) {
        return {v[2], v[3], v[1]};
    }

    AVML_FINL Vector3R<float> zwz(Vector4R<float> v) {
        return {v[2], v[3], v[2]};
    }

    AVML_FINL Vector3R<float> zww(Vector4R<float> v) {
        return {v[2], v[3], v[3]};
    }

    AVML_FINL Vector3R<float> wxx(Vector4R<float> v) {
        return {v[3], v[0], v[0]};
    }

    AVML_FINL Vector3R<float> wxy(Vector4R<float> v) {
        return {v[3], v[0], v[1]};
    }

    AVML_FINL Vector3R<float> wxz(Vector4R<float> v) {
        return {v[3], v[0], v[2]};
    }

    AVML_FINL Vector3R<float> wxw(Vector4R<float> v) {
        return {v[3], v[0], v[3]};
    }

    AVML_FINL Vector3R<float> wyx(Vector4R<float> v) {
        return {v[3], v[1], v[0]};
    }

    AVML_FINL Vector3R<float> wyy(Vector4R<float> v) {
        return {v[3], v[1], v[1]};
    }

    AVML_FINL Vector3R<float> wyz(Vector4R<float> v) {
        return {v[3], v[1], v[2]};
    }

    AVML_FINL Vector3R<float> wyw(Vector4R<float> v) {
        return {v[3], v[1], v[3]};
    }

    AVML_FINL Vector3R<float> wzx(Vector4R<float> v) {
        return {v[3], v[2], v[0]};
    }

    AVML_FINL Vector3R<float> wzy(Vector4R<float> v) {
        return {v[3], v[2], v[1]};
    }

    AVML_FINL Vector3R<float> wzz(Vector4R<float> v) {
        return {v[3], v[2], v[2]};
    }

    AVML_FINL Vector3R<float> wzw(Vector4R<float> v) {
        return {v[3], v[2], v[3]};
    }

    AVML_FINL Vector3R<float> wwx(Vector4R<float> v) {
        return {v[3], v[3], v[0]};
    }

    AVML_FINL Vector3R<float> wwy(Vector4R<float> v) {
        return {v[3], v[3], v[1]};
    }

    AVML_FINL Vector3R<float> wwz(Vector4R<float> v) {
        return {v[3], v[3], v[2]};
    }

    AVML_FINL Vector3R<float> www(Vector4R<float> v) {
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
    //                    std::string code = "    Vector4R<float> ";
    //
    //                    code += index_to_char(i);
    //                    code += index_to_char(j);
    //                    code += index_to_char(k);
    //                    code += index_to_char(l);
    //
    //                    code += "(Vector4R<float> v) {\n        return {";
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

    AVML_FINL Vector4R<float> xxxx(Vector4R<float> v) {
        return {v[0], v[0], v[0], v[0]};
    }

    AVML_FINL Vector4R<float> xxxy(Vector4R<float> v) {
        return {v[0], v[0], v[0], v[1]};
    }

    AVML_FINL Vector4R<float> xxxz(Vector4R<float> v) {
        return {v[0], v[0], v[0], v[2]};
    }

    AVML_FINL Vector4R<float> xxxw(Vector4R<float> v) {
        return {v[0], v[0], v[0], v[3]};
    }

    AVML_FINL Vector4R<float> xxyx(Vector4R<float> v) {
        return {v[0], v[0], v[1], v[0]};
    }

    AVML_FINL Vector4R<float> xxyy(Vector4R<float> v) {
        return {v[0], v[0], v[1], v[1]};
    }

    AVML_FINL Vector4R<float> xxyz(Vector4R<float> v) {
        return {v[0], v[0], v[1], v[2]};
    }

    AVML_FINL Vector4R<float> xxyw(Vector4R<float> v) {
        return {v[0], v[0], v[1], v[3]};
    }

    AVML_FINL Vector4R<float> xxzx(Vector4R<float> v) {
        return {v[0], v[0], v[2], v[0]};
    }

    AVML_FINL Vector4R<float> xxzy(Vector4R<float> v) {
        return {v[0], v[0], v[2], v[1]};
    }

    AVML_FINL Vector4R<float> xxzz(Vector4R<float> v) {
        return {v[0], v[0], v[2], v[2]};
    }

    AVML_FINL Vector4R<float> xxzw(Vector4R<float> v) {
        return {v[0], v[0], v[2], v[3]};
    }

    AVML_FINL Vector4R<float> xxwx(Vector4R<float> v) {
        return {v[0], v[0], v[3], v[0]};
    }

    AVML_FINL Vector4R<float> xxwy(Vector4R<float> v) {
        return {v[0], v[0], v[3], v[1]};
    }

    AVML_FINL Vector4R<float> xxwz(Vector4R<float> v) {
        return {v[0], v[0], v[3], v[2]};
    }

    AVML_FINL Vector4R<float> xxww(Vector4R<float> v) {
        return {v[0], v[0], v[3], v[3]};
    }

    AVML_FINL Vector4R<float> xyxx(Vector4R<float> v) {
        return {v[0], v[1], v[0], v[0]};
    }

    AVML_FINL Vector4R<float> xyxy(Vector4R<float> v) {
        return {v[0], v[1], v[0], v[1]};
    }

    AVML_FINL Vector4R<float> xyxz(Vector4R<float> v) {
        return {v[0], v[1], v[0], v[2]};
    }

    AVML_FINL Vector4R<float> xyxw(Vector4R<float> v) {
        return {v[0], v[1], v[0], v[3]};
    }

    AVML_FINL Vector4R<float> xyyx(Vector4R<float> v) {
        return {v[0], v[1], v[1], v[0]};
    }

    AVML_FINL Vector4R<float> xyyy(Vector4R<float> v) {
        return {v[0], v[1], v[1], v[1]};
    }

    AVML_FINL Vector4R<float> xyyz(Vector4R<float> v) {
        return {v[0], v[1], v[1], v[2]};
    }

    AVML_FINL Vector4R<float> xyyw(Vector4R<float> v) {
        return {v[0], v[1], v[1], v[3]};
    }

    AVML_FINL Vector4R<float> xyzx(Vector4R<float> v) {
        return {v[0], v[1], v[2], v[0]};
    }

    AVML_FINL Vector4R<float> xyzy(Vector4R<float> v) {
        return {v[0], v[1], v[2], v[1]};
    }

    AVML_FINL Vector4R<float> xyzz(Vector4R<float> v) {
        return {v[0], v[1], v[2], v[2]};
    }

    AVML_FINL Vector4R<float> xyzw(Vector4R<float> v) {
        return {v[0], v[1], v[2], v[3]};
    }

    AVML_FINL Vector4R<float> xywx(Vector4R<float> v) {
        return {v[0], v[1], v[3], v[0]};
    }

    AVML_FINL Vector4R<float> xywy(Vector4R<float> v) {
        return {v[0], v[1], v[3], v[1]};
    }

    AVML_FINL Vector4R<float> xywz(Vector4R<float> v) {
        return {v[0], v[1], v[3], v[2]};
    }

    AVML_FINL Vector4R<float> xyww(Vector4R<float> v) {
        return {v[0], v[1], v[3], v[3]};
    }

    AVML_FINL Vector4R<float> xzxx(Vector4R<float> v) {
        return {v[0], v[2], v[0], v[0]};
    }

    AVML_FINL Vector4R<float> xzxy(Vector4R<float> v) {
        return {v[0], v[2], v[0], v[1]};
    }

    AVML_FINL Vector4R<float> xzxz(Vector4R<float> v) {
        return {v[0], v[2], v[0], v[2]};
    }

    AVML_FINL Vector4R<float> xzxw(Vector4R<float> v) {
        return {v[0], v[2], v[0], v[3]};
    }

    AVML_FINL Vector4R<float> xzyx(Vector4R<float> v) {
        return {v[0], v[2], v[1], v[0]};
    }

    AVML_FINL Vector4R<float> xzyy(Vector4R<float> v) {
        return {v[0], v[2], v[1], v[1]};
    }

    AVML_FINL Vector4R<float> xzyz(Vector4R<float> v) {
        return {v[0], v[2], v[1], v[2]};
    }

    AVML_FINL Vector4R<float> xzyw(Vector4R<float> v) {
        return {v[0], v[2], v[1], v[3]};
    }

    AVML_FINL Vector4R<float> xzzx(Vector4R<float> v) {
        return {v[0], v[2], v[2], v[0]};
    }

    AVML_FINL Vector4R<float> xzzy(Vector4R<float> v) {
        return {v[0], v[2], v[2], v[1]};
    }

    AVML_FINL Vector4R<float> xzzz(Vector4R<float> v) {
        return {v[0], v[2], v[2], v[2]};
    }

    AVML_FINL Vector4R<float> xzzw(Vector4R<float> v) {
        return {v[0], v[2], v[2], v[3]};
    }

    AVML_FINL Vector4R<float> xzwx(Vector4R<float> v) {
        return {v[0], v[2], v[3], v[0]};
    }

    AVML_FINL Vector4R<float> xzwy(Vector4R<float> v) {
        return {v[0], v[2], v[3], v[1]};
    }

    AVML_FINL Vector4R<float> xzwz(Vector4R<float> v) {
        return {v[0], v[2], v[3], v[2]};
    }

    AVML_FINL Vector4R<float> xzww(Vector4R<float> v) {
        return {v[0], v[2], v[3], v[3]};
    }

    AVML_FINL Vector4R<float> xwxx(Vector4R<float> v) {
        return {v[0], v[3], v[0], v[0]};
    }

    AVML_FINL Vector4R<float> xwxy(Vector4R<float> v) {
        return {v[0], v[3], v[0], v[1]};
    }

    AVML_FINL Vector4R<float> xwxz(Vector4R<float> v) {
        return {v[0], v[3], v[0], v[2]};
    }

    AVML_FINL Vector4R<float> xwxw(Vector4R<float> v) {
        return {v[0], v[3], v[0], v[3]};
    }

    AVML_FINL Vector4R<float> xwyx(Vector4R<float> v) {
        return {v[0], v[3], v[1], v[0]};
    }

    AVML_FINL Vector4R<float> xwyy(Vector4R<float> v) {
        return {v[0], v[3], v[1], v[1]};
    }

    AVML_FINL Vector4R<float> xwyz(Vector4R<float> v) {
        return {v[0], v[3], v[1], v[2]};
    }

    AVML_FINL Vector4R<float> xwyw(Vector4R<float> v) {
        return {v[0], v[3], v[1], v[3]};
    }

    AVML_FINL Vector4R<float> xwzx(Vector4R<float> v) {
        return {v[0], v[3], v[2], v[0]};
    }

    AVML_FINL Vector4R<float> xwzy(Vector4R<float> v) {
        return {v[0], v[3], v[2], v[1]};
    }

    AVML_FINL Vector4R<float> xwzz(Vector4R<float> v) {
        return {v[0], v[3], v[2], v[2]};
    }

    AVML_FINL Vector4R<float> xwzw(Vector4R<float> v) {
        return {v[0], v[3], v[2], v[3]};
    }

    AVML_FINL Vector4R<float> xwwx(Vector4R<float> v) {
        return {v[0], v[3], v[3], v[0]};
    }

    AVML_FINL Vector4R<float> xwwy(Vector4R<float> v) {
        return {v[0], v[3], v[3], v[1]};
    }

    AVML_FINL Vector4R<float> xwwz(Vector4R<float> v) {
        return {v[0], v[3], v[3], v[2]};
    }

    AVML_FINL Vector4R<float> xwww(Vector4R<float> v) {
        return {v[0], v[3], v[3], v[3]};
    }

    AVML_FINL Vector4R<float> yxxx(Vector4R<float> v) {
        return {v[1], v[0], v[0], v[0]};
    }

    AVML_FINL Vector4R<float> yxxy(Vector4R<float> v) {
        return {v[1], v[0], v[0], v[1]};
    }

    AVML_FINL Vector4R<float> yxxz(Vector4R<float> v) {
        return {v[1], v[0], v[0], v[2]};
    }

    AVML_FINL Vector4R<float> yxxw(Vector4R<float> v) {
        return {v[1], v[0], v[0], v[3]};
    }

    AVML_FINL Vector4R<float> yxyx(Vector4R<float> v) {
        return {v[1], v[0], v[1], v[0]};
    }

    AVML_FINL Vector4R<float> yxyy(Vector4R<float> v) {
        return {v[1], v[0], v[1], v[1]};
    }

    AVML_FINL Vector4R<float> yxyz(Vector4R<float> v) {
        return {v[1], v[0], v[1], v[2]};
    }

    AVML_FINL Vector4R<float> yxyw(Vector4R<float> v) {
        return {v[1], v[0], v[1], v[3]};
    }

    AVML_FINL Vector4R<float> yxzx(Vector4R<float> v) {
        return {v[1], v[0], v[2], v[0]};
    }

    AVML_FINL Vector4R<float> yxzy(Vector4R<float> v) {
        return {v[1], v[0], v[2], v[1]};
    }

    AVML_FINL Vector4R<float> yxzz(Vector4R<float> v) {
        return {v[1], v[0], v[2], v[2]};
    }

    AVML_FINL Vector4R<float> yxzw(Vector4R<float> v) {
        return {v[1], v[0], v[2], v[3]};
    }

    AVML_FINL Vector4R<float> yxwx(Vector4R<float> v) {
        return {v[1], v[0], v[3], v[0]};
    }

    AVML_FINL Vector4R<float> yxwy(Vector4R<float> v) {
        return {v[1], v[0], v[3], v[1]};
    }

    AVML_FINL Vector4R<float> yxwz(Vector4R<float> v) {
        return {v[1], v[0], v[3], v[2]};
    }

    AVML_FINL Vector4R<float> yxww(Vector4R<float> v) {
        return {v[1], v[0], v[3], v[3]};
    }

    AVML_FINL Vector4R<float> yyxx(Vector4R<float> v) {
        return {v[1], v[1], v[0], v[0]};
    }

    AVML_FINL Vector4R<float> yyxy(Vector4R<float> v) {
        return {v[1], v[1], v[0], v[1]};
    }

    AVML_FINL Vector4R<float> yyxz(Vector4R<float> v) {
        return {v[1], v[1], v[0], v[2]};
    }

    AVML_FINL Vector4R<float> yyxw(Vector4R<float> v) {
        return {v[1], v[1], v[0], v[3]};
    }

    AVML_FINL Vector4R<float> yyyx(Vector4R<float> v) {
        return {v[1], v[1], v[1], v[0]};
    }

    AVML_FINL Vector4R<float> yyyy(Vector4R<float> v) {
        return {v[1], v[1], v[1], v[1]};
    }

    AVML_FINL Vector4R<float> yyyz(Vector4R<float> v) {
        return {v[1], v[1], v[1], v[2]};
    }

    AVML_FINL Vector4R<float> yyyw(Vector4R<float> v) {
        return {v[1], v[1], v[1], v[3]};
    }

    AVML_FINL Vector4R<float> yyzx(Vector4R<float> v) {
        return {v[1], v[1], v[2], v[0]};
    }

    AVML_FINL Vector4R<float> yyzy(Vector4R<float> v) {
        return {v[1], v[1], v[2], v[1]};
    }

    AVML_FINL Vector4R<float> yyzz(Vector4R<float> v) {
        return {v[1], v[1], v[2], v[2]};
    }

    AVML_FINL Vector4R<float> yyzw(Vector4R<float> v) {
        return {v[1], v[1], v[2], v[3]};
    }

    AVML_FINL Vector4R<float> yywx(Vector4R<float> v) {
        return {v[1], v[1], v[3], v[0]};
    }

    AVML_FINL Vector4R<float> yywy(Vector4R<float> v) {
        return {v[1], v[1], v[3], v[1]};
    }

    AVML_FINL Vector4R<float> yywz(Vector4R<float> v) {
        return {v[1], v[1], v[3], v[2]};
    }

    AVML_FINL Vector4R<float> yyww(Vector4R<float> v) {
        return {v[1], v[1], v[3], v[3]};
    }

    AVML_FINL Vector4R<float> yzxx(Vector4R<float> v) {
        return {v[1], v[2], v[0], v[0]};
    }

    AVML_FINL Vector4R<float> yzxy(Vector4R<float> v) {
        return {v[1], v[2], v[0], v[1]};
    }

    AVML_FINL Vector4R<float> yzxz(Vector4R<float> v) {
        return {v[1], v[2], v[0], v[2]};
    }

    AVML_FINL Vector4R<float> yzxw(Vector4R<float> v) {
        return {v[1], v[2], v[0], v[3]};
    }

    AVML_FINL Vector4R<float> yzyx(Vector4R<float> v) {
        return {v[1], v[2], v[1], v[0]};
    }

    AVML_FINL Vector4R<float> yzyy(Vector4R<float> v) {
        return {v[1], v[2], v[1], v[1]};
    }

    AVML_FINL Vector4R<float> yzyz(Vector4R<float> v) {
        return {v[1], v[2], v[1], v[2]};
    }

    AVML_FINL Vector4R<float> yzyw(Vector4R<float> v) {
        return {v[1], v[2], v[1], v[3]};
    }

    AVML_FINL Vector4R<float> yzzx(Vector4R<float> v) {
        return {v[1], v[2], v[2], v[0]};
    }

    AVML_FINL Vector4R<float> yzzy(Vector4R<float> v) {
        return {v[1], v[2], v[2], v[1]};
    }

    AVML_FINL Vector4R<float> yzzz(Vector4R<float> v) {
        return {v[1], v[2], v[2], v[2]};
    }

    AVML_FINL Vector4R<float> yzzw(Vector4R<float> v) {
        return {v[1], v[2], v[2], v[3]};
    }

    AVML_FINL Vector4R<float> yzwx(Vector4R<float> v) {
        return {v[1], v[2], v[3], v[0]};
    }

    AVML_FINL Vector4R<float> yzwy(Vector4R<float> v) {
        return {v[1], v[2], v[3], v[1]};
    }

    AVML_FINL Vector4R<float> yzwz(Vector4R<float> v) {
        return {v[1], v[2], v[3], v[2]};
    }

    AVML_FINL Vector4R<float> yzww(Vector4R<float> v) {
        return {v[1], v[2], v[3], v[3]};
    }

    AVML_FINL Vector4R<float> ywxx(Vector4R<float> v) {
        return {v[1], v[3], v[0], v[0]};
    }

    AVML_FINL Vector4R<float> ywxy(Vector4R<float> v) {
        return {v[1], v[3], v[0], v[1]};
    }

    AVML_FINL Vector4R<float> ywxz(Vector4R<float> v) {
        return {v[1], v[3], v[0], v[2]};
    }

    AVML_FINL Vector4R<float> ywxw(Vector4R<float> v) {
        return {v[1], v[3], v[0], v[3]};
    }

    AVML_FINL Vector4R<float> ywyx(Vector4R<float> v) {
        return {v[1], v[3], v[1], v[0]};
    }

    AVML_FINL Vector4R<float> ywyy(Vector4R<float> v) {
        return {v[1], v[3], v[1], v[1]};
    }

    AVML_FINL Vector4R<float> ywyz(Vector4R<float> v) {
        return {v[1], v[3], v[1], v[2]};
    }

    AVML_FINL Vector4R<float> ywyw(Vector4R<float> v) {
        return {v[1], v[3], v[1], v[3]};
    }

    AVML_FINL Vector4R<float> ywzx(Vector4R<float> v) {
        return {v[1], v[3], v[2], v[0]};
    }

    AVML_FINL Vector4R<float> ywzy(Vector4R<float> v) {
        return {v[1], v[3], v[2], v[1]};
    }

    AVML_FINL Vector4R<float> ywzz(Vector4R<float> v) {
        return {v[1], v[3], v[2], v[2]};
    }

    AVML_FINL Vector4R<float> ywzw(Vector4R<float> v) {
        return {v[1], v[3], v[2], v[3]};
    }

    AVML_FINL Vector4R<float> ywwx(Vector4R<float> v) {
        return {v[1], v[3], v[3], v[0]};
    }

    AVML_FINL Vector4R<float> ywwy(Vector4R<float> v) {
        return {v[1], v[3], v[3], v[1]};
    }

    AVML_FINL Vector4R<float> ywwz(Vector4R<float> v) {
        return {v[1], v[3], v[3], v[2]};
    }

    AVML_FINL Vector4R<float> ywww(Vector4R<float> v) {
        return {v[1], v[3], v[3], v[3]};
    }

    AVML_FINL Vector4R<float> zxxx(Vector4R<float> v) {
        return {v[2], v[0], v[0], v[0]};
    }

    AVML_FINL Vector4R<float> zxxy(Vector4R<float> v) {
        return {v[2], v[0], v[0], v[1]};
    }

    AVML_FINL Vector4R<float> zxxz(Vector4R<float> v) {
        return {v[2], v[0], v[0], v[2]};
    }

    AVML_FINL Vector4R<float> zxxw(Vector4R<float> v) {
        return {v[2], v[0], v[0], v[3]};
    }

    AVML_FINL Vector4R<float> zxyx(Vector4R<float> v) {
        return {v[2], v[0], v[1], v[0]};
    }

    AVML_FINL Vector4R<float> zxyy(Vector4R<float> v) {
        return {v[2], v[0], v[1], v[1]};
    }

    AVML_FINL Vector4R<float> zxyz(Vector4R<float> v) {
        return {v[2], v[0], v[1], v[2]};
    }

    AVML_FINL Vector4R<float> zxyw(Vector4R<float> v) {
        return {v[2], v[0], v[1], v[3]};
    }

    AVML_FINL Vector4R<float> zxzx(Vector4R<float> v) {
        return {v[2], v[0], v[2], v[0]};
    }

    AVML_FINL Vector4R<float> zxzy(Vector4R<float> v) {
        return {v[2], v[0], v[2], v[1]};
    }

    AVML_FINL Vector4R<float> zxzz(Vector4R<float> v) {
        return {v[2], v[0], v[2], v[2]};
    }

    AVML_FINL Vector4R<float> zxzw(Vector4R<float> v) {
        return {v[2], v[0], v[2], v[3]};
    }

    AVML_FINL Vector4R<float> zxwx(Vector4R<float> v) {
        return {v[2], v[0], v[3], v[0]};
    }

    AVML_FINL Vector4R<float> zxwy(Vector4R<float> v) {
        return {v[2], v[0], v[3], v[1]};
    }

    AVML_FINL Vector4R<float> zxwz(Vector4R<float> v) {
        return {v[2], v[0], v[3], v[2]};
    }

    AVML_FINL Vector4R<float> zxww(Vector4R<float> v) {
        return {v[2], v[0], v[3], v[3]};
    }

    AVML_FINL Vector4R<float> zyxx(Vector4R<float> v) {
        return {v[2], v[1], v[0], v[0]};
    }

    AVML_FINL Vector4R<float> zyxy(Vector4R<float> v) {
        return {v[2], v[1], v[0], v[1]};
    }

    AVML_FINL Vector4R<float> zyxz(Vector4R<float> v) {
        return {v[2], v[1], v[0], v[2]};
    }

    AVML_FINL Vector4R<float> zyxw(Vector4R<float> v) {
        return {v[2], v[1], v[0], v[3]};
    }

    AVML_FINL Vector4R<float> zyyx(Vector4R<float> v) {
        return {v[2], v[1], v[1], v[0]};
    }

    AVML_FINL Vector4R<float> zyyy(Vector4R<float> v) {
        return {v[2], v[1], v[1], v[1]};
    }

    AVML_FINL Vector4R<float> zyyz(Vector4R<float> v) {
        return {v[2], v[1], v[1], v[2]};
    }

    AVML_FINL Vector4R<float> zyyw(Vector4R<float> v) {
        return {v[2], v[1], v[1], v[3]};
    }

    AVML_FINL Vector4R<float> zyzx(Vector4R<float> v) {
        return {v[2], v[1], v[2], v[0]};
    }

    AVML_FINL Vector4R<float> zyzy(Vector4R<float> v) {
        return {v[2], v[1], v[2], v[1]};
    }

    AVML_FINL Vector4R<float> zyzz(Vector4R<float> v) {
        return {v[2], v[1], v[2], v[2]};
    }

    AVML_FINL Vector4R<float> zyzw(Vector4R<float> v) {
        return {v[2], v[1], v[2], v[3]};
    }

    AVML_FINL Vector4R<float> zywx(Vector4R<float> v) {
        return {v[2], v[1], v[3], v[0]};
    }

    AVML_FINL Vector4R<float> zywy(Vector4R<float> v) {
        return {v[2], v[1], v[3], v[1]};
    }

    AVML_FINL Vector4R<float> zywz(Vector4R<float> v) {
        return {v[2], v[1], v[3], v[2]};
    }

    AVML_FINL Vector4R<float> zyww(Vector4R<float> v) {
        return {v[2], v[1], v[3], v[3]};
    }

    AVML_FINL Vector4R<float> zzxx(Vector4R<float> v) {
        return {v[2], v[2], v[0], v[0]};
    }

    AVML_FINL Vector4R<float> zzxy(Vector4R<float> v) {
        return {v[2], v[2], v[0], v[1]};
    }

    AVML_FINL Vector4R<float> zzxz(Vector4R<float> v) {
        return {v[2], v[2], v[0], v[2]};
    }

    AVML_FINL Vector4R<float> zzxw(Vector4R<float> v) {
        return {v[2], v[2], v[0], v[3]};
    }

    AVML_FINL Vector4R<float> zzyx(Vector4R<float> v) {
        return {v[2], v[2], v[1], v[0]};
    }

    AVML_FINL Vector4R<float> zzyy(Vector4R<float> v) {
        return {v[2], v[2], v[1], v[1]};
    }

    AVML_FINL Vector4R<float> zzyz(Vector4R<float> v) {
        return {v[2], v[2], v[1], v[2]};
    }

    AVML_FINL Vector4R<float> zzyw(Vector4R<float> v) {
        return {v[2], v[2], v[1], v[3]};
    }

    AVML_FINL Vector4R<float> zzzx(Vector4R<float> v) {
        return {v[2], v[2], v[2], v[0]};
    }

    AVML_FINL Vector4R<float> zzzy(Vector4R<float> v) {
        return {v[2], v[2], v[2], v[1]};
    }

    AVML_FINL Vector4R<float> zzzz(Vector4R<float> v) {
        return {v[2], v[2], v[2], v[2]};
    }

    AVML_FINL Vector4R<float> zzzw(Vector4R<float> v) {
        return {v[2], v[2], v[2], v[3]};
    }

    AVML_FINL Vector4R<float> zzwx(Vector4R<float> v) {
        return {v[2], v[2], v[3], v[0]};
    }

    AVML_FINL Vector4R<float> zzwy(Vector4R<float> v) {
        return {v[2], v[2], v[3], v[1]};
    }

    AVML_FINL Vector4R<float> zzwz(Vector4R<float> v) {
        return {v[2], v[2], v[3], v[2]};
    }

    AVML_FINL Vector4R<float> zzww(Vector4R<float> v) {
        return {v[2], v[2], v[3], v[3]};
    }

    AVML_FINL Vector4R<float> zwxx(Vector4R<float> v) {
        return {v[2], v[3], v[0], v[0]};
    }

    AVML_FINL Vector4R<float> zwxy(Vector4R<float> v) {
        return {v[2], v[3], v[0], v[1]};
    }

    AVML_FINL Vector4R<float> zwxz(Vector4R<float> v) {
        return {v[2], v[3], v[0], v[2]};
    }

    AVML_FINL Vector4R<float> zwxw(Vector4R<float> v) {
        return {v[2], v[3], v[0], v[3]};
    }

    AVML_FINL Vector4R<float> zwyx(Vector4R<float> v) {
        return {v[2], v[3], v[1], v[0]};
    }

    AVML_FINL Vector4R<float> zwyy(Vector4R<float> v) {
        return {v[2], v[3], v[1], v[1]};
    }

    AVML_FINL Vector4R<float> zwyz(Vector4R<float> v) {
        return {v[2], v[3], v[1], v[2]};
    }

    AVML_FINL Vector4R<float> zwyw(Vector4R<float> v) {
        return {v[2], v[3], v[1], v[3]};
    }

    AVML_FINL Vector4R<float> zwzx(Vector4R<float> v) {
        return {v[2], v[3], v[2], v[0]};
    }

    AVML_FINL Vector4R<float> zwzy(Vector4R<float> v) {
        return {v[2], v[3], v[2], v[1]};
    }

    AVML_FINL Vector4R<float> zwzz(Vector4R<float> v) {
        return {v[2], v[3], v[2], v[2]};
    }

    AVML_FINL Vector4R<float> zwzw(Vector4R<float> v) {
        return {v[2], v[3], v[2], v[3]};
    }

    AVML_FINL Vector4R<float> zwwx(Vector4R<float> v) {
        return {v[2], v[3], v[3], v[0]};
    }

    AVML_FINL Vector4R<float> zwwy(Vector4R<float> v) {
        return {v[2], v[3], v[3], v[1]};
    }

    AVML_FINL Vector4R<float> zwwz(Vector4R<float> v) {
        return {v[2], v[3], v[3], v[2]};
    }

    AVML_FINL Vector4R<float> zwww(Vector4R<float> v) {
        return {v[2], v[3], v[3], v[3]};
    }

    AVML_FINL Vector4R<float> wxxx(Vector4R<float> v) {
        return {v[3], v[0], v[0], v[0]};
    }

    AVML_FINL Vector4R<float> wxxy(Vector4R<float> v) {
        return {v[3], v[0], v[0], v[1]};
    }

    AVML_FINL Vector4R<float> wxxz(Vector4R<float> v) {
        return {v[3], v[0], v[0], v[2]};
    }

    AVML_FINL Vector4R<float> wxxw(Vector4R<float> v) {
        return {v[3], v[0], v[0], v[3]};
    }

    AVML_FINL Vector4R<float> wxyx(Vector4R<float> v) {
        return {v[3], v[0], v[1], v[0]};
    }

    AVML_FINL Vector4R<float> wxyy(Vector4R<float> v) {
        return {v[3], v[0], v[1], v[1]};
    }

    AVML_FINL Vector4R<float> wxyz(Vector4R<float> v) {
        return {v[3], v[0], v[1], v[2]};
    }

    AVML_FINL Vector4R<float> wxyw(Vector4R<float> v) {
        return {v[3], v[0], v[1], v[3]};
    }

    AVML_FINL Vector4R<float> wxzx(Vector4R<float> v) {
        return {v[3], v[0], v[2], v[0]};
    }

    AVML_FINL Vector4R<float> wxzy(Vector4R<float> v) {
        return {v[3], v[0], v[2], v[1]};
    }

    AVML_FINL Vector4R<float> wxzz(Vector4R<float> v) {
        return {v[3], v[0], v[2], v[2]};
    }

    AVML_FINL Vector4R<float> wxzw(Vector4R<float> v) {
        return {v[3], v[0], v[2], v[3]};
    }

    AVML_FINL Vector4R<float> wxwx(Vector4R<float> v) {
        return {v[3], v[0], v[3], v[0]};
    }

    AVML_FINL Vector4R<float> wxwy(Vector4R<float> v) {
        return {v[3], v[0], v[3], v[1]};
    }

    AVML_FINL Vector4R<float> wxwz(Vector4R<float> v) {
        return {v[3], v[0], v[3], v[2]};
    }

    AVML_FINL Vector4R<float> wxww(Vector4R<float> v) {
        return {v[3], v[0], v[3], v[3]};
    }

    AVML_FINL Vector4R<float> wyxx(Vector4R<float> v) {
        return {v[3], v[1], v[0], v[0]};
    }

    AVML_FINL Vector4R<float> wyxy(Vector4R<float> v) {
        return {v[3], v[1], v[0], v[1]};
    }

    AVML_FINL Vector4R<float> wyxz(Vector4R<float> v) {
        return {v[3], v[1], v[0], v[2]};
    }

    AVML_FINL Vector4R<float> wyxw(Vector4R<float> v) {
        return {v[3], v[1], v[0], v[3]};
    }

    AVML_FINL Vector4R<float> wyyx(Vector4R<float> v) {
        return {v[3], v[1], v[1], v[0]};
    }

    AVML_FINL Vector4R<float> wyyy(Vector4R<float> v) {
        return {v[3], v[1], v[1], v[1]};
    }

    AVML_FINL Vector4R<float> wyyz(Vector4R<float> v) {
        return {v[3], v[1], v[1], v[2]};
    }

    AVML_FINL Vector4R<float> wyyw(Vector4R<float> v) {
        return {v[3], v[1], v[1], v[3]};
    }

    AVML_FINL Vector4R<float> wyzx(Vector4R<float> v) {
        return {v[3], v[1], v[2], v[0]};
    }

    AVML_FINL Vector4R<float> wyzy(Vector4R<float> v) {
        return {v[3], v[1], v[2], v[1]};
    }

    AVML_FINL Vector4R<float> wyzz(Vector4R<float> v) {
        return {v[3], v[1], v[2], v[2]};
    }

    AVML_FINL Vector4R<float> wyzw(Vector4R<float> v) {
        return {v[3], v[1], v[2], v[3]};
    }

    AVML_FINL Vector4R<float> wywx(Vector4R<float> v) {
        return {v[3], v[1], v[3], v[0]};
    }

    AVML_FINL Vector4R<float> wywy(Vector4R<float> v) {
        return {v[3], v[1], v[3], v[1]};
    }

    AVML_FINL Vector4R<float> wywz(Vector4R<float> v) {
        return {v[3], v[1], v[3], v[2]};
    }

    AVML_FINL Vector4R<float> wyww(Vector4R<float> v) {
        return {v[3], v[1], v[3], v[3]};
    }

    AVML_FINL Vector4R<float> wzxx(Vector4R<float> v) {
        return {v[3], v[2], v[0], v[0]};
    }

    AVML_FINL Vector4R<float> wzxy(Vector4R<float> v) {
        return {v[3], v[2], v[0], v[1]};
    }

    AVML_FINL Vector4R<float> wzxz(Vector4R<float> v) {
        return {v[3], v[2], v[0], v[2]};
    }

    AVML_FINL Vector4R<float> wzxw(Vector4R<float> v) {
        return {v[3], v[2], v[0], v[3]};
    }

    AVML_FINL Vector4R<float> wzyx(Vector4R<float> v) {
        return {v[3], v[2], v[1], v[0]};
    }

    AVML_FINL Vector4R<float> wzyy(Vector4R<float> v) {
        return {v[3], v[2], v[1], v[1]};
    }

    AVML_FINL Vector4R<float> wzyz(Vector4R<float> v) {
        return {v[3], v[2], v[1], v[2]};
    }

    AVML_FINL Vector4R<float> wzyw(Vector4R<float> v) {
        return {v[3], v[2], v[1], v[3]};
    }

    AVML_FINL Vector4R<float> wzzx(Vector4R<float> v) {
        return {v[3], v[2], v[2], v[0]};
    }

    AVML_FINL Vector4R<float> wzzy(Vector4R<float> v) {
        return {v[3], v[2], v[2], v[1]};
    }

    AVML_FINL Vector4R<float> wzzz(Vector4R<float> v) {
        return {v[3], v[2], v[2], v[2]};
    }

    AVML_FINL Vector4R<float> wzzw(Vector4R<float> v) {
        return {v[3], v[2], v[2], v[3]};
    }

    AVML_FINL Vector4R<float> wzwx(Vector4R<float> v) {
        return {v[3], v[2], v[3], v[0]};
    }

    AVML_FINL Vector4R<float> wzwy(Vector4R<float> v) {
        return {v[3], v[2], v[3], v[1]};
    }

    AVML_FINL Vector4R<float> wzwz(Vector4R<float> v) {
        return {v[3], v[2], v[3], v[2]};
    }

    AVML_FINL Vector4R<float> wzww(Vector4R<float> v) {
        return {v[3], v[2], v[3], v[3]};
    }

    AVML_FINL Vector4R<float> wwxx(Vector4R<float> v) {
        return {v[3], v[3], v[0], v[0]};
    }

    AVML_FINL Vector4R<float> wwxy(Vector4R<float> v) {
        return {v[3], v[3], v[0], v[1]};
    }

    AVML_FINL Vector4R<float> wwxz(Vector4R<float> v) {
        return {v[3], v[3], v[0], v[2]};
    }

    AVML_FINL Vector4R<float> wwxw(Vector4R<float> v) {
        return {v[3], v[3], v[0], v[3]};
    }

    AVML_FINL Vector4R<float> wwyx(Vector4R<float> v) {
        return {v[3], v[3], v[1], v[0]};
    }

    AVML_FINL Vector4R<float> wwyy(Vector4R<float> v) {
        return {v[3], v[3], v[1], v[1]};
    }

    AVML_FINL Vector4R<float> wwyz(Vector4R<float> v) {
        return {v[3], v[3], v[1], v[2]};
    }

    AVML_FINL Vector4R<float> wwyw(Vector4R<float> v) {
        return {v[3], v[3], v[1], v[3]};
    }

    AVML_FINL Vector4R<float> wwzx(Vector4R<float> v) {
        return {v[3], v[3], v[2], v[0]};
    }

    AVML_FINL Vector4R<float> wwzy(Vector4R<float> v) {
        return {v[3], v[3], v[2], v[1]};
    }

    AVML_FINL Vector4R<float> wwzz(Vector4R<float> v) {
        return {v[3], v[3], v[2], v[2]};
    }

    AVML_FINL Vector4R<float> wwzw(Vector4R<float> v) {
        return {v[3], v[3], v[2], v[3]};
    }

    AVML_FINL Vector4R<float> wwwx(Vector4R<float> v) {
        return {v[3], v[3], v[3], v[0]};
    }

    AVML_FINL Vector4R<float> wwwy(Vector4R<float> v) {
        return {v[3], v[3], v[3], v[1]};
    }

    AVML_FINL Vector4R<float> wwwz(Vector4R<float> v) {
        return {v[3], v[3], v[3], v[2]};
    }

    AVML_FINL Vector4R<float> wwww(Vector4R<float> v) {
        return {v[3], v[3], v[3], v[3]};
    }

}

#endif
