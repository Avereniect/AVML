#ifndef AVML_VEC4R_HPP
#define AVML_VEC4R_HPP

namespace avml {

    template<class R>
    class alignas(avml_impl::vector_alignment<R, 4>()) Vector4R {
    public:

        using scalar = R;

        static constexpr unsigned width = 4;

        //=================================================
        // Creation functions
        //=================================================

        AVML_FINL static Vector4R read(const R* p) {
            return Vector4R{p[0], p[1], p[2], p[3]};
        }

        AVML_FINL static Vector4R read_aligned(const R* p) {
            return Vector4R{p[0], p[1], p[2], p[3]};
        }

        //=================================================
        // -ctors
        //=================================================

        explicit AVML_FINL Vector4R(R v):
            elements{v, v, v, v} {}

        AVML_FINL Vector4R(R x, R y, R z, R w):
            elements{x, y, z, w} {}

        AVML_FINL Vector4R(Unit_vector4R<R> v):
            elements{v[0], v[1], v[2], v[3]} {}

        AVML_FINL Vector4R(Vector2R<R> v, R z, R w):
            elements{v[0], v[1], z, w} {}

        AVML_FINL Vector4R(R x, Vector2R<R> v, R w):
            elements{x, v[0], v[1], w} {}

        AVML_FINL Vector4R(R x, R y, Vector2R<R> v):
            elements{x, y, v[0], v[1]} {}

        AVML_FINL Vector4R(Vector2R<R> v, Vector2R<R> u):
            elements{v[0], v[1], u[0], u[1]} {}

        AVML_FINL Vector4R(Vector3R<R> v, R w):
            elements{v[0], v[1], v[2], w} {}

        AVML_FINL Vector4R(R x, Vector3R<R> v):
            elements{x, v[0], v[1], v[2]} {}

        template<class U>
        explicit AVML_FINL Vector4R(Vector4R<U> v):
            elements{
                static_cast<R>(v[0]),
                static_cast<R>(v[1]),
                static_cast<R>(v[2]),
                static_cast<R>(v[3])
            } {}

        Vector4R() = default;
        Vector4R(const Vector4R&) = default;
        Vector4R(Vector4R&&) noexcept = default;
        ~Vector4R() = default;

        //=================================================
        // Assignment operators
        //=================================================

        Vector4R& operator=(const Vector4R&) = default;
        Vector4R& operator=(Vector4R&&) noexcept = default;

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

        R elements[width];

    };

    //=====================================================
    // Comparison operators
    //=====================================================

    template<class R>
    AVML_FINL bool operator==(Vector4R<R> lhs, Vector4R<R> rhs) {
        return
            (lhs[0] == rhs[0]) &&
            (lhs[1] == rhs[1]) &&
            (lhs[2] == rhs[2]) &&
            (lhs[3] == rhs[3]);
    }

    template<class R>
    AVML_FINL bool operator!=(Vector4R<R> lhs, Vector4R<R> rhs) {
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
    AVML_FINL Vector4R<R> operator+(Vector4R<R> lhs, Vector4R<R> rhs) {
        lhs += rhs;
        return lhs;
    }

    template<class R>
    AVML_FINL Vector4R<R> operator-(Vector4R<R> lhs, Vector4R<R> rhs) {
        lhs -= rhs;
        return lhs;
    }

    template<class R>
    AVML_FINL Vector4R<R> operator*(Vector4R<R> lhs, Vector4R<R> rhs) {
        lhs *= rhs;
        return lhs;
    }

    template<class R>
    AVML_FINL Vector4R<R> operator*(Vector4R<R> lhs, R rhs) {
        lhs *= rhs;
        return lhs;
    }

    template<class R>
    AVML_FINL Vector4R<R> operator*(R lhs, Vector4R<R> rhs) {
        rhs *= lhs;
        return rhs;
    }

    template<class R>
    AVML_FINL Vector4R<R> operator/(Vector4R<R> lhs, R rhs) {
        lhs /= rhs;
        return lhs;
    }

    template<class R>
    AVML_FINL Vector4R<R> operator/(Vector4R<R> lhs, Vector4R<R> rhs) {
        lhs /= rhs;
        return lhs;
    }

    //=====================================================
    // Vector math
    //=====================================================

    template<class R>
    AVML_FINL R dot(Vector4R<R> lhs, Vector4R<R> rhs) {
        return
            lhs[0] * rhs[0] +
            lhs[1] * rhs[1] +
            lhs[2] * rhs[2] +
            lhs[3] * rhs[2];
    }

    template<class R>
    AVML_FINL R length2(Vector4R<R> v) {
        return dot(v, v);
    }

    template<class R>
    AVML_FINL R length(Vector4R<R> v) {
        using std::sqrt;
        return sqrt(length2(v));
    }

    template<class R>
    AVML_FINL Unit_vector4R<R> assume_normalized(Unit_vector4R<R> v) {
        return Unit_vector4R<R>::read_aligned(v.data());
    }

    template<class R>
    AVML_FINL Unit_vector4R<R> normalize(Vector4R<R> v) {
        v /= length(v);
        return assume_normalized(v);
    }

    template<class R>
    AVML_FINL Vector4R<R> project(Vector4R<R> a, Vector4R<R> b) {
        return (dot(a, b) / dot(b, b)) * b;
    }

    template<class R>
    AVML_FINL Vector4R<R> project(Vector4R<R> a, Unit_vector4R<R> b) {
        return dot(a, b) * b;
    }

    template<class R>
    AVML_FINL Vector4R<R> reflect(Vector4R<R> v, Unit_vector4R<R> normal) {
        return 2 * dot(v, normal) * normal - v;
    }

    template<class R>
    AVML_FINL Unit_vector4R<R> reflect(Unit_vector4R<R> v, Unit_vector4R<R> normal) {
        return Unit_vector4R<R>::read_aligned(reflect(static_cast<Vector4R<R>>(v), normal).data());
    }

    //=====================================================
    // Vectorized math
    //=====================================================

    template<class R>
    AVML_FINL Vector4R<R> abs(Vector4R<R> v) {
        using std::abs;
        v[0] = abs(v[0]);
        v[1] = abs(v[1]);
        v[2] = abs(v[2]);
        v[3] = abs(v[3]);
        return v;
    }

    template<class R>
    AVML_FINL Vector4R<R> max(Vector4R<R> u, Vector4R<R> v) {
        using std::max;
        u[0] = max(u[0], v[0]);
        u[1] = max(u[1], v[1]);
        u[2] = max(u[2], v[2]);
        u[3] = max(u[3], v[3]);
        return u;
    }

    template<class R>
    AVML_FINL Vector4R<R> min(Vector4R<R> u, Vector4R<R> v) {
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
    AVML_FINL R x(Vector4R<R> v) {
        return v[0];
    }

    template<class R>
    AVML_FINL R y(Vector4R<R> v) {
        return v[1];
    }

    template<class R>
    AVML_FINL R z(Vector4R<R> v) {
        return v[2];
    }

    template<class R>
    AVML_FINL R w(Vector4R<R> v) {
        return v[3];
    }

    // Two components

    template<class R>
    AVML_FINL Vector2R<R> xx(Vector4R<R> v) {
        return {v[0], v[0]};
    }

    template<class R>
    AVML_FINL Vector2R<R> xy(Vector4R<R> v) {
        return {v[0], v[1]};
    }

    template<class R>
    AVML_FINL Vector2R<R> xz(Vector4R<R> v) {
        return {v[0], v[2]};
    }

    template<class R>
    AVML_FINL Vector2R<R> xw(Vector4R<R> v) {
        return {v[0], v[3]};
    }

    template<class R>
    AVML_FINL Vector2R<R> yx(Vector4R<R> v) {
        return {v[1], v[0]};
    }

    template<class R>
    AVML_FINL Vector2R<R> yy(Vector4R<R> v) {
        return {v[1], v[1]};
    }

    template<class R>
    AVML_FINL Vector2R<R> yz(Vector4R<R> v) {
        return {v[1], v[2]};
    }

    template<class R>
    AVML_FINL Vector2R<R> yw(Vector4R<R> v) {
        return {v[1], v[3]};
    }

    template<class R>
    AVML_FINL Vector2R<R> zx(Vector4R<R> v) {
        return {v[2], v[0]};
    }

    template<class R>
    AVML_FINL Vector2R<R> zy(Vector4R<R> v) {
        return {v[2], v[1]};
    }

    template<class R>
    AVML_FINL Vector2R<R> zz(Vector4R<R> v) {
        return {v[2], v[2]};
    }

    template<class R>
    AVML_FINL Vector2R<R> zw(Vector4R<R> v) {
        return {v[2], v[2]};
    }

    template<class R>
    AVML_FINL Vector2R<R> wx(Vector4R<R> v) {
        return {v[3], v[0]};
    }

    template<class R>
    AVML_FINL Vector2R<R> wy(Vector4R<R> v) {
        return {v[3], v[1]};
    }

    template<class R>
    AVML_FINL Vector2R<R> wz(Vector4R<R> v) {
        return {v[3], v[2]};
    }

    template<class R>
    AVML_FINL Vector2R<R> ww(Vector4R<R> v) {
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
//                    std::string code = "    Vector3R<R> ";
//
//                    code += index_to_char(i);
//                    code += index_to_char(j);
//                    code += index_to_char(k);
//
//                    code += "(Vector4R<R> v) {\n        return {";
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
    AVML_FINL Vector3R<R> xxx(Vector4R<R> v) {
        return {v[0], v[0], v[0]};
    }

    template<class R>
    AVML_FINL Vector3R<R> xxy(Vector4R<R> v) {
        return {v[0], v[0], v[1]};
    }

    template<class R>
    AVML_FINL Vector3R<R> xxz(Vector4R<R> v) {
        return {v[0], v[0], v[2]};
    }

    template<class R>
    AVML_FINL Vector3R<R> xxw(Vector4R<R> v) {
        return {v[0], v[0], v[3]};
    }

    template<class R>
    AVML_FINL Vector3R<R> xyx(Vector4R<R> v) {
        return {v[0], v[1], v[0]};
    }

    template<class R>
    AVML_FINL Vector3R<R> xyy(Vector4R<R> v) {
        return {v[0], v[1], v[1]};
    }

    template<class R>
    AVML_FINL Vector3R<R> xyz(Vector4R<R> v) {
        return {v[0], v[1], v[2]};
    }

    template<class R>
    AVML_FINL Vector3R<R> xyw(Vector4R<R> v) {
        return {v[0], v[1], v[3]};
    }

    template<class R>
    AVML_FINL Vector3R<R> xzx(Vector4R<R> v) {
        return {v[0], v[2], v[0]};
    }

    template<class R>
    AVML_FINL Vector3R<R> xzy(Vector4R<R> v) {
        return {v[0], v[2], v[1]};
    }

    template<class R>
    AVML_FINL Vector3R<R> xzz(Vector4R<R> v) {
        return {v[0], v[2], v[2]};
    }

    template<class R>
    AVML_FINL Vector3R<R> xzw(Vector4R<R> v) {
        return {v[0], v[2], v[3]};
    }

    template<class R>
    AVML_FINL Vector3R<R> xwx(Vector4R<R> v) {
        return {v[0], v[3], v[0]};
    }

    template<class R>
    AVML_FINL Vector3R<R> xwy(Vector4R<R> v) {
        return {v[0], v[3], v[1]};
    }

    template<class R>
    AVML_FINL Vector3R<R> xwz(Vector4R<R> v) {
        return {v[0], v[3], v[2]};
    }

    template<class R>
    AVML_FINL Vector3R<R> xww(Vector4R<R> v) {
        return {v[0], v[3], v[3]};
    }

    template<class R>
    AVML_FINL Vector3R<R> yxx(Vector4R<R> v) {
        return {v[1], v[0], v[0]};
    }

    template<class R>
    AVML_FINL Vector3R<R> yxy(Vector4R<R> v) {
        return {v[1], v[0], v[1]};
    }

    template<class R>
    AVML_FINL Vector3R<R> yxz(Vector4R<R> v) {
        return {v[1], v[0], v[2]};
    }

    template<class R>
    AVML_FINL Vector3R<R> yxw(Vector4R<R> v) {
        return {v[1], v[0], v[3]};
    }

    template<class R>
    AVML_FINL Vector3R<R> yyx(Vector4R<R> v) {
        return {v[1], v[1], v[0]};
    }

    template<class R>
    AVML_FINL Vector3R<R> yyy(Vector4R<R> v) {
        return {v[1], v[1], v[1]};
    }

    template<class R>
    AVML_FINL Vector3R<R> yyz(Vector4R<R> v) {
        return {v[1], v[1], v[2]};
    }

    template<class R>
    AVML_FINL Vector3R<R> yyw(Vector4R<R> v) {
        return {v[1], v[1], v[3]};
    }

    template<class R>
    AVML_FINL Vector3R<R> yzx(Vector4R<R> v) {
        return {v[1], v[2], v[0]};
    }

    template<class R>
    AVML_FINL Vector3R<R> yzy(Vector4R<R> v) {
        return {v[1], v[2], v[1]};
    }

    template<class R>
    AVML_FINL Vector3R<R> yzz(Vector4R<R> v) {
        return {v[1], v[2], v[2]};
    }

    template<class R>
    AVML_FINL Vector3R<R> yzw(Vector4R<R> v) {
        return {v[1], v[2], v[3]};
    }

    template<class R>
    AVML_FINL Vector3R<R> ywx(Vector4R<R> v) {
        return {v[1], v[3], v[0]};
    }

    template<class R>
    AVML_FINL Vector3R<R> ywy(Vector4R<R> v) {
        return {v[1], v[3], v[1]};
    }

    template<class R>
    AVML_FINL Vector3R<R> ywz(Vector4R<R> v) {
        return {v[1], v[3], v[2]};
    }

    template<class R>
    AVML_FINL Vector3R<R> yww(Vector4R<R> v) {
        return {v[1], v[3], v[3]};
    }

    template<class R>
    AVML_FINL Vector3R<R> zxx(Vector4R<R> v) {
        return {v[2], v[0], v[0]};
    }

    template<class R>
    AVML_FINL Vector3R<R> zxy(Vector4R<R> v) {
        return {v[2], v[0], v[1]};
    }

    template<class R>
    AVML_FINL Vector3R<R> zxz(Vector4R<R> v) {
        return {v[2], v[0], v[2]};
    }

    template<class R>
    AVML_FINL Vector3R<R> zxw(Vector4R<R> v) {
        return {v[2], v[0], v[3]};
    }

    template<class R>
    AVML_FINL Vector3R<R> zyx(Vector4R<R> v) {
        return {v[2], v[1], v[0]};
    }

    template<class R>
    AVML_FINL Vector3R<R> zyy(Vector4R<R> v) {
        return {v[2], v[1], v[1]};
    }

    template<class R>
    AVML_FINL Vector3R<R> zyz(Vector4R<R> v) {
        return {v[2], v[1], v[2]};
    }

    template<class R>
    AVML_FINL Vector3R<R> zyw(Vector4R<R> v) {
        return {v[2], v[1], v[3]};
    }

    template<class R>
    AVML_FINL Vector3R<R> zzx(Vector4R<R> v) {
        return {v[2], v[2], v[0]};
    }

    template<class R>
    AVML_FINL Vector3R<R> zzy(Vector4R<R> v) {
        return {v[2], v[2], v[1]};
    }

    template<class R>
    AVML_FINL Vector3R<R> zzz(Vector4R<R> v) {
        return {v[2], v[2], v[2]};
    }

    template<class R>
    AVML_FINL Vector3R<R> zzw(Vector4R<R> v) {
        return {v[2], v[2], v[3]};
    }

    template<class R>
    AVML_FINL Vector3R<R> zwx(Vector4R<R> v) {
        return {v[2], v[3], v[0]};
    }

    template<class R>
    AVML_FINL Vector3R<R> zwy(Vector4R<R> v) {
        return {v[2], v[3], v[1]};
    }

    template<class R>
    AVML_FINL Vector3R<R> zwz(Vector4R<R> v) {
        return {v[2], v[3], v[2]};
    }

    template<class R>
    AVML_FINL Vector3R<R> zww(Vector4R<R> v) {
        return {v[2], v[3], v[3]};
    }

    template<class R>
    AVML_FINL Vector3R<R> wxx(Vector4R<R> v) {
        return {v[3], v[0], v[0]};
    }

    template<class R>
    AVML_FINL Vector3R<R> wxy(Vector4R<R> v) {
        return {v[3], v[0], v[1]};
    }

    template<class R>
    AVML_FINL Vector3R<R> wxz(Vector4R<R> v) {
        return {v[3], v[0], v[2]};
    }

    template<class R>
    AVML_FINL Vector3R<R> wxw(Vector4R<R> v) {
        return {v[3], v[0], v[3]};
    }

    template<class R>
    AVML_FINL Vector3R<R> wyx(Vector4R<R> v) {
        return {v[3], v[1], v[0]};
    }

    template<class R>
    AVML_FINL Vector3R<R> wyy(Vector4R<R> v) {
        return {v[3], v[1], v[1]};
    }

    template<class R>
    AVML_FINL Vector3R<R> wyz(Vector4R<R> v) {
        return {v[3], v[1], v[2]};
    }

    template<class R>
    AVML_FINL Vector3R<R> wyw(Vector4R<R> v) {
        return {v[3], v[1], v[3]};
    }

    template<class R>
    AVML_FINL Vector3R<R> wzx(Vector4R<R> v) {
        return {v[3], v[2], v[0]};
    }

    template<class R>
    AVML_FINL Vector3R<R> wzy(Vector4R<R> v) {
        return {v[3], v[2], v[1]};
    }

    template<class R>
    AVML_FINL Vector3R<R> wzz(Vector4R<R> v) {
        return {v[3], v[2], v[2]};
    }

    template<class R>
    AVML_FINL Vector3R<R> wzw(Vector4R<R> v) {
        return {v[3], v[2], v[3]};
    }

    template<class R>
    AVML_FINL Vector3R<R> wwx(Vector4R<R> v) {
        return {v[3], v[3], v[0]};
    }

    template<class R>
    AVML_FINL Vector3R<R> wwy(Vector4R<R> v) {
        return {v[3], v[3], v[1]};
    }

    template<class R>
    AVML_FINL Vector3R<R> wwz(Vector4R<R> v) {
        return {v[3], v[3], v[2]};
    }

    template<class R>
    AVML_FINL Vector3R<R> www(Vector4R<R> v) {
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
    //                    std::string code = "    Vector4R<R> ";
    //
    //                    code += index_to_char(i);
    //                    code += index_to_char(j);
    //                    code += index_to_char(k);
    //                    code += index_to_char(l);
    //
    //                    code += "(Vector4R<R> v) {\n        return {";
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
    AVML_FINL Vector4R<R> xxxx(Vector4R<R> v) {
        return {v[0], v[0], v[0], v[0]};
    }

    template<class R>
    AVML_FINL Vector4R<R> xxxy(Vector4R<R> v) {
        return {v[0], v[0], v[0], v[1]};
    }

    template<class R>
    AVML_FINL Vector4R<R> xxxz(Vector4R<R> v) {
        return {v[0], v[0], v[0], v[2]};
    }

    template<class R>
    AVML_FINL Vector4R<R> xxxw(Vector4R<R> v) {
        return {v[0], v[0], v[0], v[3]};
    }

    template<class R>
    AVML_FINL Vector4R<R> xxyx(Vector4R<R> v) {
        return {v[0], v[0], v[1], v[0]};
    }

    template<class R>
    AVML_FINL Vector4R<R> xxyy(Vector4R<R> v) {
        return {v[0], v[0], v[1], v[1]};
    }

    template<class R>
    AVML_FINL Vector4R<R> xxyz(Vector4R<R> v) {
        return {v[0], v[0], v[1], v[2]};
    }

    template<class R>
    AVML_FINL Vector4R<R> xxyw(Vector4R<R> v) {
        return {v[0], v[0], v[1], v[3]};
    }

    template<class R>
    AVML_FINL Vector4R<R> xxzx(Vector4R<R> v) {
        return {v[0], v[0], v[2], v[0]};
    }

    template<class R>
    AVML_FINL Vector4R<R> xxzy(Vector4R<R> v) {
        return {v[0], v[0], v[2], v[1]};
    }

    template<class R>
    AVML_FINL Vector4R<R> xxzz(Vector4R<R> v) {
        return {v[0], v[0], v[2], v[2]};
    }

    template<class R>
    AVML_FINL Vector4R<R> xxzw(Vector4R<R> v) {
        return {v[0], v[0], v[2], v[3]};
    }

    template<class R>
    AVML_FINL Vector4R<R> xxwx(Vector4R<R> v) {
        return {v[0], v[0], v[3], v[0]};
    }

    template<class R>
    AVML_FINL Vector4R<R> xxwy(Vector4R<R> v) {
        return {v[0], v[0], v[3], v[1]};
    }

    template<class R>
    AVML_FINL Vector4R<R> xxwz(Vector4R<R> v) {
        return {v[0], v[0], v[3], v[2]};
    }

    template<class R>
    AVML_FINL Vector4R<R> xxww(Vector4R<R> v) {
        return {v[0], v[0], v[3], v[3]};
    }

    template<class R>
    AVML_FINL Vector4R<R> xyxx(Vector4R<R> v) {
        return {v[0], v[1], v[0], v[0]};
    }

    template<class R>
    AVML_FINL Vector4R<R> xyxy(Vector4R<R> v) {
        return {v[0], v[1], v[0], v[1]};
    }

    template<class R>
    AVML_FINL Vector4R<R> xyxz(Vector4R<R> v) {
        return {v[0], v[1], v[0], v[2]};
    }

    template<class R>
    AVML_FINL Vector4R<R> xyxw(Vector4R<R> v) {
        return {v[0], v[1], v[0], v[3]};
    }

    template<class R>
    AVML_FINL Vector4R<R> xyyx(Vector4R<R> v) {
        return {v[0], v[1], v[1], v[0]};
    }

    template<class R>
    AVML_FINL Vector4R<R> xyyy(Vector4R<R> v) {
        return {v[0], v[1], v[1], v[1]};
    }

    template<class R>
    AVML_FINL Vector4R<R> xyyz(Vector4R<R> v) {
        return {v[0], v[1], v[1], v[2]};
    }

    template<class R>
    AVML_FINL Vector4R<R> xyyw(Vector4R<R> v) {
        return {v[0], v[1], v[1], v[3]};
    }

    template<class R>
    AVML_FINL Vector4R<R> xyzx(Vector4R<R> v) {
        return {v[0], v[1], v[2], v[0]};
    }

    template<class R>
    AVML_FINL Vector4R<R> xyzy(Vector4R<R> v) {
        return {v[0], v[1], v[2], v[1]};
    }

    template<class R>
    AVML_FINL Vector4R<R> xyzz(Vector4R<R> v) {
        return {v[0], v[1], v[2], v[2]};
    }

    template<class R>
    AVML_FINL Vector4R<R> xyzw(Vector4R<R> v) {
        return {v[0], v[1], v[2], v[3]};
    }

    template<class R>
    AVML_FINL Vector4R<R> xywx(Vector4R<R> v) {
        return {v[0], v[1], v[3], v[0]};
    }

    template<class R>
    AVML_FINL Vector4R<R> xywy(Vector4R<R> v) {
        return {v[0], v[1], v[3], v[1]};
    }

    template<class R>
    AVML_FINL Vector4R<R> xywz(Vector4R<R> v) {
        return {v[0], v[1], v[3], v[2]};
    }

    template<class R>
    AVML_FINL Vector4R<R> xyww(Vector4R<R> v) {
        return {v[0], v[1], v[3], v[3]};
    }

    template<class R>
    AVML_FINL Vector4R<R> xzxx(Vector4R<R> v) {
        return {v[0], v[2], v[0], v[0]};
    }

    template<class R>
    AVML_FINL Vector4R<R> xzxy(Vector4R<R> v) {
        return {v[0], v[2], v[0], v[1]};
    }

    template<class R>
    AVML_FINL Vector4R<R> xzxz(Vector4R<R> v) {
        return {v[0], v[2], v[0], v[2]};
    }

    template<class R>
    AVML_FINL Vector4R<R> xzxw(Vector4R<R> v) {
        return {v[0], v[2], v[0], v[3]};
    }

    template<class R>
    AVML_FINL Vector4R<R> xzyx(Vector4R<R> v) {
        return {v[0], v[2], v[1], v[0]};
    }

    template<class R>
    AVML_FINL Vector4R<R> xzyy(Vector4R<R> v) {
        return {v[0], v[2], v[1], v[1]};
    }

    template<class R>
    AVML_FINL Vector4R<R> xzyz(Vector4R<R> v) {
        return {v[0], v[2], v[1], v[2]};
    }

    template<class R>
    AVML_FINL Vector4R<R> xzyw(Vector4R<R> v) {
        return {v[0], v[2], v[1], v[3]};
    }

    template<class R>
    AVML_FINL Vector4R<R> xzzx(Vector4R<R> v) {
        return {v[0], v[2], v[2], v[0]};
    }

    template<class R>
    AVML_FINL Vector4R<R> xzzy(Vector4R<R> v) {
        return {v[0], v[2], v[2], v[1]};
    }

    template<class R>
    AVML_FINL Vector4R<R> xzzz(Vector4R<R> v) {
        return {v[0], v[2], v[2], v[2]};
    }

    template<class R>
    AVML_FINL Vector4R<R> xzzw(Vector4R<R> v) {
        return {v[0], v[2], v[2], v[3]};
    }

    template<class R>
    AVML_FINL Vector4R<R> xzwx(Vector4R<R> v) {
        return {v[0], v[2], v[3], v[0]};
    }

    template<class R>
    AVML_FINL Vector4R<R> xzwy(Vector4R<R> v) {
        return {v[0], v[2], v[3], v[1]};
    }

    template<class R>
    AVML_FINL Vector4R<R> xzwz(Vector4R<R> v) {
        return {v[0], v[2], v[3], v[2]};
    }

    template<class R>
    AVML_FINL Vector4R<R> xzww(Vector4R<R> v) {
        return {v[0], v[2], v[3], v[3]};
    }

    template<class R>
    AVML_FINL Vector4R<R> xwxx(Vector4R<R> v) {
        return {v[0], v[3], v[0], v[0]};
    }

    template<class R>
    AVML_FINL Vector4R<R> xwxy(Vector4R<R> v) {
        return {v[0], v[3], v[0], v[1]};
    }

    template<class R>
    AVML_FINL Vector4R<R> xwxz(Vector4R<R> v) {
        return {v[0], v[3], v[0], v[2]};
    }

    template<class R>
    AVML_FINL Vector4R<R> xwxw(Vector4R<R> v) {
        return {v[0], v[3], v[0], v[3]};
    }

    template<class R>
    AVML_FINL Vector4R<R> xwyx(Vector4R<R> v) {
        return {v[0], v[3], v[1], v[0]};
    }

    template<class R>
    AVML_FINL Vector4R<R> xwyy(Vector4R<R> v) {
        return {v[0], v[3], v[1], v[1]};
    }

    template<class R>
    AVML_FINL Vector4R<R> xwyz(Vector4R<R> v) {
        return {v[0], v[3], v[1], v[2]};
    }

    template<class R>
    AVML_FINL Vector4R<R> xwyw(Vector4R<R> v) {
        return {v[0], v[3], v[1], v[3]};
    }

    template<class R>
    AVML_FINL Vector4R<R> xwzx(Vector4R<R> v) {
        return {v[0], v[3], v[2], v[0]};
    }

    template<class R>
    AVML_FINL Vector4R<R> xwzy(Vector4R<R> v) {
        return {v[0], v[3], v[2], v[1]};
    }

    template<class R>
    AVML_FINL Vector4R<R> xwzz(Vector4R<R> v) {
        return {v[0], v[3], v[2], v[2]};
    }

    template<class R>
    AVML_FINL Vector4R<R> xwzw(Vector4R<R> v) {
        return {v[0], v[3], v[2], v[3]};
    }

    template<class R>
    AVML_FINL Vector4R<R> xwwx(Vector4R<R> v) {
        return {v[0], v[3], v[3], v[0]};
    }

    template<class R>
    AVML_FINL Vector4R<R> xwwy(Vector4R<R> v) {
        return {v[0], v[3], v[3], v[1]};
    }

    template<class R>
    AVML_FINL Vector4R<R> xwwz(Vector4R<R> v) {
        return {v[0], v[3], v[3], v[2]};
    }

    template<class R>
    AVML_FINL Vector4R<R> xwww(Vector4R<R> v) {
        return {v[0], v[3], v[3], v[3]};
    }

    template<class R>
    AVML_FINL Vector4R<R> yxxx(Vector4R<R> v) {
        return {v[1], v[0], v[0], v[0]};
    }

    template<class R>
    AVML_FINL Vector4R<R> yxxy(Vector4R<R> v) {
        return {v[1], v[0], v[0], v[1]};
    }

    template<class R>
    AVML_FINL Vector4R<R> yxxz(Vector4R<R> v) {
        return {v[1], v[0], v[0], v[2]};
    }

    template<class R>
    AVML_FINL Vector4R<R> yxxw(Vector4R<R> v) {
        return {v[1], v[0], v[0], v[3]};
    }

    template<class R>
    AVML_FINL Vector4R<R> yxyx(Vector4R<R> v) {
        return {v[1], v[0], v[1], v[0]};
    }

    template<class R>
    AVML_FINL Vector4R<R> yxyy(Vector4R<R> v) {
        return {v[1], v[0], v[1], v[1]};
    }

    template<class R>
    AVML_FINL Vector4R<R> yxyz(Vector4R<R> v) {
        return {v[1], v[0], v[1], v[2]};
    }

    template<class R>
    AVML_FINL Vector4R<R> yxyw(Vector4R<R> v) {
        return {v[1], v[0], v[1], v[3]};
    }

    template<class R>
    AVML_FINL Vector4R<R> yxzx(Vector4R<R> v) {
        return {v[1], v[0], v[2], v[0]};
    }

    template<class R>
    AVML_FINL Vector4R<R> yxzy(Vector4R<R> v) {
        return {v[1], v[0], v[2], v[1]};
    }

    template<class R>
    AVML_FINL Vector4R<R> yxzz(Vector4R<R> v) {
        return {v[1], v[0], v[2], v[2]};
    }

    template<class R>
    AVML_FINL Vector4R<R> yxzw(Vector4R<R> v) {
        return {v[1], v[0], v[2], v[3]};
    }

    template<class R>
    AVML_FINL Vector4R<R> yxwx(Vector4R<R> v) {
        return {v[1], v[0], v[3], v[0]};
    }

    template<class R>
    AVML_FINL Vector4R<R> yxwy(Vector4R<R> v) {
        return {v[1], v[0], v[3], v[1]};
    }

    template<class R>
    AVML_FINL Vector4R<R> yxwz(Vector4R<R> v) {
        return {v[1], v[0], v[3], v[2]};
    }

    template<class R>
    AVML_FINL Vector4R<R> yxww(Vector4R<R> v) {
        return {v[1], v[0], v[3], v[3]};
    }

    template<class R>
    AVML_FINL Vector4R<R> yyxx(Vector4R<R> v) {
        return {v[1], v[1], v[0], v[0]};
    }

    template<class R>
    AVML_FINL Vector4R<R> yyxy(Vector4R<R> v) {
        return {v[1], v[1], v[0], v[1]};
    }

    template<class R>
    AVML_FINL Vector4R<R> yyxz(Vector4R<R> v) {
        return {v[1], v[1], v[0], v[2]};
    }

    template<class R>
    AVML_FINL Vector4R<R> yyxw(Vector4R<R> v) {
        return {v[1], v[1], v[0], v[3]};
    }

    template<class R>
    AVML_FINL Vector4R<R> yyyx(Vector4R<R> v) {
        return {v[1], v[1], v[1], v[0]};
    }

    template<class R>
    AVML_FINL Vector4R<R> yyyy(Vector4R<R> v) {
        return {v[1], v[1], v[1], v[1]};
    }

    template<class R>
    AVML_FINL Vector4R<R> yyyz(Vector4R<R> v) {
        return {v[1], v[1], v[1], v[2]};
    }

    template<class R>
    AVML_FINL Vector4R<R> yyyw(Vector4R<R> v) {
        return {v[1], v[1], v[1], v[3]};
    }

    template<class R>
    AVML_FINL Vector4R<R> yyzx(Vector4R<R> v) {
        return {v[1], v[1], v[2], v[0]};
    }

    template<class R>
    AVML_FINL Vector4R<R> yyzy(Vector4R<R> v) {
        return {v[1], v[1], v[2], v[1]};
    }

    template<class R>
    AVML_FINL Vector4R<R> yyzz(Vector4R<R> v) {
        return {v[1], v[1], v[2], v[2]};
    }

    template<class R>
    AVML_FINL Vector4R<R> yyzw(Vector4R<R> v) {
        return {v[1], v[1], v[2], v[3]};
    }

    template<class R>
    AVML_FINL Vector4R<R> yywx(Vector4R<R> v) {
        return {v[1], v[1], v[3], v[0]};
    }

    template<class R>
    AVML_FINL Vector4R<R> yywy(Vector4R<R> v) {
        return {v[1], v[1], v[3], v[1]};
    }

    template<class R>
    AVML_FINL Vector4R<R> yywz(Vector4R<R> v) {
        return {v[1], v[1], v[3], v[2]};
    }

    template<class R>
    AVML_FINL Vector4R<R> yyww(Vector4R<R> v) {
        return {v[1], v[1], v[3], v[3]};
    }

    template<class R>
    AVML_FINL Vector4R<R> yzxx(Vector4R<R> v) {
        return {v[1], v[2], v[0], v[0]};
    }

    template<class R>
    AVML_FINL Vector4R<R> yzxy(Vector4R<R> v) {
        return {v[1], v[2], v[0], v[1]};
    }

    template<class R>
    AVML_FINL Vector4R<R> yzxz(Vector4R<R> v) {
        return {v[1], v[2], v[0], v[2]};
    }

    template<class R>
    AVML_FINL Vector4R<R> yzxw(Vector4R<R> v) {
        return {v[1], v[2], v[0], v[3]};
    }

    template<class R>
    AVML_FINL Vector4R<R> yzyx(Vector4R<R> v) {
        return {v[1], v[2], v[1], v[0]};
    }

    template<class R>
    AVML_FINL Vector4R<R> yzyy(Vector4R<R> v) {
        return {v[1], v[2], v[1], v[1]};
    }

    template<class R>
    AVML_FINL Vector4R<R> yzyz(Vector4R<R> v) {
        return {v[1], v[2], v[1], v[2]};
    }

    template<class R>
    AVML_FINL Vector4R<R> yzyw(Vector4R<R> v) {
        return {v[1], v[2], v[1], v[3]};
    }

    template<class R>
    AVML_FINL Vector4R<R> yzzx(Vector4R<R> v) {
        return {v[1], v[2], v[2], v[0]};
    }

    template<class R>
    AVML_FINL Vector4R<R> yzzy(Vector4R<R> v) {
        return {v[1], v[2], v[2], v[1]};
    }

    template<class R>
    AVML_FINL Vector4R<R> yzzz(Vector4R<R> v) {
        return {v[1], v[2], v[2], v[2]};
    }

    template<class R>
    AVML_FINL Vector4R<R> yzzw(Vector4R<R> v) {
        return {v[1], v[2], v[2], v[3]};
    }

    template<class R>
    AVML_FINL Vector4R<R> yzwx(Vector4R<R> v) {
        return {v[1], v[2], v[3], v[0]};
    }

    template<class R>
    AVML_FINL Vector4R<R> yzwy(Vector4R<R> v) {
        return {v[1], v[2], v[3], v[1]};
    }

    template<class R>
    AVML_FINL Vector4R<R> yzwz(Vector4R<R> v) {
        return {v[1], v[2], v[3], v[2]};
    }

    template<class R>
    AVML_FINL Vector4R<R> yzww(Vector4R<R> v) {
        return {v[1], v[2], v[3], v[3]};
    }

    template<class R>
    AVML_FINL Vector4R<R> ywxx(Vector4R<R> v) {
        return {v[1], v[3], v[0], v[0]};
    }

    template<class R>
    AVML_FINL Vector4R<R> ywxy(Vector4R<R> v) {
        return {v[1], v[3], v[0], v[1]};
    }

    template<class R>
    AVML_FINL Vector4R<R> ywxz(Vector4R<R> v) {
        return {v[1], v[3], v[0], v[2]};
    }

    template<class R>
    AVML_FINL Vector4R<R> ywxw(Vector4R<R> v) {
        return {v[1], v[3], v[0], v[3]};
    }

    template<class R>
    AVML_FINL Vector4R<R> ywyx(Vector4R<R> v) {
        return {v[1], v[3], v[1], v[0]};
    }

    template<class R>
    AVML_FINL Vector4R<R> ywyy(Vector4R<R> v) {
        return {v[1], v[3], v[1], v[1]};
    }

    template<class R>
    AVML_FINL Vector4R<R> ywyz(Vector4R<R> v) {
        return {v[1], v[3], v[1], v[2]};
    }

    template<class R>
    AVML_FINL Vector4R<R> ywyw(Vector4R<R> v) {
        return {v[1], v[3], v[1], v[3]};
    }

    template<class R>
    AVML_FINL Vector4R<R> ywzx(Vector4R<R> v) {
        return {v[1], v[3], v[2], v[0]};
    }

    template<class R>
    AVML_FINL Vector4R<R> ywzy(Vector4R<R> v) {
        return {v[1], v[3], v[2], v[1]};
    }

    template<class R>
    AVML_FINL Vector4R<R> ywzz(Vector4R<R> v) {
        return {v[1], v[3], v[2], v[2]};
    }

    template<class R>
    AVML_FINL Vector4R<R> ywzw(Vector4R<R> v) {
        return {v[1], v[3], v[2], v[3]};
    }

    template<class R>
    AVML_FINL Vector4R<R> ywwx(Vector4R<R> v) {
        return {v[1], v[3], v[3], v[0]};
    }

    template<class R>
    AVML_FINL Vector4R<R> ywwy(Vector4R<R> v) {
        return {v[1], v[3], v[3], v[1]};
    }

    template<class R>
    AVML_FINL Vector4R<R> ywwz(Vector4R<R> v) {
        return {v[1], v[3], v[3], v[2]};
    }

    template<class R>
    AVML_FINL Vector4R<R> ywww(Vector4R<R> v) {
        return {v[1], v[3], v[3], v[3]};
    }

    template<class R>
    AVML_FINL Vector4R<R> zxxx(Vector4R<R> v) {
        return {v[2], v[0], v[0], v[0]};
    }

    template<class R>
    AVML_FINL Vector4R<R> zxxy(Vector4R<R> v) {
        return {v[2], v[0], v[0], v[1]};
    }

    template<class R>
    AVML_FINL Vector4R<R> zxxz(Vector4R<R> v) {
        return {v[2], v[0], v[0], v[2]};
    }

    template<class R>
    AVML_FINL Vector4R<R> zxxw(Vector4R<R> v) {
        return {v[2], v[0], v[0], v[3]};
    }

    template<class R>
    AVML_FINL Vector4R<R> zxyx(Vector4R<R> v) {
        return {v[2], v[0], v[1], v[0]};
    }

    template<class R>
    AVML_FINL Vector4R<R> zxyy(Vector4R<R> v) {
        return {v[2], v[0], v[1], v[1]};
    }

    template<class R>
    AVML_FINL Vector4R<R> zxyz(Vector4R<R> v) {
        return {v[2], v[0], v[1], v[2]};
    }

    template<class R>
    AVML_FINL Vector4R<R> zxyw(Vector4R<R> v) {
        return {v[2], v[0], v[1], v[3]};
    }

    template<class R>
    AVML_FINL Vector4R<R> zxzx(Vector4R<R> v) {
        return {v[2], v[0], v[2], v[0]};
    }

    template<class R>
    AVML_FINL Vector4R<R> zxzy(Vector4R<R> v) {
        return {v[2], v[0], v[2], v[1]};
    }

    template<class R>
    AVML_FINL Vector4R<R> zxzz(Vector4R<R> v) {
        return {v[2], v[0], v[2], v[2]};
    }

    template<class R>
    AVML_FINL Vector4R<R> zxzw(Vector4R<R> v) {
        return {v[2], v[0], v[2], v[3]};
    }

    template<class R>
    AVML_FINL Vector4R<R> zxwx(Vector4R<R> v) {
        return {v[2], v[0], v[3], v[0]};
    }

    template<class R>
    AVML_FINL Vector4R<R> zxwy(Vector4R<R> v) {
        return {v[2], v[0], v[3], v[1]};
    }

    template<class R>
    AVML_FINL Vector4R<R> zxwz(Vector4R<R> v) {
        return {v[2], v[0], v[3], v[2]};
    }

    template<class R>
    AVML_FINL Vector4R<R> zxww(Vector4R<R> v) {
        return {v[2], v[0], v[3], v[3]};
    }

    template<class R>
    AVML_FINL Vector4R<R> zyxx(Vector4R<R> v) {
        return {v[2], v[1], v[0], v[0]};
    }

    template<class R>
    AVML_FINL Vector4R<R> zyxy(Vector4R<R> v) {
        return {v[2], v[1], v[0], v[1]};
    }

    template<class R>
    AVML_FINL Vector4R<R> zyxz(Vector4R<R> v) {
        return {v[2], v[1], v[0], v[2]};
    }

    template<class R>
    AVML_FINL Vector4R<R> zyxw(Vector4R<R> v) {
        return {v[2], v[1], v[0], v[3]};
    }

    template<class R>
    AVML_FINL Vector4R<R> zyyx(Vector4R<R> v) {
        return {v[2], v[1], v[1], v[0]};
    }

    template<class R>
    AVML_FINL Vector4R<R> zyyy(Vector4R<R> v) {
        return {v[2], v[1], v[1], v[1]};
    }

    template<class R>
    AVML_FINL Vector4R<R> zyyz(Vector4R<R> v) {
        return {v[2], v[1], v[1], v[2]};
    }

    template<class R>
    AVML_FINL Vector4R<R> zyyw(Vector4R<R> v) {
        return {v[2], v[1], v[1], v[3]};
    }

    template<class R>
    AVML_FINL Vector4R<R> zyzx(Vector4R<R> v) {
        return {v[2], v[1], v[2], v[0]};
    }

    template<class R>
    AVML_FINL Vector4R<R> zyzy(Vector4R<R> v) {
        return {v[2], v[1], v[2], v[1]};
    }

    template<class R>
    AVML_FINL Vector4R<R> zyzz(Vector4R<R> v) {
        return {v[2], v[1], v[2], v[2]};
    }

    template<class R>
    AVML_FINL Vector4R<R> zyzw(Vector4R<R> v) {
        return {v[2], v[1], v[2], v[3]};
    }

    template<class R>
    AVML_FINL Vector4R<R> zywx(Vector4R<R> v) {
        return {v[2], v[1], v[3], v[0]};
    }

    template<class R>
    AVML_FINL Vector4R<R> zywy(Vector4R<R> v) {
        return {v[2], v[1], v[3], v[1]};
    }

    template<class R>
    AVML_FINL Vector4R<R> zywz(Vector4R<R> v) {
        return {v[2], v[1], v[3], v[2]};
    }

    template<class R>
    AVML_FINL Vector4R<R> zyww(Vector4R<R> v) {
        return {v[2], v[1], v[3], v[3]};
    }

    template<class R>
    AVML_FINL Vector4R<R> zzxx(Vector4R<R> v) {
        return {v[2], v[2], v[0], v[0]};
    }

    template<class R>
    AVML_FINL Vector4R<R> zzxy(Vector4R<R> v) {
        return {v[2], v[2], v[0], v[1]};
    }

    template<class R>
    AVML_FINL Vector4R<R> zzxz(Vector4R<R> v) {
        return {v[2], v[2], v[0], v[2]};
    }

    template<class R>
    AVML_FINL Vector4R<R> zzxw(Vector4R<R> v) {
        return {v[2], v[2], v[0], v[3]};
    }

    template<class R>
    AVML_FINL Vector4R<R> zzyx(Vector4R<R> v) {
        return {v[2], v[2], v[1], v[0]};
    }

    template<class R>
    AVML_FINL Vector4R<R> zzyy(Vector4R<R> v) {
        return {v[2], v[2], v[1], v[1]};
    }

    template<class R>
    AVML_FINL Vector4R<R> zzyz(Vector4R<R> v) {
        return {v[2], v[2], v[1], v[2]};
    }

    template<class R>
    AVML_FINL Vector4R<R> zzyw(Vector4R<R> v) {
        return {v[2], v[2], v[1], v[3]};
    }

    template<class R>
    AVML_FINL Vector4R<R> zzzx(Vector4R<R> v) {
        return {v[2], v[2], v[2], v[0]};
    }

    template<class R>
    AVML_FINL Vector4R<R> zzzy(Vector4R<R> v) {
        return {v[2], v[2], v[2], v[1]};
    }

    template<class R>
    AVML_FINL Vector4R<R> zzzz(Vector4R<R> v) {
        return {v[2], v[2], v[2], v[2]};
    }

    template<class R>
    AVML_FINL Vector4R<R> zzzw(Vector4R<R> v) {
        return {v[2], v[2], v[2], v[3]};
    }

    template<class R>
    AVML_FINL Vector4R<R> zzwx(Vector4R<R> v) {
        return {v[2], v[2], v[3], v[0]};
    }

    template<class R>
    AVML_FINL Vector4R<R> zzwy(Vector4R<R> v) {
        return {v[2], v[2], v[3], v[1]};
    }

    template<class R>
    AVML_FINL Vector4R<R> zzwz(Vector4R<R> v) {
        return {v[2], v[2], v[3], v[2]};
    }

    template<class R>
    AVML_FINL Vector4R<R> zzww(Vector4R<R> v) {
        return {v[2], v[2], v[3], v[3]};
    }

    template<class R>
    AVML_FINL Vector4R<R> zwxx(Vector4R<R> v) {
        return {v[2], v[3], v[0], v[0]};
    }

    template<class R>
    AVML_FINL Vector4R<R> zwxy(Vector4R<R> v) {
        return {v[2], v[3], v[0], v[1]};
    }

    template<class R>
    AVML_FINL Vector4R<R> zwxz(Vector4R<R> v) {
        return {v[2], v[3], v[0], v[2]};
    }

    template<class R>
    AVML_FINL Vector4R<R> zwxw(Vector4R<R> v) {
        return {v[2], v[3], v[0], v[3]};
    }

    template<class R>
    AVML_FINL Vector4R<R> zwyx(Vector4R<R> v) {
        return {v[2], v[3], v[1], v[0]};
    }

    template<class R>
    AVML_FINL Vector4R<R> zwyy(Vector4R<R> v) {
        return {v[2], v[3], v[1], v[1]};
    }

    template<class R>
    AVML_FINL Vector4R<R> zwyz(Vector4R<R> v) {
        return {v[2], v[3], v[1], v[2]};
    }

    template<class R>
    AVML_FINL Vector4R<R> zwyw(Vector4R<R> v) {
        return {v[2], v[3], v[1], v[3]};
    }

    template<class R>
    AVML_FINL Vector4R<R> zwzx(Vector4R<R> v) {
        return {v[2], v[3], v[2], v[0]};
    }

    template<class R>
    AVML_FINL Vector4R<R> zwzy(Vector4R<R> v) {
        return {v[2], v[3], v[2], v[1]};
    }

    template<class R>
    AVML_FINL Vector4R<R> zwzz(Vector4R<R> v) {
        return {v[2], v[3], v[2], v[2]};
    }

    template<class R>
    AVML_FINL Vector4R<R> zwzw(Vector4R<R> v) {
        return {v[2], v[3], v[2], v[3]};
    }

    template<class R>
    AVML_FINL Vector4R<R> zwwx(Vector4R<R> v) {
        return {v[2], v[3], v[3], v[0]};
    }

    template<class R>
    AVML_FINL Vector4R<R> zwwy(Vector4R<R> v) {
        return {v[2], v[3], v[3], v[1]};
    }

    template<class R>
    AVML_FINL Vector4R<R> zwwz(Vector4R<R> v) {
        return {v[2], v[3], v[3], v[2]};
    }

    template<class R>
    AVML_FINL Vector4R<R> zwww(Vector4R<R> v) {
        return {v[2], v[3], v[3], v[3]};
    }

    template<class R>
    AVML_FINL Vector4R<R> wxxx(Vector4R<R> v) {
        return {v[3], v[0], v[0], v[0]};
    }

    template<class R>
    AVML_FINL Vector4R<R> wxxy(Vector4R<R> v) {
        return {v[3], v[0], v[0], v[1]};
    }

    template<class R>
    AVML_FINL Vector4R<R> wxxz(Vector4R<R> v) {
        return {v[3], v[0], v[0], v[2]};
    }

    template<class R>
    AVML_FINL Vector4R<R> wxxw(Vector4R<R> v) {
        return {v[3], v[0], v[0], v[3]};
    }

    template<class R>
    AVML_FINL Vector4R<R> wxyx(Vector4R<R> v) {
        return {v[3], v[0], v[1], v[0]};
    }

    template<class R>
    AVML_FINL Vector4R<R> wxyy(Vector4R<R> v) {
        return {v[3], v[0], v[1], v[1]};
    }

    template<class R>
    AVML_FINL Vector4R<R> wxyz(Vector4R<R> v) {
        return {v[3], v[0], v[1], v[2]};
    }

    template<class R>
    AVML_FINL Vector4R<R> wxyw(Vector4R<R> v) {
        return {v[3], v[0], v[1], v[3]};
    }

    template<class R>
    AVML_FINL Vector4R<R> wxzx(Vector4R<R> v) {
        return {v[3], v[0], v[2], v[0]};
    }

    template<class R>
    AVML_FINL Vector4R<R> wxzy(Vector4R<R> v) {
        return {v[3], v[0], v[2], v[1]};
    }

    template<class R>
    AVML_FINL Vector4R<R> wxzz(Vector4R<R> v) {
        return {v[3], v[0], v[2], v[2]};
    }

    template<class R>
    AVML_FINL Vector4R<R> wxzw(Vector4R<R> v) {
        return {v[3], v[0], v[2], v[3]};
    }

    template<class R>
    AVML_FINL Vector4R<R> wxwx(Vector4R<R> v) {
        return {v[3], v[0], v[3], v[0]};
    }

    template<class R>
    AVML_FINL Vector4R<R> wxwy(Vector4R<R> v) {
        return {v[3], v[0], v[3], v[1]};
    }

    template<class R>
    AVML_FINL Vector4R<R> wxwz(Vector4R<R> v) {
        return {v[3], v[0], v[3], v[2]};
    }

    template<class R>
    AVML_FINL Vector4R<R> wxww(Vector4R<R> v) {
        return {v[3], v[0], v[3], v[3]};
    }

    template<class R>
    AVML_FINL Vector4R<R> wyxx(Vector4R<R> v) {
        return {v[3], v[1], v[0], v[0]};
    }

    template<class R>
    AVML_FINL Vector4R<R> wyxy(Vector4R<R> v) {
        return {v[3], v[1], v[0], v[1]};
    }

    template<class R>
    AVML_FINL Vector4R<R> wyxz(Vector4R<R> v) {
        return {v[3], v[1], v[0], v[2]};
    }

    template<class R>
    AVML_FINL Vector4R<R> wyxw(Vector4R<R> v) {
        return {v[3], v[1], v[0], v[3]};
    }

    template<class R>
    AVML_FINL Vector4R<R> wyyx(Vector4R<R> v) {
        return {v[3], v[1], v[1], v[0]};
    }

    template<class R>
    AVML_FINL Vector4R<R> wyyy(Vector4R<R> v) {
        return {v[3], v[1], v[1], v[1]};
    }

    template<class R>
    AVML_FINL Vector4R<R> wyyz(Vector4R<R> v) {
        return {v[3], v[1], v[1], v[2]};
    }

    template<class R>
    AVML_FINL Vector4R<R> wyyw(Vector4R<R> v) {
        return {v[3], v[1], v[1], v[3]};
    }

    template<class R>
    AVML_FINL Vector4R<R> wyzx(Vector4R<R> v) {
        return {v[3], v[1], v[2], v[0]};
    }

    template<class R>
    AVML_FINL Vector4R<R> wyzy(Vector4R<R> v) {
        return {v[3], v[1], v[2], v[1]};
    }

    template<class R>
    AVML_FINL Vector4R<R> wyzz(Vector4R<R> v) {
        return {v[3], v[1], v[2], v[2]};
    }

    template<class R>
    AVML_FINL Vector4R<R> wyzw(Vector4R<R> v) {
        return {v[3], v[1], v[2], v[3]};
    }

    template<class R>
    AVML_FINL Vector4R<R> wywx(Vector4R<R> v) {
        return {v[3], v[1], v[3], v[0]};
    }

    template<class R>
    AVML_FINL Vector4R<R> wywy(Vector4R<R> v) {
        return {v[3], v[1], v[3], v[1]};
    }

    template<class R>
    AVML_FINL Vector4R<R> wywz(Vector4R<R> v) {
        return {v[3], v[1], v[3], v[2]};
    }

    template<class R>
    AVML_FINL Vector4R<R> wyww(Vector4R<R> v) {
        return {v[3], v[1], v[3], v[3]};
    }

    template<class R>
    AVML_FINL Vector4R<R> wzxx(Vector4R<R> v) {
        return {v[3], v[2], v[0], v[0]};
    }

    template<class R>
    AVML_FINL Vector4R<R> wzxy(Vector4R<R> v) {
        return {v[3], v[2], v[0], v[1]};
    }

    template<class R>
    AVML_FINL Vector4R<R> wzxz(Vector4R<R> v) {
        return {v[3], v[2], v[0], v[2]};
    }

    template<class R>
    AVML_FINL Vector4R<R> wzxw(Vector4R<R> v) {
        return {v[3], v[2], v[0], v[3]};
    }

    template<class R>
    AVML_FINL Vector4R<R> wzyx(Vector4R<R> v) {
        return {v[3], v[2], v[1], v[0]};
    }

    template<class R>
    AVML_FINL Vector4R<R> wzyy(Vector4R<R> v) {
        return {v[3], v[2], v[1], v[1]};
    }

    template<class R>
    AVML_FINL Vector4R<R> wzyz(Vector4R<R> v) {
        return {v[3], v[2], v[1], v[2]};
    }

    template<class R>
    AVML_FINL Vector4R<R> wzyw(Vector4R<R> v) {
        return {v[3], v[2], v[1], v[3]};
    }

    template<class R>
    AVML_FINL Vector4R<R> wzzx(Vector4R<R> v) {
        return {v[3], v[2], v[2], v[0]};
    }

    template<class R>
    AVML_FINL Vector4R<R> wzzy(Vector4R<R> v) {
        return {v[3], v[2], v[2], v[1]};
    }

    template<class R>
    AVML_FINL Vector4R<R> wzzz(Vector4R<R> v) {
        return {v[3], v[2], v[2], v[2]};
    }

    template<class R>
    AVML_FINL Vector4R<R> wzzw(Vector4R<R> v) {
        return {v[3], v[2], v[2], v[3]};
    }

    template<class R>
    AVML_FINL Vector4R<R> wzwx(Vector4R<R> v) {
        return {v[3], v[2], v[3], v[0]};
    }

    template<class R>
    AVML_FINL Vector4R<R> wzwy(Vector4R<R> v) {
        return {v[3], v[2], v[3], v[1]};
    }

    template<class R>
    AVML_FINL Vector4R<R> wzwz(Vector4R<R> v) {
        return {v[3], v[2], v[3], v[2]};
    }

    template<class R>
    AVML_FINL Vector4R<R> wzww(Vector4R<R> v) {
        return {v[3], v[2], v[3], v[3]};
    }

    template<class R>
    AVML_FINL Vector4R<R> wwxx(Vector4R<R> v) {
        return {v[3], v[3], v[0], v[0]};
    }

    template<class R>
    AVML_FINL Vector4R<R> wwxy(Vector4R<R> v) {
        return {v[3], v[3], v[0], v[1]};
    }

    template<class R>
    AVML_FINL Vector4R<R> wwxz(Vector4R<R> v) {
        return {v[3], v[3], v[0], v[2]};
    }

    template<class R>
    AVML_FINL Vector4R<R> wwxw(Vector4R<R> v) {
        return {v[3], v[3], v[0], v[3]};
    }

    template<class R>
    AVML_FINL Vector4R<R> wwyx(Vector4R<R> v) {
        return {v[3], v[3], v[1], v[0]};
    }

    template<class R>
    AVML_FINL Vector4R<R> wwyy(Vector4R<R> v) {
        return {v[3], v[3], v[1], v[1]};
    }

    template<class R>
    AVML_FINL Vector4R<R> wwyz(Vector4R<R> v) {
        return {v[3], v[3], v[1], v[2]};
    }

    template<class R>
    AVML_FINL Vector4R<R> wwyw(Vector4R<R> v) {
        return {v[3], v[3], v[1], v[3]};
    }

    template<class R>
    AVML_FINL Vector4R<R> wwzx(Vector4R<R> v) {
        return {v[3], v[3], v[2], v[0]};
    }

    template<class R>
    AVML_FINL Vector4R<R> wwzy(Vector4R<R> v) {
        return {v[3], v[3], v[2], v[1]};
    }

    template<class R>
    AVML_FINL Vector4R<R> wwzz(Vector4R<R> v) {
        return {v[3], v[3], v[2], v[2]};
    }

    template<class R>
    AVML_FINL Vector4R<R> wwzw(Vector4R<R> v) {
        return {v[3], v[3], v[2], v[3]};
    }

    template<class R>
    AVML_FINL Vector4R<R> wwwx(Vector4R<R> v) {
        return {v[3], v[3], v[3], v[0]};
    }

    template<class R>
    AVML_FINL Vector4R<R> wwwy(Vector4R<R> v) {
        return {v[3], v[3], v[3], v[1]};
    }

    template<class R>
    AVML_FINL Vector4R<R> wwwz(Vector4R<R> v) {
        return {v[3], v[3], v[3], v[2]};
    }

    template<class R>
    AVML_FINL Vector4R<R> wwww(Vector4R<R> v) {
        return {v[3], v[3], v[3], v[3]};
    }

}

#endif
