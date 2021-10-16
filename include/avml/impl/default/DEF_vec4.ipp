#ifndef AVML_VEC4_IPP
#define AVML_VEC4_IPP

namespace avml {

    template<class R>
    class alignas(alignof(R) * 4) Vector4 {
    public:

        using scalar = R;

        static constexpr unsigned width = 4;

        //=================================================
        // Creation functions
        //=================================================

        AVML_FINL static Vector4 read(const R* p) {
            return Vector4{p[0], p[1], p[2], p[3]};
        }

        AVML_FINL static Vector4 read_aligned(const R* p) {
            return Vector4{p[0], p[1], p[2], p[3]};
        }

        //=================================================
        // -ctors
        //=================================================

        explicit AVML_FINL Vector4(R v):
            elements{v, v, v, v} {}

        AVML_FINL Vector4(R x, R y, R z, R w):
            elements{x, y, z, w} {}

        AVML_FINL Vector4(Unit_vector4<R> v):
            elements{v[0], v[1], v[2], v[3]} {}

        AVML_FINL Vector4(Vector2<R> v, R z, R w):
            elements{v[0], v[1], z, w} {}

        AVML_FINL Vector4(R x, Vector2<R> v, R w):
            elements{x, v[0], v[1], w} {}

        AVML_FINL Vector4(R x, R y, Vector2<R> v):
            elements{x, y, v[0], v[1]} {}

        AVML_FINL Vector4(Vector2<R> v, Vector2<R> u):
            elements{v[0], v[1], u[0], u[1]} {}

        AVML_FINL Vector4(Vector3<R> v, R w):
            elements{v[0], v[1], v[2], w} {}

        AVML_FINL Vector4(R x, Vector3<R> v):
            elements{x, v[0], v[1], v[2]} {}

        Vector4() = default;
        Vector4(const Vector4&) = default;
        Vector4(Vector4&&) = default;
        ~Vector4() = default;

        //=================================================
        // Assignment operators
        //=================================================

        Vector4& operator=(const Vector4&) = default;
        Vector4& operator=(Vector4&&) = default;

        //=================================================
        // Unary arithmetic operators
        //=================================================

        AVML_FINL Vector4 operator+() const {
            return *this;
        }

        AVML_FINL Vector4 operator-() const {
            return Vector4{
                -elements[0],
                -elements[1],
                -elements[2],
                -elements[3]
            };
        }

        //=================================================
        // Arithmetic assignment operators
        //=================================================

        AVML_FINL Vector4& operator+=(const Vector4& rhs) {
            for (unsigned i = 0; i < width; ++i) {
                elements[i] += rhs[i];
            }
            return *this;
        }

        AVML_FINL Vector4& operator-=(const Vector4& rhs) {
            for (unsigned i = 0; i < width; ++i) {
                elements[i] -= rhs[i];
            }
            return *this;
        }

        AVML_FINL Vector4& operator*=(const scalar rhs) {
            for (unsigned i = 0; i < width; ++i) {
                elements[i] *= rhs;
            }
            return *this;
        }

        AVML_FINL Vector4& operator*=(const Vector4 rhs) {
            for (unsigned i = 0; i < width; ++i) {
                elements[i] *= rhs[i];
            }
            return *this;
        }

        AVML_FINL Vector4& operator/=(const Vector4 rhs) {
            for (unsigned i = 0; i < width; ++i) {
                elements[i] /= rhs[i];
            }
            return *this;
        }

        AVML_FINL Vector4& operator/=(const scalar rhs) {
            for (unsigned i = 0; i < width; ++i) {
                elements[i] /= rhs;
            }
            return *this;
        }

        //=================================================
        // Accessors
        //=================================================

        AVML_FINL R& operator[](unsigned i) {
            return elements[i];
        }

        AVML_FINL const R& operator[](unsigned i) const {
            return elements[i];
        }

        AVML_FINL R* data() {
            return elements;
        }

        AVML_FINL const R* data() const {
            return elements;
        }

    private:

        //=================================================
        // Instance members
        //=================================================

        R elements[width] = {0.0f, 0.0f, 0.0f, 0.0f};

    };

    //=====================================================
    // Comparison operators
    //=====================================================

    template<class R>
    AVML_FINL bool operator==(Vector4<R> lhs, Vector4<R> rhs) {
        return
            (lhs[0] == rhs[0]) &&
            (lhs[1] == rhs[1]) &&
            (lhs[2] == rhs[2]) &&
            (lhs[3] == rhs[3]);
    }

    template<class R>
    AVML_FINL bool operator!=(Vector4<R> lhs, Vector4<R> rhs) {
        return
            (lhs[0] != rhs[0]) ||
            (lhs[1] != rhs[1]) ||
            (lhs[2] != rhs[2]) ||
            (lhs[3] != rhs[3]);
    }

    //=====================================================
    // Arithmetic operators
    //=====================================================

    template<class R>
    AVML_FINL Vector4<R> operator+(Vector4<R> lhs, Vector4<R> rhs) {
        lhs += rhs;
        return lhs;
    }

    template<class R>
    AVML_FINL Vector4<R> operator-(Vector4<R> lhs, Vector4<R> rhs) {
        lhs -= rhs;
        return lhs;
    }

    template<class R>
    AVML_FINL Vector4<R> operator*(Vector4<R> lhs, Vector4<R> rhs) {
        lhs *= rhs;
        return lhs;
    }

    template<class R>
    AVML_FINL Vector4<R> operator*(Vector4<R> lhs, R rhs) {
        lhs *= rhs;
        return lhs;
    }

    template<class R>
    AVML_FINL Vector4<R> operator*(R lhs, Vector4<R> rhs) {
        rhs *= lhs;
        return rhs;
    }

    template<class R>
    AVML_FINL Vector4<R> operator/(Vector4<R> lhs, R rhs) {
        lhs /= rhs;
        return lhs;
    }

    template<class R>
    AVML_FINL Vector4<R> operator/(Vector4<R> lhs, Vector4<R> rhs) {
        lhs /= rhs;
        return lhs;
    }

    //=====================================================
    // Vector math
    //=====================================================

    template<class R>
    AVML_FINL R dot(Vector4<R> lhs, Vector4<R> rhs) {
        return
            lhs[0] * rhs[0] +
            lhs[1] * rhs[1] +
            lhs[2] * rhs[2] +
            lhs[3] * rhs[2];
    }

    template<class R>
    AVML_FINL R length2(Unit_vector4<R>) = delete;

    template<class R>
    AVML_FINL R length2(Vector4<R> v) {
        return dot(v, v);
    }

    template<class R>
    AVML_FINL R length(Unit_vector4<R>) = delete;

    template<class R>
    AVML_FINL R length(Vector4<R> v) {
        using std::sqrt;
        return sqrt(length2(v));
    }

    template<class R>
    AVML_FINL Unit_vector4<R> assume_normalized(Vector4<R> v) {
        return Unit_vector4<R>::read_aligned(v.data());
    }

    template<class R>
    AVML_FINL Unit_vector4<R> normalize(Vector4<R> v) {
        v /= length(v);
        return assume_normalized(v);
    }

    template<class R>
    AVML_FINL Vector4<R> project(Vector4<R> a, Vector4<R> b) {
        return (dot(a, b) / dot(b, b)) * b;
    }

    template<class R>
    AVML_FINL Vector4<R> project(Vector4<R> a, Unit_vector4<R> b) {
        return dot(a, b) * b;
    }

    template<class R>
    AVML_FINL Vector4<R> reflect(Vector4<R> v, Unit_vector4<R> normal) {
        return 2 * dot(v, normal) * normal - v;
    }

    template<class R>
    AVML_FINL Unit_vector4<R> reflect(Unit_vector4<R> v, Unit_vector4<R> normal) {
        return Unit_vector4<R>::read_aligned(reflect(static_cast<Vector4<R>>(v), normal).data());
    }

    //=====================================================
    // Vectorized math
    //=====================================================

    template<class R>
    AVML_FINL Vector4<R> abs(Vector4<R> v) {
        using std::abs;
        v[0] = abs(v[0]);
        v[1] = abs(v[1]);
        v[2] = abs(v[2]);
        v[3] = abs(v[3]);
        return v;
    }

    template<class R>
    AVML_FINL Vector4<R> max(Vector4<R> u, Vector4<R> v) {
        using std::max;
        u[0] = max(u[0], v[0]);
        u[1] = max(u[1], v[1]);
        u[2] = max(u[2], v[2]);
        u[3] = max(u[3], v[3]);
        return u;
    }

    template<class R>
    AVML_FINL Vector4<R> min(Vector4<R> u, Vector4<R> v) {
        using std::min;
        u[0] = min(u[0], v[0]);
        u[1] = min(u[1], v[1]);
        u[2] = min(u[2], v[2]);
        u[3] = min(u[3], v[3]);
        return u;
    }

    //=====================================================
    // Swizzling
    //=====================================================

    // Single component

    template<class R>
    AVML_FINL R x(Vector4<R> v) {
        return v[0];
    }

    template<class R>
    AVML_FINL R y(Vector4<R> v) {
        return v[1];
    }

    template<class R>
    AVML_FINL R z(Vector4<R> v) {
        return v[2];
    }

    template<class R>
    AVML_FINL R w(Vector4<R> v) {
        return v[3];
    }

    // Two components

    template<class R>
    AVML_FINL vec2f xx(Vector4<R> v) {
        return {v[0], v[0]};
    }

    template<class R>
    AVML_FINL vec2f xy(Vector4<R> v) {
        return {v[0], v[1]};
    }

    template<class R>
    AVML_FINL vec2f xz(Vector4<R> v) {
        return {v[0], v[2]};
    }

    template<class R>
    AVML_FINL vec2f xw(Vector4<R> v) {
        return {v[0], v[3]};
    }

    template<class R>
    AVML_FINL vec2f yx(Vector4<R> v) {
        return {v[1], v[0]};
    }

    template<class R>
    AVML_FINL vec2f yy(Vector4<R> v) {
        return {v[1], v[1]};
    }

    template<class R>
    AVML_FINL vec2f yz(Vector4<R> v) {
        return {v[1], v[2]};
    }

    template<class R>
    AVML_FINL vec2f yw(Vector4<R> v) {
        return {v[1], v[3]};
    }

    template<class R>
    AVML_FINL vec2f zx(Vector4<R> v) {
        return {v[2], v[0]};
    }

    template<class R>
    AVML_FINL vec2f zy(Vector4<R> v) {
        return {v[2], v[1]};
    }

    template<class R>
    AVML_FINL vec2f zz(Vector4<R> v) {
        return {v[2], v[2]};
    }

    template<class R>
    AVML_FINL vec2f zw(Vector4<R> v) {
        return {v[2], v[2]};
    }

    template<class R>
    AVML_FINL vec2f wx(Vector4<R> v) {
        return {v[3], v[0]};
    }

    template<class R>
    AVML_FINL vec2f wy(Vector4<R> v) {
        return {v[3], v[1]};
    }

    template<class R>
    AVML_FINL vec2f wz(Vector4<R> v) {
        return {v[3], v[2]};
    }

    template<class R>
    AVML_FINL vec2f ww(Vector4<R> v) {
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
//                    code += "(Vector4<R> v) {\n        return {";
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

    template<class R>
    AVML_FINL vec3f xxx(Vector4<R> v) {
        return {v[0], v[0], v[0]};
    }

    template<class R>
    AVML_FINL vec3f xxy(Vector4<R> v) {
        return {v[0], v[0], v[1]};
    }

    template<class R>
    AVML_FINL vec3f xxz(Vector4<R> v) {
        return {v[0], v[0], v[2]};
    }

    template<class R>
    AVML_FINL vec3f xxw(Vector4<R> v) {
        return {v[0], v[0], v[3]};
    }

    template<class R>
    AVML_FINL vec3f xyx(Vector4<R> v) {
        return {v[0], v[1], v[0]};
    }

    template<class R>
    AVML_FINL vec3f xyy(Vector4<R> v) {
        return {v[0], v[1], v[1]};
    }

    template<class R>
    AVML_FINL vec3f xyz(Vector4<R> v) {
        return {v[0], v[1], v[2]};
    }

    template<class R>
    AVML_FINL vec3f xyw(Vector4<R> v) {
        return {v[0], v[1], v[3]};
    }

    template<class R>
    AVML_FINL vec3f xzx(Vector4<R> v) {
        return {v[0], v[2], v[0]};
    }

    template<class R>
    AVML_FINL vec3f xzy(Vector4<R> v) {
        return {v[0], v[2], v[1]};
    }

    template<class R>
    AVML_FINL vec3f xzz(Vector4<R> v) {
        return {v[0], v[2], v[2]};
    }

    template<class R>
    AVML_FINL vec3f xzw(Vector4<R> v) {
        return {v[0], v[2], v[3]};
    }

    template<class R>
    AVML_FINL vec3f xwx(Vector4<R> v) {
        return {v[0], v[3], v[0]};
    }

    template<class R>
    AVML_FINL vec3f xwy(Vector4<R> v) {
        return {v[0], v[3], v[1]};
    }

    template<class R>
    AVML_FINL vec3f xwz(Vector4<R> v) {
        return {v[0], v[3], v[2]};
    }

    template<class R>
    AVML_FINL vec3f xww(Vector4<R> v) {
        return {v[0], v[3], v[3]};
    }

    template<class R>
    AVML_FINL vec3f yxx(Vector4<R> v) {
        return {v[1], v[0], v[0]};
    }

    template<class R>
    AVML_FINL vec3f yxy(Vector4<R> v) {
        return {v[1], v[0], v[1]};
    }

    template<class R>
    AVML_FINL vec3f yxz(Vector4<R> v) {
        return {v[1], v[0], v[2]};
    }

    template<class R>
    AVML_FINL vec3f yxw(Vector4<R> v) {
        return {v[1], v[0], v[3]};
    }

    template<class R>
    AVML_FINL vec3f yyx(Vector4<R> v) {
        return {v[1], v[1], v[0]};
    }

    template<class R>
    AVML_FINL vec3f yyy(Vector4<R> v) {
        return {v[1], v[1], v[1]};
    }

    template<class R>
    AVML_FINL vec3f yyz(Vector4<R> v) {
        return {v[1], v[1], v[2]};
    }

    template<class R>
    AVML_FINL vec3f yyw(Vector4<R> v) {
        return {v[1], v[1], v[3]};
    }

    template<class R>
    AVML_FINL vec3f yzx(Vector4<R> v) {
        return {v[1], v[2], v[0]};
    }

    template<class R>
    AVML_FINL vec3f yzy(Vector4<R> v) {
        return {v[1], v[2], v[1]};
    }

    template<class R>
    AVML_FINL vec3f yzz(Vector4<R> v) {
        return {v[1], v[2], v[2]};
    }

    template<class R>
    AVML_FINL vec3f yzw(Vector4<R> v) {
        return {v[1], v[2], v[3]};
    }

    template<class R>
    AVML_FINL vec3f ywx(Vector4<R> v) {
        return {v[1], v[3], v[0]};
    }

    template<class R>
    AVML_FINL vec3f ywy(Vector4<R> v) {
        return {v[1], v[3], v[1]};
    }

    template<class R>
    AVML_FINL vec3f ywz(Vector4<R> v) {
        return {v[1], v[3], v[2]};
    }

    template<class R>
    AVML_FINL vec3f yww(Vector4<R> v) {
        return {v[1], v[3], v[3]};
    }

    template<class R>
    AVML_FINL vec3f zxx(Vector4<R> v) {
        return {v[2], v[0], v[0]};
    }

    template<class R>
    AVML_FINL vec3f zxy(Vector4<R> v) {
        return {v[2], v[0], v[1]};
    }

    template<class R>
    AVML_FINL vec3f zxz(Vector4<R> v) {
        return {v[2], v[0], v[2]};
    }

    template<class R>
    AVML_FINL vec3f zxw(Vector4<R> v) {
        return {v[2], v[0], v[3]};
    }

    template<class R>
    AVML_FINL vec3f zyx(Vector4<R> v) {
        return {v[2], v[1], v[0]};
    }

    template<class R>
    AVML_FINL vec3f zyy(Vector4<R> v) {
        return {v[2], v[1], v[1]};
    }

    template<class R>
    AVML_FINL vec3f zyz(Vector4<R> v) {
        return {v[2], v[1], v[2]};
    }

    template<class R>
    AVML_FINL vec3f zyw(Vector4<R> v) {
        return {v[2], v[1], v[3]};
    }

    template<class R>
    AVML_FINL vec3f zzx(Vector4<R> v) {
        return {v[2], v[2], v[0]};
    }

    template<class R>
    AVML_FINL vec3f zzy(Vector4<R> v) {
        return {v[2], v[2], v[1]};
    }

    template<class R>
    AVML_FINL vec3f zzz(Vector4<R> v) {
        return {v[2], v[2], v[2]};
    }

    template<class R>
    AVML_FINL vec3f zzw(Vector4<R> v) {
        return {v[2], v[2], v[3]};
    }

    template<class R>
    AVML_FINL vec3f zwx(Vector4<R> v) {
        return {v[2], v[3], v[0]};
    }

    template<class R>
    AVML_FINL vec3f zwy(Vector4<R> v) {
        return {v[2], v[3], v[1]};
    }

    template<class R>
    AVML_FINL vec3f zwz(Vector4<R> v) {
        return {v[2], v[3], v[2]};
    }

    template<class R>
    AVML_FINL vec3f zww(Vector4<R> v) {
        return {v[2], v[3], v[3]};
    }

    template<class R>
    AVML_FINL vec3f wxx(Vector4<R> v) {
        return {v[3], v[0], v[0]};
    }

    template<class R>
    AVML_FINL vec3f wxy(Vector4<R> v) {
        return {v[3], v[0], v[1]};
    }

    template<class R>
    AVML_FINL vec3f wxz(Vector4<R> v) {
        return {v[3], v[0], v[2]};
    }

    template<class R>
    AVML_FINL vec3f wxw(Vector4<R> v) {
        return {v[3], v[0], v[3]};
    }

    template<class R>
    AVML_FINL vec3f wyx(Vector4<R> v) {
        return {v[3], v[1], v[0]};
    }

    template<class R>
    AVML_FINL vec3f wyy(Vector4<R> v) {
        return {v[3], v[1], v[1]};
    }

    template<class R>
    AVML_FINL vec3f wyz(Vector4<R> v) {
        return {v[3], v[1], v[2]};
    }

    template<class R>
    AVML_FINL vec3f wyw(Vector4<R> v) {
        return {v[3], v[1], v[3]};
    }

    template<class R>
    AVML_FINL vec3f wzx(Vector4<R> v) {
        return {v[3], v[2], v[0]};
    }

    template<class R>
    AVML_FINL vec3f wzy(Vector4<R> v) {
        return {v[3], v[2], v[1]};
    }

    template<class R>
    AVML_FINL vec3f wzz(Vector4<R> v) {
        return {v[3], v[2], v[2]};
    }

    template<class R>
    AVML_FINL vec3f wzw(Vector4<R> v) {
        return {v[3], v[2], v[3]};
    }

    template<class R>
    AVML_FINL vec3f wwx(Vector4<R> v) {
        return {v[3], v[3], v[0]};
    }

    template<class R>
    AVML_FINL vec3f wwy(Vector4<R> v) {
        return {v[3], v[3], v[1]};
    }

    template<class R>
    AVML_FINL vec3f wwz(Vector4<R> v) {
        return {v[3], v[3], v[2]};
    }

    template<class R>
    AVML_FINL vec3f www(Vector4<R> v) {
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
    //                    std::string code = "    Vector4<R> ";
    //
    //                    code += index_to_char(i);
    //                    code += index_to_char(j);
    //                    code += index_to_char(k);
    //                    code += index_to_char(l);
    //
    //                    code += "(Vector4<R> v) {\n        return {";
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

    template<class R>
    AVML_FINL Vector4<R> xxxx(Vector4<R> v) {
        return {v[0], v[0], v[0], v[0]};
    }

    template<class R>
    AVML_FINL Vector4<R> xxxy(Vector4<R> v) {
        return {v[0], v[0], v[0], v[1]};
    }

    template<class R>
    AVML_FINL Vector4<R> xxxz(Vector4<R> v) {
        return {v[0], v[0], v[0], v[2]};
    }

    template<class R>
    AVML_FINL Vector4<R> xxxw(Vector4<R> v) {
        return {v[0], v[0], v[0], v[3]};
    }

    template<class R>
    AVML_FINL Vector4<R> xxyx(Vector4<R> v) {
        return {v[0], v[0], v[1], v[0]};
    }

    template<class R>
    AVML_FINL Vector4<R> xxyy(Vector4<R> v) {
        return {v[0], v[0], v[1], v[1]};
    }

    template<class R>
    AVML_FINL Vector4<R> xxyz(Vector4<R> v) {
        return {v[0], v[0], v[1], v[2]};
    }

    template<class R>
    AVML_FINL Vector4<R> xxyw(Vector4<R> v) {
        return {v[0], v[0], v[1], v[3]};
    }

    template<class R>
    AVML_FINL Vector4<R> xxzx(Vector4<R> v) {
        return {v[0], v[0], v[2], v[0]};
    }

    template<class R>
    AVML_FINL Vector4<R> xxzy(Vector4<R> v) {
        return {v[0], v[0], v[2], v[1]};
    }

    template<class R>
    AVML_FINL Vector4<R> xxzz(Vector4<R> v) {
        return {v[0], v[0], v[2], v[2]};
    }

    template<class R>
    AVML_FINL Vector4<R> xxzw(Vector4<R> v) {
        return {v[0], v[0], v[2], v[3]};
    }

    template<class R>
    AVML_FINL Vector4<R> xxwx(Vector4<R> v) {
        return {v[0], v[0], v[3], v[0]};
    }

    template<class R>
    AVML_FINL Vector4<R> xxwy(Vector4<R> v) {
        return {v[0], v[0], v[3], v[1]};
    }

    template<class R>
    AVML_FINL Vector4<R> xxwz(Vector4<R> v) {
        return {v[0], v[0], v[3], v[2]};
    }

    template<class R>
    AVML_FINL Vector4<R> xxww(Vector4<R> v) {
        return {v[0], v[0], v[3], v[3]};
    }

    template<class R>
    AVML_FINL Vector4<R> xyxx(Vector4<R> v) {
        return {v[0], v[1], v[0], v[0]};
    }

    template<class R>
    AVML_FINL Vector4<R> xyxy(Vector4<R> v) {
        return {v[0], v[1], v[0], v[1]};
    }

    template<class R>
    AVML_FINL Vector4<R> xyxz(Vector4<R> v) {
        return {v[0], v[1], v[0], v[2]};
    }

    template<class R>
    AVML_FINL Vector4<R> xyxw(Vector4<R> v) {
        return {v[0], v[1], v[0], v[3]};
    }

    template<class R>
    AVML_FINL Vector4<R> xyyx(Vector4<R> v) {
        return {v[0], v[1], v[1], v[0]};
    }

    template<class R>
    AVML_FINL Vector4<R> xyyy(Vector4<R> v) {
        return {v[0], v[1], v[1], v[1]};
    }

    template<class R>
    AVML_FINL Vector4<R> xyyz(Vector4<R> v) {
        return {v[0], v[1], v[1], v[2]};
    }

    template<class R>
    AVML_FINL Vector4<R> xyyw(Vector4<R> v) {
        return {v[0], v[1], v[1], v[3]};
    }

    template<class R>
    AVML_FINL Vector4<R> xyzx(Vector4<R> v) {
        return {v[0], v[1], v[2], v[0]};
    }

    template<class R>
    AVML_FINL Vector4<R> xyzy(Vector4<R> v) {
        return {v[0], v[1], v[2], v[1]};
    }

    template<class R>
    AVML_FINL Vector4<R> xyzz(Vector4<R> v) {
        return {v[0], v[1], v[2], v[2]};
    }

    template<class R>
    AVML_FINL Vector4<R> xyzw(Vector4<R> v) {
        return {v[0], v[1], v[2], v[3]};
    }

    template<class R>
    AVML_FINL Vector4<R> xywx(Vector4<R> v) {
        return {v[0], v[1], v[3], v[0]};
    }

    template<class R>
    AVML_FINL Vector4<R> xywy(Vector4<R> v) {
        return {v[0], v[1], v[3], v[1]};
    }

    template<class R>
    AVML_FINL Vector4<R> xywz(Vector4<R> v) {
        return {v[0], v[1], v[3], v[2]};
    }

    template<class R>
    AVML_FINL Vector4<R> xyww(Vector4<R> v) {
        return {v[0], v[1], v[3], v[3]};
    }

    template<class R>
    AVML_FINL Vector4<R> xzxx(Vector4<R> v) {
        return {v[0], v[2], v[0], v[0]};
    }

    template<class R>
    AVML_FINL Vector4<R> xzxy(Vector4<R> v) {
        return {v[0], v[2], v[0], v[1]};
    }

    template<class R>
    AVML_FINL Vector4<R> xzxz(Vector4<R> v) {
        return {v[0], v[2], v[0], v[2]};
    }

    template<class R>
    AVML_FINL Vector4<R> xzxw(Vector4<R> v) {
        return {v[0], v[2], v[0], v[3]};
    }

    template<class R>
    AVML_FINL Vector4<R> xzyx(Vector4<R> v) {
        return {v[0], v[2], v[1], v[0]};
    }

    template<class R>
    AVML_FINL Vector4<R> xzyy(Vector4<R> v) {
        return {v[0], v[2], v[1], v[1]};
    }

    template<class R>
    AVML_FINL Vector4<R> xzyz(Vector4<R> v) {
        return {v[0], v[2], v[1], v[2]};
    }

    template<class R>
    AVML_FINL Vector4<R> xzyw(Vector4<R> v) {
        return {v[0], v[2], v[1], v[3]};
    }

    template<class R>
    AVML_FINL Vector4<R> xzzx(Vector4<R> v) {
        return {v[0], v[2], v[2], v[0]};
    }

    template<class R>
    AVML_FINL Vector4<R> xzzy(Vector4<R> v) {
        return {v[0], v[2], v[2], v[1]};
    }

    template<class R>
    AVML_FINL Vector4<R> xzzz(Vector4<R> v) {
        return {v[0], v[2], v[2], v[2]};
    }

    template<class R>
    AVML_FINL Vector4<R> xzzw(Vector4<R> v) {
        return {v[0], v[2], v[2], v[3]};
    }

    template<class R>
    AVML_FINL Vector4<R> xzwx(Vector4<R> v) {
        return {v[0], v[2], v[3], v[0]};
    }

    template<class R>
    AVML_FINL Vector4<R> xzwy(Vector4<R> v) {
        return {v[0], v[2], v[3], v[1]};
    }

    template<class R>
    AVML_FINL Vector4<R> xzwz(Vector4<R> v) {
        return {v[0], v[2], v[3], v[2]};
    }

    template<class R>
    AVML_FINL Vector4<R> xzww(Vector4<R> v) {
        return {v[0], v[2], v[3], v[3]};
    }

    template<class R>
    AVML_FINL Vector4<R> xwxx(Vector4<R> v) {
        return {v[0], v[3], v[0], v[0]};
    }

    template<class R>
    AVML_FINL Vector4<R> xwxy(Vector4<R> v) {
        return {v[0], v[3], v[0], v[1]};
    }

    template<class R>
    AVML_FINL Vector4<R> xwxz(Vector4<R> v) {
        return {v[0], v[3], v[0], v[2]};
    }

    template<class R>
    AVML_FINL Vector4<R> xwxw(Vector4<R> v) {
        return {v[0], v[3], v[0], v[3]};
    }

    template<class R>
    AVML_FINL Vector4<R> xwyx(Vector4<R> v) {
        return {v[0], v[3], v[1], v[0]};
    }

    template<class R>
    AVML_FINL Vector4<R> xwyy(Vector4<R> v) {
        return {v[0], v[3], v[1], v[1]};
    }

    template<class R>
    AVML_FINL Vector4<R> xwyz(Vector4<R> v) {
        return {v[0], v[3], v[1], v[2]};
    }

    template<class R>
    AVML_FINL Vector4<R> xwyw(Vector4<R> v) {
        return {v[0], v[3], v[1], v[3]};
    }

    template<class R>
    AVML_FINL Vector4<R> xwzx(Vector4<R> v) {
        return {v[0], v[3], v[2], v[0]};
    }

    template<class R>
    AVML_FINL Vector4<R> xwzy(Vector4<R> v) {
        return {v[0], v[3], v[2], v[1]};
    }

    template<class R>
    AVML_FINL Vector4<R> xwzz(Vector4<R> v) {
        return {v[0], v[3], v[2], v[2]};
    }

    template<class R>
    AVML_FINL Vector4<R> xwzw(Vector4<R> v) {
        return {v[0], v[3], v[2], v[3]};
    }

    template<class R>
    AVML_FINL Vector4<R> xwwx(Vector4<R> v) {
        return {v[0], v[3], v[3], v[0]};
    }

    template<class R>
    AVML_FINL Vector4<R> xwwy(Vector4<R> v) {
        return {v[0], v[3], v[3], v[1]};
    }

    template<class R>
    AVML_FINL Vector4<R> xwwz(Vector4<R> v) {
        return {v[0], v[3], v[3], v[2]};
    }

    template<class R>
    AVML_FINL Vector4<R> xwww(Vector4<R> v) {
        return {v[0], v[3], v[3], v[3]};
    }

    template<class R>
    AVML_FINL Vector4<R> yxxx(Vector4<R> v) {
        return {v[1], v[0], v[0], v[0]};
    }

    template<class R>
    AVML_FINL Vector4<R> yxxy(Vector4<R> v) {
        return {v[1], v[0], v[0], v[1]};
    }

    template<class R>
    AVML_FINL Vector4<R> yxxz(Vector4<R> v) {
        return {v[1], v[0], v[0], v[2]};
    }

    template<class R>
    AVML_FINL Vector4<R> yxxw(Vector4<R> v) {
        return {v[1], v[0], v[0], v[3]};
    }

    template<class R>
    AVML_FINL Vector4<R> yxyx(Vector4<R> v) {
        return {v[1], v[0], v[1], v[0]};
    }

    template<class R>
    AVML_FINL Vector4<R> yxyy(Vector4<R> v) {
        return {v[1], v[0], v[1], v[1]};
    }

    template<class R>
    AVML_FINL Vector4<R> yxyz(Vector4<R> v) {
        return {v[1], v[0], v[1], v[2]};
    }

    template<class R>
    AVML_FINL Vector4<R> yxyw(Vector4<R> v) {
        return {v[1], v[0], v[1], v[3]};
    }

    template<class R>
    AVML_FINL Vector4<R> yxzx(Vector4<R> v) {
        return {v[1], v[0], v[2], v[0]};
    }

    template<class R>
    AVML_FINL Vector4<R> yxzy(Vector4<R> v) {
        return {v[1], v[0], v[2], v[1]};
    }

    template<class R>
    AVML_FINL Vector4<R> yxzz(Vector4<R> v) {
        return {v[1], v[0], v[2], v[2]};
    }

    template<class R>
    AVML_FINL Vector4<R> yxzw(Vector4<R> v) {
        return {v[1], v[0], v[2], v[3]};
    }

    template<class R>
    AVML_FINL Vector4<R> yxwx(Vector4<R> v) {
        return {v[1], v[0], v[3], v[0]};
    }

    template<class R>
    AVML_FINL Vector4<R> yxwy(Vector4<R> v) {
        return {v[1], v[0], v[3], v[1]};
    }

    template<class R>
    AVML_FINL Vector4<R> yxwz(Vector4<R> v) {
        return {v[1], v[0], v[3], v[2]};
    }

    template<class R>
    AVML_FINL Vector4<R> yxww(Vector4<R> v) {
        return {v[1], v[0], v[3], v[3]};
    }

    template<class R>
    AVML_FINL Vector4<R> yyxx(Vector4<R> v) {
        return {v[1], v[1], v[0], v[0]};
    }

    template<class R>
    AVML_FINL Vector4<R> yyxy(Vector4<R> v) {
        return {v[1], v[1], v[0], v[1]};
    }

    template<class R>
    AVML_FINL Vector4<R> yyxz(Vector4<R> v) {
        return {v[1], v[1], v[0], v[2]};
    }

    template<class R>
    AVML_FINL Vector4<R> yyxw(Vector4<R> v) {
        return {v[1], v[1], v[0], v[3]};
    }

    template<class R>
    AVML_FINL Vector4<R> yyyx(Vector4<R> v) {
        return {v[1], v[1], v[1], v[0]};
    }

    template<class R>
    AVML_FINL Vector4<R> yyyy(Vector4<R> v) {
        return {v[1], v[1], v[1], v[1]};
    }

    template<class R>
    AVML_FINL Vector4<R> yyyz(Vector4<R> v) {
        return {v[1], v[1], v[1], v[2]};
    }

    template<class R>
    AVML_FINL Vector4<R> yyyw(Vector4<R> v) {
        return {v[1], v[1], v[1], v[3]};
    }

    template<class R>
    AVML_FINL Vector4<R> yyzx(Vector4<R> v) {
        return {v[1], v[1], v[2], v[0]};
    }

    template<class R>
    AVML_FINL Vector4<R> yyzy(Vector4<R> v) {
        return {v[1], v[1], v[2], v[1]};
    }

    template<class R>
    AVML_FINL Vector4<R> yyzz(Vector4<R> v) {
        return {v[1], v[1], v[2], v[2]};
    }

    template<class R>
    AVML_FINL Vector4<R> yyzw(Vector4<R> v) {
        return {v[1], v[1], v[2], v[3]};
    }

    template<class R>
    AVML_FINL Vector4<R> yywx(Vector4<R> v) {
        return {v[1], v[1], v[3], v[0]};
    }

    template<class R>
    AVML_FINL Vector4<R> yywy(Vector4<R> v) {
        return {v[1], v[1], v[3], v[1]};
    }

    template<class R>
    AVML_FINL Vector4<R> yywz(Vector4<R> v) {
        return {v[1], v[1], v[3], v[2]};
    }

    template<class R>
    AVML_FINL Vector4<R> yyww(Vector4<R> v) {
        return {v[1], v[1], v[3], v[3]};
    }

    template<class R>
    AVML_FINL Vector4<R> yzxx(Vector4<R> v) {
        return {v[1], v[2], v[0], v[0]};
    }

    template<class R>
    AVML_FINL Vector4<R> yzxy(Vector4<R> v) {
        return {v[1], v[2], v[0], v[1]};
    }

    template<class R>
    AVML_FINL Vector4<R> yzxz(Vector4<R> v) {
        return {v[1], v[2], v[0], v[2]};
    }

    template<class R>
    AVML_FINL Vector4<R> yzxw(Vector4<R> v) {
        return {v[1], v[2], v[0], v[3]};
    }

    template<class R>
    AVML_FINL Vector4<R> yzyx(Vector4<R> v) {
        return {v[1], v[2], v[1], v[0]};
    }

    template<class R>
    AVML_FINL Vector4<R> yzyy(Vector4<R> v) {
        return {v[1], v[2], v[1], v[1]};
    }

    template<class R>
    AVML_FINL Vector4<R> yzyz(Vector4<R> v) {
        return {v[1], v[2], v[1], v[2]};
    }

    template<class R>
    AVML_FINL Vector4<R> yzyw(Vector4<R> v) {
        return {v[1], v[2], v[1], v[3]};
    }

    template<class R>
    AVML_FINL Vector4<R> yzzx(Vector4<R> v) {
        return {v[1], v[2], v[2], v[0]};
    }

    template<class R>
    AVML_FINL Vector4<R> yzzy(Vector4<R> v) {
        return {v[1], v[2], v[2], v[1]};
    }

    template<class R>
    AVML_FINL Vector4<R> yzzz(Vector4<R> v) {
        return {v[1], v[2], v[2], v[2]};
    }

    template<class R>
    AVML_FINL Vector4<R> yzzw(Vector4<R> v) {
        return {v[1], v[2], v[2], v[3]};
    }

    template<class R>
    AVML_FINL Vector4<R> yzwx(Vector4<R> v) {
        return {v[1], v[2], v[3], v[0]};
    }

    template<class R>
    AVML_FINL Vector4<R> yzwy(Vector4<R> v) {
        return {v[1], v[2], v[3], v[1]};
    }

    template<class R>
    AVML_FINL Vector4<R> yzwz(Vector4<R> v) {
        return {v[1], v[2], v[3], v[2]};
    }

    template<class R>
    AVML_FINL Vector4<R> yzww(Vector4<R> v) {
        return {v[1], v[2], v[3], v[3]};
    }

    template<class R>
    AVML_FINL Vector4<R> ywxx(Vector4<R> v) {
        return {v[1], v[3], v[0], v[0]};
    }

    template<class R>
    AVML_FINL Vector4<R> ywxy(Vector4<R> v) {
        return {v[1], v[3], v[0], v[1]};
    }

    template<class R>
    AVML_FINL Vector4<R> ywxz(Vector4<R> v) {
        return {v[1], v[3], v[0], v[2]};
    }

    template<class R>
    AVML_FINL Vector4<R> ywxw(Vector4<R> v) {
        return {v[1], v[3], v[0], v[3]};
    }

    template<class R>
    AVML_FINL Vector4<R> ywyx(Vector4<R> v) {
        return {v[1], v[3], v[1], v[0]};
    }

    template<class R>
    AVML_FINL Vector4<R> ywyy(Vector4<R> v) {
        return {v[1], v[3], v[1], v[1]};
    }

    template<class R>
    AVML_FINL Vector4<R> ywyz(Vector4<R> v) {
        return {v[1], v[3], v[1], v[2]};
    }

    template<class R>
    AVML_FINL Vector4<R> ywyw(Vector4<R> v) {
        return {v[1], v[3], v[1], v[3]};
    }

    template<class R>
    AVML_FINL Vector4<R> ywzx(Vector4<R> v) {
        return {v[1], v[3], v[2], v[0]};
    }

    template<class R>
    AVML_FINL Vector4<R> ywzy(Vector4<R> v) {
        return {v[1], v[3], v[2], v[1]};
    }

    template<class R>
    AVML_FINL Vector4<R> ywzz(Vector4<R> v) {
        return {v[1], v[3], v[2], v[2]};
    }

    template<class R>
    AVML_FINL Vector4<R> ywzw(Vector4<R> v) {
        return {v[1], v[3], v[2], v[3]};
    }

    template<class R>
    AVML_FINL Vector4<R> ywwx(Vector4<R> v) {
        return {v[1], v[3], v[3], v[0]};
    }

    template<class R>
    AVML_FINL Vector4<R> ywwy(Vector4<R> v) {
        return {v[1], v[3], v[3], v[1]};
    }

    template<class R>
    AVML_FINL Vector4<R> ywwz(Vector4<R> v) {
        return {v[1], v[3], v[3], v[2]};
    }

    template<class R>
    AVML_FINL Vector4<R> ywww(Vector4<R> v) {
        return {v[1], v[3], v[3], v[3]};
    }

    template<class R>
    AVML_FINL Vector4<R> zxxx(Vector4<R> v) {
        return {v[2], v[0], v[0], v[0]};
    }

    template<class R>
    AVML_FINL Vector4<R> zxxy(Vector4<R> v) {
        return {v[2], v[0], v[0], v[1]};
    }

    template<class R>
    AVML_FINL Vector4<R> zxxz(Vector4<R> v) {
        return {v[2], v[0], v[0], v[2]};
    }

    template<class R>
    AVML_FINL Vector4<R> zxxw(Vector4<R> v) {
        return {v[2], v[0], v[0], v[3]};
    }

    template<class R>
    AVML_FINL Vector4<R> zxyx(Vector4<R> v) {
        return {v[2], v[0], v[1], v[0]};
    }

    template<class R>
    AVML_FINL Vector4<R> zxyy(Vector4<R> v) {
        return {v[2], v[0], v[1], v[1]};
    }

    template<class R>
    AVML_FINL Vector4<R> zxyz(Vector4<R> v) {
        return {v[2], v[0], v[1], v[2]};
    }

    template<class R>
    AVML_FINL Vector4<R> zxyw(Vector4<R> v) {
        return {v[2], v[0], v[1], v[3]};
    }

    template<class R>
    AVML_FINL Vector4<R> zxzx(Vector4<R> v) {
        return {v[2], v[0], v[2], v[0]};
    }

    template<class R>
    AVML_FINL Vector4<R> zxzy(Vector4<R> v) {
        return {v[2], v[0], v[2], v[1]};
    }

    template<class R>
    AVML_FINL Vector4<R> zxzz(Vector4<R> v) {
        return {v[2], v[0], v[2], v[2]};
    }

    template<class R>
    AVML_FINL Vector4<R> zxzw(Vector4<R> v) {
        return {v[2], v[0], v[2], v[3]};
    }

    template<class R>
    AVML_FINL Vector4<R> zxwx(Vector4<R> v) {
        return {v[2], v[0], v[3], v[0]};
    }

    template<class R>
    AVML_FINL Vector4<R> zxwy(Vector4<R> v) {
        return {v[2], v[0], v[3], v[1]};
    }

    template<class R>
    AVML_FINL Vector4<R> zxwz(Vector4<R> v) {
        return {v[2], v[0], v[3], v[2]};
    }

    template<class R>
    AVML_FINL Vector4<R> zxww(Vector4<R> v) {
        return {v[2], v[0], v[3], v[3]};
    }

    template<class R>
    AVML_FINL Vector4<R> zyxx(Vector4<R> v) {
        return {v[2], v[1], v[0], v[0]};
    }

    template<class R>
    AVML_FINL Vector4<R> zyxy(Vector4<R> v) {
        return {v[2], v[1], v[0], v[1]};
    }

    template<class R>
    AVML_FINL Vector4<R> zyxz(Vector4<R> v) {
        return {v[2], v[1], v[0], v[2]};
    }

    template<class R>
    AVML_FINL Vector4<R> zyxw(Vector4<R> v) {
        return {v[2], v[1], v[0], v[3]};
    }

    template<class R>
    AVML_FINL Vector4<R> zyyx(Vector4<R> v) {
        return {v[2], v[1], v[1], v[0]};
    }

    template<class R>
    AVML_FINL Vector4<R> zyyy(Vector4<R> v) {
        return {v[2], v[1], v[1], v[1]};
    }

    template<class R>
    AVML_FINL Vector4<R> zyyz(Vector4<R> v) {
        return {v[2], v[1], v[1], v[2]};
    }

    template<class R>
    AVML_FINL Vector4<R> zyyw(Vector4<R> v) {
        return {v[2], v[1], v[1], v[3]};
    }

    template<class R>
    AVML_FINL Vector4<R> zyzx(Vector4<R> v) {
        return {v[2], v[1], v[2], v[0]};
    }

    template<class R>
    AVML_FINL Vector4<R> zyzy(Vector4<R> v) {
        return {v[2], v[1], v[2], v[1]};
    }

    template<class R>
    AVML_FINL Vector4<R> zyzz(Vector4<R> v) {
        return {v[2], v[1], v[2], v[2]};
    }

    template<class R>
    AVML_FINL Vector4<R> zyzw(Vector4<R> v) {
        return {v[2], v[1], v[2], v[3]};
    }

    template<class R>
    AVML_FINL Vector4<R> zywx(Vector4<R> v) {
        return {v[2], v[1], v[3], v[0]};
    }

    template<class R>
    AVML_FINL Vector4<R> zywy(Vector4<R> v) {
        return {v[2], v[1], v[3], v[1]};
    }

    template<class R>
    AVML_FINL Vector4<R> zywz(Vector4<R> v) {
        return {v[2], v[1], v[3], v[2]};
    }

    template<class R>
    AVML_FINL Vector4<R> zyww(Vector4<R> v) {
        return {v[2], v[1], v[3], v[3]};
    }

    template<class R>
    AVML_FINL Vector4<R> zzxx(Vector4<R> v) {
        return {v[2], v[2], v[0], v[0]};
    }

    template<class R>
    AVML_FINL Vector4<R> zzxy(Vector4<R> v) {
        return {v[2], v[2], v[0], v[1]};
    }

    template<class R>
    AVML_FINL Vector4<R> zzxz(Vector4<R> v) {
        return {v[2], v[2], v[0], v[2]};
    }

    template<class R>
    AVML_FINL Vector4<R> zzxw(Vector4<R> v) {
        return {v[2], v[2], v[0], v[3]};
    }

    template<class R>
    AVML_FINL Vector4<R> zzyx(Vector4<R> v) {
        return {v[2], v[2], v[1], v[0]};
    }

    template<class R>
    AVML_FINL Vector4<R> zzyy(Vector4<R> v) {
        return {v[2], v[2], v[1], v[1]};
    }

    template<class R>
    AVML_FINL Vector4<R> zzyz(Vector4<R> v) {
        return {v[2], v[2], v[1], v[2]};
    }

    template<class R>
    AVML_FINL Vector4<R> zzyw(Vector4<R> v) {
        return {v[2], v[2], v[1], v[3]};
    }

    template<class R>
    AVML_FINL Vector4<R> zzzx(Vector4<R> v) {
        return {v[2], v[2], v[2], v[0]};
    }

    template<class R>
    AVML_FINL Vector4<R> zzzy(Vector4<R> v) {
        return {v[2], v[2], v[2], v[1]};
    }

    template<class R>
    AVML_FINL Vector4<R> zzzz(Vector4<R> v) {
        return {v[2], v[2], v[2], v[2]};
    }

    template<class R>
    AVML_FINL Vector4<R> zzzw(Vector4<R> v) {
        return {v[2], v[2], v[2], v[3]};
    }

    template<class R>
    AVML_FINL Vector4<R> zzwx(Vector4<R> v) {
        return {v[2], v[2], v[3], v[0]};
    }

    template<class R>
    AVML_FINL Vector4<R> zzwy(Vector4<R> v) {
        return {v[2], v[2], v[3], v[1]};
    }

    template<class R>
    AVML_FINL Vector4<R> zzwz(Vector4<R> v) {
        return {v[2], v[2], v[3], v[2]};
    }

    template<class R>
    AVML_FINL Vector4<R> zzww(Vector4<R> v) {
        return {v[2], v[2], v[3], v[3]};
    }

    template<class R>
    AVML_FINL Vector4<R> zwxx(Vector4<R> v) {
        return {v[2], v[3], v[0], v[0]};
    }

    template<class R>
    AVML_FINL Vector4<R> zwxy(Vector4<R> v) {
        return {v[2], v[3], v[0], v[1]};
    }

    template<class R>
    AVML_FINL Vector4<R> zwxz(Vector4<R> v) {
        return {v[2], v[3], v[0], v[2]};
    }

    template<class R>
    AVML_FINL Vector4<R> zwxw(Vector4<R> v) {
        return {v[2], v[3], v[0], v[3]};
    }

    template<class R>
    AVML_FINL Vector4<R> zwyx(Vector4<R> v) {
        return {v[2], v[3], v[1], v[0]};
    }

    template<class R>
    AVML_FINL Vector4<R> zwyy(Vector4<R> v) {
        return {v[2], v[3], v[1], v[1]};
    }

    template<class R>
    AVML_FINL Vector4<R> zwyz(Vector4<R> v) {
        return {v[2], v[3], v[1], v[2]};
    }

    template<class R>
    AVML_FINL Vector4<R> zwyw(Vector4<R> v) {
        return {v[2], v[3], v[1], v[3]};
    }

    template<class R>
    AVML_FINL Vector4<R> zwzx(Vector4<R> v) {
        return {v[2], v[3], v[2], v[0]};
    }

    template<class R>
    AVML_FINL Vector4<R> zwzy(Vector4<R> v) {
        return {v[2], v[3], v[2], v[1]};
    }

    template<class R>
    AVML_FINL Vector4<R> zwzz(Vector4<R> v) {
        return {v[2], v[3], v[2], v[2]};
    }

    template<class R>
    AVML_FINL Vector4<R> zwzw(Vector4<R> v) {
        return {v[2], v[3], v[2], v[3]};
    }

    template<class R>
    AVML_FINL Vector4<R> zwwx(Vector4<R> v) {
        return {v[2], v[3], v[3], v[0]};
    }

    template<class R>
    AVML_FINL Vector4<R> zwwy(Vector4<R> v) {
        return {v[2], v[3], v[3], v[1]};
    }

    template<class R>
    AVML_FINL Vector4<R> zwwz(Vector4<R> v) {
        return {v[2], v[3], v[3], v[2]};
    }

    template<class R>
    AVML_FINL Vector4<R> zwww(Vector4<R> v) {
        return {v[2], v[3], v[3], v[3]};
    }

    template<class R>
    AVML_FINL Vector4<R> wxxx(Vector4<R> v) {
        return {v[3], v[0], v[0], v[0]};
    }

    template<class R>
    AVML_FINL Vector4<R> wxxy(Vector4<R> v) {
        return {v[3], v[0], v[0], v[1]};
    }

    template<class R>
    AVML_FINL Vector4<R> wxxz(Vector4<R> v) {
        return {v[3], v[0], v[0], v[2]};
    }

    template<class R>
    AVML_FINL Vector4<R> wxxw(Vector4<R> v) {
        return {v[3], v[0], v[0], v[3]};
    }

    template<class R>
    AVML_FINL Vector4<R> wxyx(Vector4<R> v) {
        return {v[3], v[0], v[1], v[0]};
    }

    template<class R>
    AVML_FINL Vector4<R> wxyy(Vector4<R> v) {
        return {v[3], v[0], v[1], v[1]};
    }

    template<class R>
    AVML_FINL Vector4<R> wxyz(Vector4<R> v) {
        return {v[3], v[0], v[1], v[2]};
    }

    template<class R>
    AVML_FINL Vector4<R> wxyw(Vector4<R> v) {
        return {v[3], v[0], v[1], v[3]};
    }

    template<class R>
    AVML_FINL Vector4<R> wxzx(Vector4<R> v) {
        return {v[3], v[0], v[2], v[0]};
    }

    template<class R>
    AVML_FINL Vector4<R> wxzy(Vector4<R> v) {
        return {v[3], v[0], v[2], v[1]};
    }

    template<class R>
    AVML_FINL Vector4<R> wxzz(Vector4<R> v) {
        return {v[3], v[0], v[2], v[2]};
    }

    template<class R>
    AVML_FINL Vector4<R> wxzw(Vector4<R> v) {
        return {v[3], v[0], v[2], v[3]};
    }

    template<class R>
    AVML_FINL Vector4<R> wxwx(Vector4<R> v) {
        return {v[3], v[0], v[3], v[0]};
    }

    template<class R>
    AVML_FINL Vector4<R> wxwy(Vector4<R> v) {
        return {v[3], v[0], v[3], v[1]};
    }

    template<class R>
    AVML_FINL Vector4<R> wxwz(Vector4<R> v) {
        return {v[3], v[0], v[3], v[2]};
    }

    template<class R>
    AVML_FINL Vector4<R> wxww(Vector4<R> v) {
        return {v[3], v[0], v[3], v[3]};
    }

    template<class R>
    AVML_FINL Vector4<R> wyxx(Vector4<R> v) {
        return {v[3], v[1], v[0], v[0]};
    }

    template<class R>
    AVML_FINL Vector4<R> wyxy(Vector4<R> v) {
        return {v[3], v[1], v[0], v[1]};
    }

    template<class R>
    AVML_FINL Vector4<R> wyxz(Vector4<R> v) {
        return {v[3], v[1], v[0], v[2]};
    }

    template<class R>
    AVML_FINL Vector4<R> wyxw(Vector4<R> v) {
        return {v[3], v[1], v[0], v[3]};
    }

    template<class R>
    AVML_FINL Vector4<R> wyyx(Vector4<R> v) {
        return {v[3], v[1], v[1], v[0]};
    }

    template<class R>
    AVML_FINL Vector4<R> wyyy(Vector4<R> v) {
        return {v[3], v[1], v[1], v[1]};
    }

    template<class R>
    AVML_FINL Vector4<R> wyyz(Vector4<R> v) {
        return {v[3], v[1], v[1], v[2]};
    }

    template<class R>
    AVML_FINL Vector4<R> wyyw(Vector4<R> v) {
        return {v[3], v[1], v[1], v[3]};
    }

    template<class R>
    AVML_FINL Vector4<R> wyzx(Vector4<R> v) {
        return {v[3], v[1], v[2], v[0]};
    }

    template<class R>
    AVML_FINL Vector4<R> wyzy(Vector4<R> v) {
        return {v[3], v[1], v[2], v[1]};
    }

    template<class R>
    AVML_FINL Vector4<R> wyzz(Vector4<R> v) {
        return {v[3], v[1], v[2], v[2]};
    }

    template<class R>
    AVML_FINL Vector4<R> wyzw(Vector4<R> v) {
        return {v[3], v[1], v[2], v[3]};
    }

    template<class R>
    AVML_FINL Vector4<R> wywx(Vector4<R> v) {
        return {v[3], v[1], v[3], v[0]};
    }

    template<class R>
    AVML_FINL Vector4<R> wywy(Vector4<R> v) {
        return {v[3], v[1], v[3], v[1]};
    }

    template<class R>
    AVML_FINL Vector4<R> wywz(Vector4<R> v) {
        return {v[3], v[1], v[3], v[2]};
    }

    template<class R>
    AVML_FINL Vector4<R> wyww(Vector4<R> v) {
        return {v[3], v[1], v[3], v[3]};
    }

    template<class R>
    AVML_FINL Vector4<R> wzxx(Vector4<R> v) {
        return {v[3], v[2], v[0], v[0]};
    }

    template<class R>
    AVML_FINL Vector4<R> wzxy(Vector4<R> v) {
        return {v[3], v[2], v[0], v[1]};
    }

    template<class R>
    AVML_FINL Vector4<R> wzxz(Vector4<R> v) {
        return {v[3], v[2], v[0], v[2]};
    }

    template<class R>
    AVML_FINL Vector4<R> wzxw(Vector4<R> v) {
        return {v[3], v[2], v[0], v[3]};
    }

    template<class R>
    AVML_FINL Vector4<R> wzyx(Vector4<R> v) {
        return {v[3], v[2], v[1], v[0]};
    }

    template<class R>
    AVML_FINL Vector4<R> wzyy(Vector4<R> v) {
        return {v[3], v[2], v[1], v[1]};
    }

    template<class R>
    AVML_FINL Vector4<R> wzyz(Vector4<R> v) {
        return {v[3], v[2], v[1], v[2]};
    }

    template<class R>
    AVML_FINL Vector4<R> wzyw(Vector4<R> v) {
        return {v[3], v[2], v[1], v[3]};
    }

    template<class R>
    AVML_FINL Vector4<R> wzzx(Vector4<R> v) {
        return {v[3], v[2], v[2], v[0]};
    }

    template<class R>
    AVML_FINL Vector4<R> wzzy(Vector4<R> v) {
        return {v[3], v[2], v[2], v[1]};
    }

    template<class R>
    AVML_FINL Vector4<R> wzzz(Vector4<R> v) {
        return {v[3], v[2], v[2], v[2]};
    }

    template<class R>
    AVML_FINL Vector4<R> wzzw(Vector4<R> v) {
        return {v[3], v[2], v[2], v[3]};
    }

    template<class R>
    AVML_FINL Vector4<R> wzwx(Vector4<R> v) {
        return {v[3], v[2], v[3], v[0]};
    }

    template<class R>
    AVML_FINL Vector4<R> wzwy(Vector4<R> v) {
        return {v[3], v[2], v[3], v[1]};
    }

    template<class R>
    AVML_FINL Vector4<R> wzwz(Vector4<R> v) {
        return {v[3], v[2], v[3], v[2]};
    }

    template<class R>
    AVML_FINL Vector4<R> wzww(Vector4<R> v) {
        return {v[3], v[2], v[3], v[3]};
    }

    template<class R>
    AVML_FINL Vector4<R> wwxx(Vector4<R> v) {
        return {v[3], v[3], v[0], v[0]};
    }

    template<class R>
    AVML_FINL Vector4<R> wwxy(Vector4<R> v) {
        return {v[3], v[3], v[0], v[1]};
    }

    template<class R>
    AVML_FINL Vector4<R> wwxz(Vector4<R> v) {
        return {v[3], v[3], v[0], v[2]};
    }

    template<class R>
    AVML_FINL Vector4<R> wwxw(Vector4<R> v) {
        return {v[3], v[3], v[0], v[3]};
    }

    template<class R>
    AVML_FINL Vector4<R> wwyx(Vector4<R> v) {
        return {v[3], v[3], v[1], v[0]};
    }

    template<class R>
    AVML_FINL Vector4<R> wwyy(Vector4<R> v) {
        return {v[3], v[3], v[1], v[1]};
    }

    template<class R>
    AVML_FINL Vector4<R> wwyz(Vector4<R> v) {
        return {v[3], v[3], v[1], v[2]};
    }

    template<class R>
    AVML_FINL Vector4<R> wwyw(Vector4<R> v) {
        return {v[3], v[3], v[1], v[3]};
    }

    template<class R>
    AVML_FINL Vector4<R> wwzx(Vector4<R> v) {
        return {v[3], v[3], v[2], v[0]};
    }

    template<class R>
    AVML_FINL Vector4<R> wwzy(Vector4<R> v) {
        return {v[3], v[3], v[2], v[1]};
    }

    template<class R>
    AVML_FINL Vector4<R> wwzz(Vector4<R> v) {
        return {v[3], v[3], v[2], v[2]};
    }

    template<class R>
    AVML_FINL Vector4<R> wwzw(Vector4<R> v) {
        return {v[3], v[3], v[2], v[3]};
    }

    template<class R>
    AVML_FINL Vector4<R> wwwx(Vector4<R> v) {
        return {v[3], v[3], v[3], v[0]};
    }

    template<class R>
    AVML_FINL Vector4<R> wwwy(Vector4<R> v) {
        return {v[3], v[3], v[3], v[1]};
    }

    template<class R>
    AVML_FINL Vector4<R> wwwz(Vector4<R> v) {
        return {v[3], v[3], v[3], v[2]};
    }

    template<class R>
    AVML_FINL Vector4<R> wwww(Vector4<R> v) {
        return {v[3], v[3], v[3], v[3]};
    }

}

#endif
