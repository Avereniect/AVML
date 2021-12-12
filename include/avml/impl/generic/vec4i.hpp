#ifndef AVML_GEN_VEV4I_HPP
#define AVML_GEN_VEC4I_HPP

namespace avml {

    template<class I>
    class alignas(avml_impl::vector_alignment<I, 4>()) Vector4I {
    public:

        using scalar = I;

        static constexpr unsigned width = 4;

        //=================================================
        // Creation functions
        //=================================================

        AVML_FINL static Vector4I read(const I* p) {
            return Vector4I{p[0], p[1], p[2], p[3]};
        }

        AVML_FINL static Vector4I read_aligned(const I* p) {
            return Vector4I{p[0], p[1], p[2], p[3]};
        }

        //=================================================
        // -ctors
        //=================================================

        explicit AVML_FINL Vector4I(I v):
            elements{v, v, v, v} {}

        AVML_FINL Vector4I(I x, I y, I z, I w):
            elements{x, y, z, w} {}

        AVML_FINL Vector4I(Vector2I<I> v, Vector2I<I> u):
            elements{v[0], v[1], u[0], u[1]} {}

        AVML_FINL Vector4I(Vector3I<I> v, I w):
            elements{v[0], v[1], v[2], w} {}

        AVML_FINL Vector4I(I x, Vector3I<I> v):
            elements{x, v[0], v[1], v[2]} {}

        template<class U>
        explicit AVML_FINL Vector4I(Vector4I<U> v):
            elements{
                static_cast<I>(v[0]),
                static_cast<I>(v[1]),
                static_cast<I>(v[2]),
                static_cast<I>(v[3])
            } {}

        template<class R>
        explicit AVML_FINL Vector4I(Vector4R<R> v):
            elements{
                static_cast<I>(v[0]),
                static_cast<I>(v[1]),
                static_cast<I>(v[2]),
                static_cast<I>(v[3])
            } {}

        Vector4I() = default;
        Vector4I(const Vector4I&) = default;
        Vector4I(Vector4I&&) noexcept = default;
        ~Vector4I() = default;

        //=================================================
        // Assignment operators
        //=================================================

        Vector4I& operator=(const Vector4I&) = default;
        Vector4I& operator=(Vector4I&&) noexcept = default;

        //=================================================
        // Unary arithmetic operators
        //=================================================

        AVML_FINL Vector4I operator+() const {
            return *this;
        }

        AVML_FINL Vector4I operator-() const {
            return Vector4I{
                -elements[0],
                -elements[1],
                -elements[2],
                -elements[3]
            };
        }

        //=================================================
        // Arithmetic assignment operators
        //=================================================

        AVML_FINL Vector4I& operator+=(const Vector4I& rhs) {
            for (unsigned i = 0; i < width; ++i) {
                elements[i] += rhs[i];
            }
            return *this;
        }

        AVML_FINL Vector4I& operator-=(const Vector4I& rhs) {
            for (unsigned i = 0; i < width; ++i) {
                elements[i] -= rhs[i];
            }
            return *this;
        }

        AVML_FINL Vector4I& operator*=(const scalar rhs) {
            for (unsigned i = 0; i < width; ++i) {
                elements[i] *= rhs;
            }
            return *this;
        }

        AVML_FINL Vector4I& operator*=(const Vector4I rhs) {
            for (unsigned i = 0; i < width; ++i) {
                elements[i] *= rhs[i];
            }
            return *this;
        }

        AVML_FINL Vector4I& operator/=(const Vector4I rhs) {
            for (unsigned i = 0; i < width; ++i) {
                elements[i] /= rhs[i];
            }
            return *this;
        }

        AVML_FINL Vector4I& operator/=(const scalar rhs) {
            for (unsigned i = 0; i < width; ++i) {
                elements[i] /= rhs;
            }
            return *this;
        }

        //=================================================
        // Accessors
        //=================================================

        AVML_FINL I& operator[](unsigned i) {
            return elements[i];
        }

        AVML_FINL const I& operator[](unsigned i) const {
            return elements[i];
        }

        AVML_FINL I* data() {
            return elements;
        }

        AVML_FINL const I* data() const {
            return elements;
        }

    private:

        //=================================================
        // Instance members
        //=================================================

        I elements[width] = {0.0f, 0.0f, 0.0f, 0.0f};

    };

    //=====================================================
    // Comparison operators
    //=====================================================

    template<class I>
    AVML_FINL bool operator==(Vector4I<I> lhs, Vector4I<I> rhs) {
        return
            (lhs[0] == rhs[0]) &&
            (lhs[1] == rhs[1]) &&
            (lhs[2] == rhs[2]) &&
            (lhs[3] == rhs[3]);
    }

    template<class I>
    AVML_FINL bool operator!=(Vector4I<I> lhs, Vector4I<I> rhs) {
        return
            (lhs[0] != rhs[0]) ||
            (lhs[1] != rhs[1]) ||
            (lhs[2] != rhs[2]) ||
            (lhs[3] != rhs[3]);
    }

    //=====================================================
    // Arithmetic operators
    //=====================================================

    template<class I>
    AVML_FINL Vector4I<I> operator+(Vector4I<I> lhs, Vector4I<I> rhs) {
        lhs += rhs;
        return lhs;
    }

    template<class I>
    AVML_FINL Vector4I<I> operator-(Vector4I<I> lhs, Vector4I<I> rhs) {
        lhs -= rhs;
        return lhs;
    }

    template<class I>
    AVML_FINL Vector4I<I> operator*(Vector4I<I> lhs, Vector4I<I> rhs) {
        lhs *= rhs;
        return lhs;
    }

    template<class I>
    AVML_FINL Vector4I<I> operator*(Vector4I<I> lhs, I rhs) {
        lhs *= rhs;
        return lhs;
    }

    template<class I>
    AVML_FINL Vector4I<I> operator*(I lhs, Vector4I<I> rhs) {
        rhs *= lhs;
        return rhs;
    }

    template<class I>
    AVML_FINL Vector4I<I> operator/(Vector4I<I> lhs, I rhs) {
        lhs /= rhs;
        return lhs;
    }

    template<class I>
    AVML_FINL Vector4I<I> operator/(Vector4I<I> lhs, Vector4I<I> rhs) {
        lhs /= rhs;
        return lhs;
    }

    //=====================================================
    // Vector math
    //=====================================================

    template<class I>
    AVML_FINL I dot(Vector4I<I> lhs, Vector4I<I> rhs) {
        return
            lhs[0] * rhs[0] +
            lhs[1] * rhs[1] +
            lhs[2] * rhs[2] +
            lhs[3] * rhs[2];
    }

    template<class I>
    AVML_FINL I length2(Vector4I<I> v) {
        return dot(v, v);
    }

    //=====================================================
    // Vectorized math
    //=====================================================

    template<class I>
    AVML_FINL Vector4I<I> abs(Vector4I<I> v) {
        using std::abs;
        v[0] = abs(v[0]);
        v[1] = abs(v[1]);
        v[2] = abs(v[2]);
        v[3] = abs(v[3]);
        return v;
    }

    template<class I>
    AVML_FINL Vector4I<I> max(Vector4I<I> u, Vector4I<I> v) {
        using std::max;
        u[0] = max(u[0], v[0]);
        u[1] = max(u[1], v[1]);
        u[2] = max(u[2], v[2]);
        u[3] = max(u[3], v[3]);
        return u;
    }

    template<class I>
    AVML_FINL Vector4I<I> min(Vector4I<I> u, Vector4I<I> v) {
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

    template<class I>
    AVML_FINL I x(Vector4I<I> v) {
        return v[0];
    }

    template<class I>
    AVML_FINL I y(Vector4I<I> v) {
        return v[1];
    }

    template<class I>
    AVML_FINL I z(Vector4I<I> v) {
        return v[2];
    }

    template<class I>
    AVML_FINL I w(Vector4I<I> v) {
        return v[3];
    }

    // Two components

    template<class I>
    AVML_FINL Vector2I<I> xx(Vector4I<I> v) {
        return {v[0], v[0]};
    }

    template<class I>
    AVML_FINL Vector2I<I> xy(Vector4I<I> v) {
        return {v[0], v[1]};
    }

    template<class I>
    AVML_FINL Vector2I<I> xz(Vector4I<I> v) {
        return {v[0], v[2]};
    }

    template<class I>
    AVML_FINL Vector2I<I> xw(Vector4I<I> v) {
        return {v[0], v[3]};
    }

    template<class I>
    AVML_FINL Vector2I<I> yx(Vector4I<I> v) {
        return {v[1], v[0]};
    }

    template<class I>
    AVML_FINL Vector2I<I> yy(Vector4I<I> v) {
        return {v[1], v[1]};
    }

    template<class I>
    AVML_FINL Vector2I<I> yz(Vector4I<I> v) {
        return {v[1], v[2]};
    }

    template<class I>
    AVML_FINL Vector2I<I> yw(Vector4I<I> v) {
        return {v[1], v[3]};
    }

    template<class I>
    AVML_FINL Vector2I<I> zx(Vector4I<I> v) {
        return {v[2], v[0]};
    }

    template<class I>
    AVML_FINL Vector2I<I> zy(Vector4I<I> v) {
        return {v[2], v[1]};
    }

    template<class I>
    AVML_FINL Vector2I<I> zz(Vector4I<I> v) {
        return {v[2], v[2]};
    }

    template<class I>
    AVML_FINL Vector2I<I> zw(Vector4I<I> v) {
        return {v[2], v[2]};
    }

    template<class I>
    AVML_FINL Vector2I<I> wx(Vector4I<I> v) {
        return {v[3], v[0]};
    }

    template<class I>
    AVML_FINL Vector2I<I> wy(Vector4I<I> v) {
        return {v[3], v[1]};
    }

    template<class I>
    AVML_FINL Vector2I<I> wz(Vector4I<I> v) {
        return {v[3], v[2]};
    }

    template<class I>
    AVML_FINL Vector2I<I> ww(Vector4I<I> v) {
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
//                    std::string code = "    Vector3I<I> ";
//
//                    code += index_to_char(i);
//                    code += index_to_char(j);
//                    code += index_to_char(k);
//
//                    code += "(Vector4I<I> v) {\n        return {";
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


    template<class I>
    AVML_FINL Vector3I<I> xxx(Vector4I<I> v) {
        return {v[0], v[0], v[0]};
    }

    template<class I>
    AVML_FINL Vector3I<I> xxy(Vector4I<I> v) {
        return {v[0], v[0], v[1]};
    }

    template<class I>
    AVML_FINL Vector3I<I> xxz(Vector4I<I> v) {
        return {v[0], v[0], v[2]};
    }

    template<class I>
    AVML_FINL Vector3I<I> xxw(Vector4I<I> v) {
        return {v[0], v[0], v[3]};
    }

    template<class I>
    AVML_FINL Vector3I<I> xyx(Vector4I<I> v) {
        return {v[0], v[1], v[0]};
    }

    template<class I>
    AVML_FINL Vector3I<I> xyy(Vector4I<I> v) {
        return {v[0], v[1], v[1]};
    }

    template<class I>
    AVML_FINL Vector3I<I> xyz(Vector4I<I> v) {
        return {v[0], v[1], v[2]};
    }

    template<class I>
    AVML_FINL Vector3I<I> xyw(Vector4I<I> v) {
        return {v[0], v[1], v[3]};
    }

    template<class I>
    AVML_FINL Vector3I<I> xzx(Vector4I<I> v) {
        return {v[0], v[2], v[0]};
    }

    template<class I>
    AVML_FINL Vector3I<I> xzy(Vector4I<I> v) {
        return {v[0], v[2], v[1]};
    }

    template<class I>
    AVML_FINL Vector3I<I> xzz(Vector4I<I> v) {
        return {v[0], v[2], v[2]};
    }

    template<class I>
    AVML_FINL Vector3I<I> xzw(Vector4I<I> v) {
        return {v[0], v[2], v[3]};
    }

    template<class I>
    AVML_FINL Vector3I<I> xwx(Vector4I<I> v) {
        return {v[0], v[3], v[0]};
    }

    template<class I>
    AVML_FINL Vector3I<I> xwy(Vector4I<I> v) {
        return {v[0], v[3], v[1]};
    }

    template<class I>
    AVML_FINL Vector3I<I> xwz(Vector4I<I> v) {
        return {v[0], v[3], v[2]};
    }

    template<class I>
    AVML_FINL Vector3I<I> xww(Vector4I<I> v) {
        return {v[0], v[3], v[3]};
    }

    template<class I>
    AVML_FINL Vector3I<I> yxx(Vector4I<I> v) {
        return {v[1], v[0], v[0]};
    }

    template<class I>
    AVML_FINL Vector3I<I> yxy(Vector4I<I> v) {
        return {v[1], v[0], v[1]};
    }

    template<class I>
    AVML_FINL Vector3I<I> yxz(Vector4I<I> v) {
        return {v[1], v[0], v[2]};
    }

    template<class I>
    AVML_FINL Vector3I<I> yxw(Vector4I<I> v) {
        return {v[1], v[0], v[3]};
    }

    template<class I>
    AVML_FINL Vector3I<I> yyx(Vector4I<I> v) {
        return {v[1], v[1], v[0]};
    }

    template<class I>
    AVML_FINL Vector3I<I> yyy(Vector4I<I> v) {
        return {v[1], v[1], v[1]};
    }

    template<class I>
    AVML_FINL Vector3I<I> yyz(Vector4I<I> v) {
        return {v[1], v[1], v[2]};
    }

    template<class I>
    AVML_FINL Vector3I<I> yyw(Vector4I<I> v) {
        return {v[1], v[1], v[3]};
    }

    template<class I>
    AVML_FINL Vector3I<I> yzx(Vector4I<I> v) {
        return {v[1], v[2], v[0]};
    }

    template<class I>
    AVML_FINL Vector3I<I> yzy(Vector4I<I> v) {
        return {v[1], v[2], v[1]};
    }

    template<class I>
    AVML_FINL Vector3I<I> yzz(Vector4I<I> v) {
        return {v[1], v[2], v[2]};
    }

    template<class I>
    AVML_FINL Vector3I<I> yzw(Vector4I<I> v) {
        return {v[1], v[2], v[3]};
    }

    template<class I>
    AVML_FINL Vector3I<I> ywx(Vector4I<I> v) {
        return {v[1], v[3], v[0]};
    }

    template<class I>
    AVML_FINL Vector3I<I> ywy(Vector4I<I> v) {
        return {v[1], v[3], v[1]};
    }

    template<class I>
    AVML_FINL Vector3I<I> ywz(Vector4I<I> v) {
        return {v[1], v[3], v[2]};
    }

    template<class I>
    AVML_FINL Vector3I<I> yww(Vector4I<I> v) {
        return {v[1], v[3], v[3]};
    }

    template<class I>
    AVML_FINL Vector3I<I> zxx(Vector4I<I> v) {
        return {v[2], v[0], v[0]};
    }

    template<class I>
    AVML_FINL Vector3I<I> zxy(Vector4I<I> v) {
        return {v[2], v[0], v[1]};
    }

    template<class I>
    AVML_FINL Vector3I<I> zxz(Vector4I<I> v) {
        return {v[2], v[0], v[2]};
    }

    template<class I>
    AVML_FINL Vector3I<I> zxw(Vector4I<I> v) {
        return {v[2], v[0], v[3]};
    }

    template<class I>
    AVML_FINL Vector3I<I> zyx(Vector4I<I> v) {
        return {v[2], v[1], v[0]};
    }

    template<class I>
    AVML_FINL Vector3I<I> zyy(Vector4I<I> v) {
        return {v[2], v[1], v[1]};
    }

    template<class I>
    AVML_FINL Vector3I<I> zyz(Vector4I<I> v) {
        return {v[2], v[1], v[2]};
    }

    template<class I>
    AVML_FINL Vector3I<I> zyw(Vector4I<I> v) {
        return {v[2], v[1], v[3]};
    }

    template<class I>
    AVML_FINL Vector3I<I> zzx(Vector4I<I> v) {
        return {v[2], v[2], v[0]};
    }

    template<class I>
    AVML_FINL Vector3I<I> zzy(Vector4I<I> v) {
        return {v[2], v[2], v[1]};
    }

    template<class I>
    AVML_FINL Vector3I<I> zzz(Vector4I<I> v) {
        return {v[2], v[2], v[2]};
    }

    template<class I>
    AVML_FINL Vector3I<I> zzw(Vector4I<I> v) {
        return {v[2], v[2], v[3]};
    }

    template<class I>
    AVML_FINL Vector3I<I> zwx(Vector4I<I> v) {
        return {v[2], v[3], v[0]};
    }

    template<class I>
    AVML_FINL Vector3I<I> zwy(Vector4I<I> v) {
        return {v[2], v[3], v[1]};
    }

    template<class I>
    AVML_FINL Vector3I<I> zwz(Vector4I<I> v) {
        return {v[2], v[3], v[2]};
    }

    template<class I>
    AVML_FINL Vector3I<I> zww(Vector4I<I> v) {
        return {v[2], v[3], v[3]};
    }

    template<class I>
    AVML_FINL Vector3I<I> wxx(Vector4I<I> v) {
        return {v[3], v[0], v[0]};
    }

    template<class I>
    AVML_FINL Vector3I<I> wxy(Vector4I<I> v) {
        return {v[3], v[0], v[1]};
    }

    template<class I>
    AVML_FINL Vector3I<I> wxz(Vector4I<I> v) {
        return {v[3], v[0], v[2]};
    }

    template<class I>
    AVML_FINL Vector3I<I> wxw(Vector4I<I> v) {
        return {v[3], v[0], v[3]};
    }

    template<class I>
    AVML_FINL Vector3I<I> wyx(Vector4I<I> v) {
        return {v[3], v[1], v[0]};
    }

    template<class I>
    AVML_FINL Vector3I<I> wyy(Vector4I<I> v) {
        return {v[3], v[1], v[1]};
    }

    template<class I>
    AVML_FINL Vector3I<I> wyz(Vector4I<I> v) {
        return {v[3], v[1], v[2]};
    }

    template<class I>
    AVML_FINL Vector3I<I> wyw(Vector4I<I> v) {
        return {v[3], v[1], v[3]};
    }

    template<class I>
    AVML_FINL Vector3I<I> wzx(Vector4I<I> v) {
        return {v[3], v[2], v[0]};
    }

    template<class I>
    AVML_FINL Vector3I<I> wzy(Vector4I<I> v) {
        return {v[3], v[2], v[1]};
    }

    template<class I>
    AVML_FINL Vector3I<I> wzz(Vector4I<I> v) {
        return {v[3], v[2], v[2]};
    }

    template<class I>
    AVML_FINL Vector3I<I> wzw(Vector4I<I> v) {
        return {v[3], v[2], v[3]};
    }

    template<class I>
    AVML_FINL Vector3I<I> wwx(Vector4I<I> v) {
        return {v[3], v[3], v[0]};
    }

    template<class I>
    AVML_FINL Vector3I<I> wwy(Vector4I<I> v) {
        return {v[3], v[3], v[1]};
    }

    template<class I>
    AVML_FINL Vector3I<I> wwz(Vector4I<I> v) {
        return {v[3], v[3], v[2]};
    }

    template<class I>
    AVML_FINL Vector3I<I> www(Vector4I<I> v) {
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
    //                    std::string code = "    Vector4I<I> ";
    //
    //                    code += index_to_char(i);
    //                    code += index_to_char(j);
    //                    code += index_to_char(k);
    //                    code += index_to_char(l);
    //
    //                    code += "(Vector4I<I> v) {\n        return {";
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

    template<class I>
    AVML_FINL Vector4I<I> xxxx(Vector4I<I> v) {
        return {v[0], v[0], v[0], v[0]};
    }

    template<class I>
    AVML_FINL Vector4I<I> xxxy(Vector4I<I> v) {
        return {v[0], v[0], v[0], v[1]};
    }

    template<class I>
    AVML_FINL Vector4I<I> xxxz(Vector4I<I> v) {
        return {v[0], v[0], v[0], v[2]};
    }

    template<class I>
    AVML_FINL Vector4I<I> xxxw(Vector4I<I> v) {
        return {v[0], v[0], v[0], v[3]};
    }

    template<class I>
    AVML_FINL Vector4I<I> xxyx(Vector4I<I> v) {
        return {v[0], v[0], v[1], v[0]};
    }

    template<class I>
    AVML_FINL Vector4I<I> xxyy(Vector4I<I> v) {
        return {v[0], v[0], v[1], v[1]};
    }

    template<class I>
    AVML_FINL Vector4I<I> xxyz(Vector4I<I> v) {
        return {v[0], v[0], v[1], v[2]};
    }

    template<class I>
    AVML_FINL Vector4I<I> xxyw(Vector4I<I> v) {
        return {v[0], v[0], v[1], v[3]};
    }

    template<class I>
    AVML_FINL Vector4I<I> xxzx(Vector4I<I> v) {
        return {v[0], v[0], v[2], v[0]};
    }

    template<class I>
    AVML_FINL Vector4I<I> xxzy(Vector4I<I> v) {
        return {v[0], v[0], v[2], v[1]};
    }

    template<class I>
    AVML_FINL Vector4I<I> xxzz(Vector4I<I> v) {
        return {v[0], v[0], v[2], v[2]};
    }

    template<class I>
    AVML_FINL Vector4I<I> xxzw(Vector4I<I> v) {
        return {v[0], v[0], v[2], v[3]};
    }

    template<class I>
    AVML_FINL Vector4I<I> xxwx(Vector4I<I> v) {
        return {v[0], v[0], v[3], v[0]};
    }

    template<class I>
    AVML_FINL Vector4I<I> xxwy(Vector4I<I> v) {
        return {v[0], v[0], v[3], v[1]};
    }

    template<class I>
    AVML_FINL Vector4I<I> xxwz(Vector4I<I> v) {
        return {v[0], v[0], v[3], v[2]};
    }

    template<class I>
    AVML_FINL Vector4I<I> xxww(Vector4I<I> v) {
        return {v[0], v[0], v[3], v[3]};
    }

    template<class I>
    AVML_FINL Vector4I<I> xyxx(Vector4I<I> v) {
        return {v[0], v[1], v[0], v[0]};
    }

    template<class I>
    AVML_FINL Vector4I<I> xyxy(Vector4I<I> v) {
        return {v[0], v[1], v[0], v[1]};
    }

    template<class I>
    AVML_FINL Vector4I<I> xyxz(Vector4I<I> v) {
        return {v[0], v[1], v[0], v[2]};
    }

    template<class I>
    AVML_FINL Vector4I<I> xyxw(Vector4I<I> v) {
        return {v[0], v[1], v[0], v[3]};
    }

    template<class I>
    AVML_FINL Vector4I<I> xyyx(Vector4I<I> v) {
        return {v[0], v[1], v[1], v[0]};
    }

    template<class I>
    AVML_FINL Vector4I<I> xyyy(Vector4I<I> v) {
        return {v[0], v[1], v[1], v[1]};
    }

    template<class I>
    AVML_FINL Vector4I<I> xyyz(Vector4I<I> v) {
        return {v[0], v[1], v[1], v[2]};
    }

    template<class I>
    AVML_FINL Vector4I<I> xyyw(Vector4I<I> v) {
        return {v[0], v[1], v[1], v[3]};
    }

    template<class I>
    AVML_FINL Vector4I<I> xyzx(Vector4I<I> v) {
        return {v[0], v[1], v[2], v[0]};
    }

    template<class I>
    AVML_FINL Vector4I<I> xyzy(Vector4I<I> v) {
        return {v[0], v[1], v[2], v[1]};
    }

    template<class I>
    AVML_FINL Vector4I<I> xyzz(Vector4I<I> v) {
        return {v[0], v[1], v[2], v[2]};
    }

    template<class I>
    AVML_FINL Vector4I<I> xyzw(Vector4I<I> v) {
        return {v[0], v[1], v[2], v[3]};
    }

    template<class I>
    AVML_FINL Vector4I<I> xywx(Vector4I<I> v) {
        return {v[0], v[1], v[3], v[0]};
    }

    template<class I>
    AVML_FINL Vector4I<I> xywy(Vector4I<I> v) {
        return {v[0], v[1], v[3], v[1]};
    }

    template<class I>
    AVML_FINL Vector4I<I> xywz(Vector4I<I> v) {
        return {v[0], v[1], v[3], v[2]};
    }

    template<class I>
    AVML_FINL Vector4I<I> xyww(Vector4I<I> v) {
        return {v[0], v[1], v[3], v[3]};
    }

    template<class I>
    AVML_FINL Vector4I<I> xzxx(Vector4I<I> v) {
        return {v[0], v[2], v[0], v[0]};
    }

    template<class I>
    AVML_FINL Vector4I<I> xzxy(Vector4I<I> v) {
        return {v[0], v[2], v[0], v[1]};
    }

    template<class I>
    AVML_FINL Vector4I<I> xzxz(Vector4I<I> v) {
        return {v[0], v[2], v[0], v[2]};
    }

    template<class I>
    AVML_FINL Vector4I<I> xzxw(Vector4I<I> v) {
        return {v[0], v[2], v[0], v[3]};
    }

    template<class I>
    AVML_FINL Vector4I<I> xzyx(Vector4I<I> v) {
        return {v[0], v[2], v[1], v[0]};
    }

    template<class I>
    AVML_FINL Vector4I<I> xzyy(Vector4I<I> v) {
        return {v[0], v[2], v[1], v[1]};
    }

    template<class I>
    AVML_FINL Vector4I<I> xzyz(Vector4I<I> v) {
        return {v[0], v[2], v[1], v[2]};
    }

    template<class I>
    AVML_FINL Vector4I<I> xzyw(Vector4I<I> v) {
        return {v[0], v[2], v[1], v[3]};
    }

    template<class I>
    AVML_FINL Vector4I<I> xzzx(Vector4I<I> v) {
        return {v[0], v[2], v[2], v[0]};
    }

    template<class I>
    AVML_FINL Vector4I<I> xzzy(Vector4I<I> v) {
        return {v[0], v[2], v[2], v[1]};
    }

    template<class I>
    AVML_FINL Vector4I<I> xzzz(Vector4I<I> v) {
        return {v[0], v[2], v[2], v[2]};
    }

    template<class I>
    AVML_FINL Vector4I<I> xzzw(Vector4I<I> v) {
        return {v[0], v[2], v[2], v[3]};
    }

    template<class I>
    AVML_FINL Vector4I<I> xzwx(Vector4I<I> v) {
        return {v[0], v[2], v[3], v[0]};
    }

    template<class I>
    AVML_FINL Vector4I<I> xzwy(Vector4I<I> v) {
        return {v[0], v[2], v[3], v[1]};
    }

    template<class I>
    AVML_FINL Vector4I<I> xzwz(Vector4I<I> v) {
        return {v[0], v[2], v[3], v[2]};
    }

    template<class I>
    AVML_FINL Vector4I<I> xzww(Vector4I<I> v) {
        return {v[0], v[2], v[3], v[3]};
    }

    template<class I>
    AVML_FINL Vector4I<I> xwxx(Vector4I<I> v) {
        return {v[0], v[3], v[0], v[0]};
    }

    template<class I>
    AVML_FINL Vector4I<I> xwxy(Vector4I<I> v) {
        return {v[0], v[3], v[0], v[1]};
    }

    template<class I>
    AVML_FINL Vector4I<I> xwxz(Vector4I<I> v) {
        return {v[0], v[3], v[0], v[2]};
    }

    template<class I>
    AVML_FINL Vector4I<I> xwxw(Vector4I<I> v) {
        return {v[0], v[3], v[0], v[3]};
    }

    template<class I>
    AVML_FINL Vector4I<I> xwyx(Vector4I<I> v) {
        return {v[0], v[3], v[1], v[0]};
    }

    template<class I>
    AVML_FINL Vector4I<I> xwyy(Vector4I<I> v) {
        return {v[0], v[3], v[1], v[1]};
    }

    template<class I>
    AVML_FINL Vector4I<I> xwyz(Vector4I<I> v) {
        return {v[0], v[3], v[1], v[2]};
    }

    template<class I>
    AVML_FINL Vector4I<I> xwyw(Vector4I<I> v) {
        return {v[0], v[3], v[1], v[3]};
    }

    template<class I>
    AVML_FINL Vector4I<I> xwzx(Vector4I<I> v) {
        return {v[0], v[3], v[2], v[0]};
    }

    template<class I>
    AVML_FINL Vector4I<I> xwzy(Vector4I<I> v) {
        return {v[0], v[3], v[2], v[1]};
    }

    template<class I>
    AVML_FINL Vector4I<I> xwzz(Vector4I<I> v) {
        return {v[0], v[3], v[2], v[2]};
    }

    template<class I>
    AVML_FINL Vector4I<I> xwzw(Vector4I<I> v) {
        return {v[0], v[3], v[2], v[3]};
    }

    template<class I>
    AVML_FINL Vector4I<I> xwwx(Vector4I<I> v) {
        return {v[0], v[3], v[3], v[0]};
    }

    template<class I>
    AVML_FINL Vector4I<I> xwwy(Vector4I<I> v) {
        return {v[0], v[3], v[3], v[1]};
    }

    template<class I>
    AVML_FINL Vector4I<I> xwwz(Vector4I<I> v) {
        return {v[0], v[3], v[3], v[2]};
    }

    template<class I>
    AVML_FINL Vector4I<I> xwww(Vector4I<I> v) {
        return {v[0], v[3], v[3], v[3]};
    }

    template<class I>
    AVML_FINL Vector4I<I> yxxx(Vector4I<I> v) {
        return {v[1], v[0], v[0], v[0]};
    }

    template<class I>
    AVML_FINL Vector4I<I> yxxy(Vector4I<I> v) {
        return {v[1], v[0], v[0], v[1]};
    }

    template<class I>
    AVML_FINL Vector4I<I> yxxz(Vector4I<I> v) {
        return {v[1], v[0], v[0], v[2]};
    }

    template<class I>
    AVML_FINL Vector4I<I> yxxw(Vector4I<I> v) {
        return {v[1], v[0], v[0], v[3]};
    }

    template<class I>
    AVML_FINL Vector4I<I> yxyx(Vector4I<I> v) {
        return {v[1], v[0], v[1], v[0]};
    }

    template<class I>
    AVML_FINL Vector4I<I> yxyy(Vector4I<I> v) {
        return {v[1], v[0], v[1], v[1]};
    }

    template<class I>
    AVML_FINL Vector4I<I> yxyz(Vector4I<I> v) {
        return {v[1], v[0], v[1], v[2]};
    }

    template<class I>
    AVML_FINL Vector4I<I> yxyw(Vector4I<I> v) {
        return {v[1], v[0], v[1], v[3]};
    }

    template<class I>
    AVML_FINL Vector4I<I> yxzx(Vector4I<I> v) {
        return {v[1], v[0], v[2], v[0]};
    }

    template<class I>
    AVML_FINL Vector4I<I> yxzy(Vector4I<I> v) {
        return {v[1], v[0], v[2], v[1]};
    }

    template<class I>
    AVML_FINL Vector4I<I> yxzz(Vector4I<I> v) {
        return {v[1], v[0], v[2], v[2]};
    }

    template<class I>
    AVML_FINL Vector4I<I> yxzw(Vector4I<I> v) {
        return {v[1], v[0], v[2], v[3]};
    }

    template<class I>
    AVML_FINL Vector4I<I> yxwx(Vector4I<I> v) {
        return {v[1], v[0], v[3], v[0]};
    }

    template<class I>
    AVML_FINL Vector4I<I> yxwy(Vector4I<I> v) {
        return {v[1], v[0], v[3], v[1]};
    }

    template<class I>
    AVML_FINL Vector4I<I> yxwz(Vector4I<I> v) {
        return {v[1], v[0], v[3], v[2]};
    }

    template<class I>
    AVML_FINL Vector4I<I> yxww(Vector4I<I> v) {
        return {v[1], v[0], v[3], v[3]};
    }

    template<class I>
    AVML_FINL Vector4I<I> yyxx(Vector4I<I> v) {
        return {v[1], v[1], v[0], v[0]};
    }

    template<class I>
    AVML_FINL Vector4I<I> yyxy(Vector4I<I> v) {
        return {v[1], v[1], v[0], v[1]};
    }

    template<class I>
    AVML_FINL Vector4I<I> yyxz(Vector4I<I> v) {
        return {v[1], v[1], v[0], v[2]};
    }

    template<class I>
    AVML_FINL Vector4I<I> yyxw(Vector4I<I> v) {
        return {v[1], v[1], v[0], v[3]};
    }

    template<class I>
    AVML_FINL Vector4I<I> yyyx(Vector4I<I> v) {
        return {v[1], v[1], v[1], v[0]};
    }

    template<class I>
    AVML_FINL Vector4I<I> yyyy(Vector4I<I> v) {
        return {v[1], v[1], v[1], v[1]};
    }

    template<class I>
    AVML_FINL Vector4I<I> yyyz(Vector4I<I> v) {
        return {v[1], v[1], v[1], v[2]};
    }

    template<class I>
    AVML_FINL Vector4I<I> yyyw(Vector4I<I> v) {
        return {v[1], v[1], v[1], v[3]};
    }

    template<class I>
    AVML_FINL Vector4I<I> yyzx(Vector4I<I> v) {
        return {v[1], v[1], v[2], v[0]};
    }

    template<class I>
    AVML_FINL Vector4I<I> yyzy(Vector4I<I> v) {
        return {v[1], v[1], v[2], v[1]};
    }

    template<class I>
    AVML_FINL Vector4I<I> yyzz(Vector4I<I> v) {
        return {v[1], v[1], v[2], v[2]};
    }

    template<class I>
    AVML_FINL Vector4I<I> yyzw(Vector4I<I> v) {
        return {v[1], v[1], v[2], v[3]};
    }

    template<class I>
    AVML_FINL Vector4I<I> yywx(Vector4I<I> v) {
        return {v[1], v[1], v[3], v[0]};
    }

    template<class I>
    AVML_FINL Vector4I<I> yywy(Vector4I<I> v) {
        return {v[1], v[1], v[3], v[1]};
    }

    template<class I>
    AVML_FINL Vector4I<I> yywz(Vector4I<I> v) {
        return {v[1], v[1], v[3], v[2]};
    }

    template<class I>
    AVML_FINL Vector4I<I> yyww(Vector4I<I> v) {
        return {v[1], v[1], v[3], v[3]};
    }

    template<class I>
    AVML_FINL Vector4I<I> yzxx(Vector4I<I> v) {
        return {v[1], v[2], v[0], v[0]};
    }

    template<class I>
    AVML_FINL Vector4I<I> yzxy(Vector4I<I> v) {
        return {v[1], v[2], v[0], v[1]};
    }

    template<class I>
    AVML_FINL Vector4I<I> yzxz(Vector4I<I> v) {
        return {v[1], v[2], v[0], v[2]};
    }

    template<class I>
    AVML_FINL Vector4I<I> yzxw(Vector4I<I> v) {
        return {v[1], v[2], v[0], v[3]};
    }

    template<class I>
    AVML_FINL Vector4I<I> yzyx(Vector4I<I> v) {
        return {v[1], v[2], v[1], v[0]};
    }

    template<class I>
    AVML_FINL Vector4I<I> yzyy(Vector4I<I> v) {
        return {v[1], v[2], v[1], v[1]};
    }

    template<class I>
    AVML_FINL Vector4I<I> yzyz(Vector4I<I> v) {
        return {v[1], v[2], v[1], v[2]};
    }

    template<class I>
    AVML_FINL Vector4I<I> yzyw(Vector4I<I> v) {
        return {v[1], v[2], v[1], v[3]};
    }

    template<class I>
    AVML_FINL Vector4I<I> yzzx(Vector4I<I> v) {
        return {v[1], v[2], v[2], v[0]};
    }

    template<class I>
    AVML_FINL Vector4I<I> yzzy(Vector4I<I> v) {
        return {v[1], v[2], v[2], v[1]};
    }

    template<class I>
    AVML_FINL Vector4I<I> yzzz(Vector4I<I> v) {
        return {v[1], v[2], v[2], v[2]};
    }

    template<class I>
    AVML_FINL Vector4I<I> yzzw(Vector4I<I> v) {
        return {v[1], v[2], v[2], v[3]};
    }

    template<class I>
    AVML_FINL Vector4I<I> yzwx(Vector4I<I> v) {
        return {v[1], v[2], v[3], v[0]};
    }

    template<class I>
    AVML_FINL Vector4I<I> yzwy(Vector4I<I> v) {
        return {v[1], v[2], v[3], v[1]};
    }

    template<class I>
    AVML_FINL Vector4I<I> yzwz(Vector4I<I> v) {
        return {v[1], v[2], v[3], v[2]};
    }

    template<class I>
    AVML_FINL Vector4I<I> yzww(Vector4I<I> v) {
        return {v[1], v[2], v[3], v[3]};
    }

    template<class I>
    AVML_FINL Vector4I<I> ywxx(Vector4I<I> v) {
        return {v[1], v[3], v[0], v[0]};
    }

    template<class I>
    AVML_FINL Vector4I<I> ywxy(Vector4I<I> v) {
        return {v[1], v[3], v[0], v[1]};
    }

    template<class I>
    AVML_FINL Vector4I<I> ywxz(Vector4I<I> v) {
        return {v[1], v[3], v[0], v[2]};
    }

    template<class I>
    AVML_FINL Vector4I<I> ywxw(Vector4I<I> v) {
        return {v[1], v[3], v[0], v[3]};
    }

    template<class I>
    AVML_FINL Vector4I<I> ywyx(Vector4I<I> v) {
        return {v[1], v[3], v[1], v[0]};
    }

    template<class I>
    AVML_FINL Vector4I<I> ywyy(Vector4I<I> v) {
        return {v[1], v[3], v[1], v[1]};
    }

    template<class I>
    AVML_FINL Vector4I<I> ywyz(Vector4I<I> v) {
        return {v[1], v[3], v[1], v[2]};
    }

    template<class I>
    AVML_FINL Vector4I<I> ywyw(Vector4I<I> v) {
        return {v[1], v[3], v[1], v[3]};
    }

    template<class I>
    AVML_FINL Vector4I<I> ywzx(Vector4I<I> v) {
        return {v[1], v[3], v[2], v[0]};
    }

    template<class I>
    AVML_FINL Vector4I<I> ywzy(Vector4I<I> v) {
        return {v[1], v[3], v[2], v[1]};
    }

    template<class I>
    AVML_FINL Vector4I<I> ywzz(Vector4I<I> v) {
        return {v[1], v[3], v[2], v[2]};
    }

    template<class I>
    AVML_FINL Vector4I<I> ywzw(Vector4I<I> v) {
        return {v[1], v[3], v[2], v[3]};
    }

    template<class I>
    AVML_FINL Vector4I<I> ywwx(Vector4I<I> v) {
        return {v[1], v[3], v[3], v[0]};
    }

    template<class I>
    AVML_FINL Vector4I<I> ywwy(Vector4I<I> v) {
        return {v[1], v[3], v[3], v[1]};
    }

    template<class I>
    AVML_FINL Vector4I<I> ywwz(Vector4I<I> v) {
        return {v[1], v[3], v[3], v[2]};
    }

    template<class I>
    AVML_FINL Vector4I<I> ywww(Vector4I<I> v) {
        return {v[1], v[3], v[3], v[3]};
    }

    template<class I>
    AVML_FINL Vector4I<I> zxxx(Vector4I<I> v) {
        return {v[2], v[0], v[0], v[0]};
    }

    template<class I>
    AVML_FINL Vector4I<I> zxxy(Vector4I<I> v) {
        return {v[2], v[0], v[0], v[1]};
    }

    template<class I>
    AVML_FINL Vector4I<I> zxxz(Vector4I<I> v) {
        return {v[2], v[0], v[0], v[2]};
    }

    template<class I>
    AVML_FINL Vector4I<I> zxxw(Vector4I<I> v) {
        return {v[2], v[0], v[0], v[3]};
    }

    template<class I>
    AVML_FINL Vector4I<I> zxyx(Vector4I<I> v) {
        return {v[2], v[0], v[1], v[0]};
    }

    template<class I>
    AVML_FINL Vector4I<I> zxyy(Vector4I<I> v) {
        return {v[2], v[0], v[1], v[1]};
    }

    template<class I>
    AVML_FINL Vector4I<I> zxyz(Vector4I<I> v) {
        return {v[2], v[0], v[1], v[2]};
    }

    template<class I>
    AVML_FINL Vector4I<I> zxyw(Vector4I<I> v) {
        return {v[2], v[0], v[1], v[3]};
    }

    template<class I>
    AVML_FINL Vector4I<I> zxzx(Vector4I<I> v) {
        return {v[2], v[0], v[2], v[0]};
    }

    template<class I>
    AVML_FINL Vector4I<I> zxzy(Vector4I<I> v) {
        return {v[2], v[0], v[2], v[1]};
    }

    template<class I>
    AVML_FINL Vector4I<I> zxzz(Vector4I<I> v) {
        return {v[2], v[0], v[2], v[2]};
    }

    template<class I>
    AVML_FINL Vector4I<I> zxzw(Vector4I<I> v) {
        return {v[2], v[0], v[2], v[3]};
    }

    template<class I>
    AVML_FINL Vector4I<I> zxwx(Vector4I<I> v) {
        return {v[2], v[0], v[3], v[0]};
    }

    template<class I>
    AVML_FINL Vector4I<I> zxwy(Vector4I<I> v) {
        return {v[2], v[0], v[3], v[1]};
    }

    template<class I>
    AVML_FINL Vector4I<I> zxwz(Vector4I<I> v) {
        return {v[2], v[0], v[3], v[2]};
    }

    template<class I>
    AVML_FINL Vector4I<I> zxww(Vector4I<I> v) {
        return {v[2], v[0], v[3], v[3]};
    }

    template<class I>
    AVML_FINL Vector4I<I> zyxx(Vector4I<I> v) {
        return {v[2], v[1], v[0], v[0]};
    }

    template<class I>
    AVML_FINL Vector4I<I> zyxy(Vector4I<I> v) {
        return {v[2], v[1], v[0], v[1]};
    }

    template<class I>
    AVML_FINL Vector4I<I> zyxz(Vector4I<I> v) {
        return {v[2], v[1], v[0], v[2]};
    }

    template<class I>
    AVML_FINL Vector4I<I> zyxw(Vector4I<I> v) {
        return {v[2], v[1], v[0], v[3]};
    }

    template<class I>
    AVML_FINL Vector4I<I> zyyx(Vector4I<I> v) {
        return {v[2], v[1], v[1], v[0]};
    }

    template<class I>
    AVML_FINL Vector4I<I> zyyy(Vector4I<I> v) {
        return {v[2], v[1], v[1], v[1]};
    }

    template<class I>
    AVML_FINL Vector4I<I> zyyz(Vector4I<I> v) {
        return {v[2], v[1], v[1], v[2]};
    }

    template<class I>
    AVML_FINL Vector4I<I> zyyw(Vector4I<I> v) {
        return {v[2], v[1], v[1], v[3]};
    }

    template<class I>
    AVML_FINL Vector4I<I> zyzx(Vector4I<I> v) {
        return {v[2], v[1], v[2], v[0]};
    }

    template<class I>
    AVML_FINL Vector4I<I> zyzy(Vector4I<I> v) {
        return {v[2], v[1], v[2], v[1]};
    }

    template<class I>
    AVML_FINL Vector4I<I> zyzz(Vector4I<I> v) {
        return {v[2], v[1], v[2], v[2]};
    }

    template<class I>
    AVML_FINL Vector4I<I> zyzw(Vector4I<I> v) {
        return {v[2], v[1], v[2], v[3]};
    }

    template<class I>
    AVML_FINL Vector4I<I> zywx(Vector4I<I> v) {
        return {v[2], v[1], v[3], v[0]};
    }

    template<class I>
    AVML_FINL Vector4I<I> zywy(Vector4I<I> v) {
        return {v[2], v[1], v[3], v[1]};
    }

    template<class I>
    AVML_FINL Vector4I<I> zywz(Vector4I<I> v) {
        return {v[2], v[1], v[3], v[2]};
    }

    template<class I>
    AVML_FINL Vector4I<I> zyww(Vector4I<I> v) {
        return {v[2], v[1], v[3], v[3]};
    }

    template<class I>
    AVML_FINL Vector4I<I> zzxx(Vector4I<I> v) {
        return {v[2], v[2], v[0], v[0]};
    }

    template<class I>
    AVML_FINL Vector4I<I> zzxy(Vector4I<I> v) {
        return {v[2], v[2], v[0], v[1]};
    }

    template<class I>
    AVML_FINL Vector4I<I> zzxz(Vector4I<I> v) {
        return {v[2], v[2], v[0], v[2]};
    }

    template<class I>
    AVML_FINL Vector4I<I> zzxw(Vector4I<I> v) {
        return {v[2], v[2], v[0], v[3]};
    }

    template<class I>
    AVML_FINL Vector4I<I> zzyx(Vector4I<I> v) {
        return {v[2], v[2], v[1], v[0]};
    }

    template<class I>
    AVML_FINL Vector4I<I> zzyy(Vector4I<I> v) {
        return {v[2], v[2], v[1], v[1]};
    }

    template<class I>
    AVML_FINL Vector4I<I> zzyz(Vector4I<I> v) {
        return {v[2], v[2], v[1], v[2]};
    }

    template<class I>
    AVML_FINL Vector4I<I> zzyw(Vector4I<I> v) {
        return {v[2], v[2], v[1], v[3]};
    }

    template<class I>
    AVML_FINL Vector4I<I> zzzx(Vector4I<I> v) {
        return {v[2], v[2], v[2], v[0]};
    }

    template<class I>
    AVML_FINL Vector4I<I> zzzy(Vector4I<I> v) {
        return {v[2], v[2], v[2], v[1]};
    }

    template<class I>
    AVML_FINL Vector4I<I> zzzz(Vector4I<I> v) {
        return {v[2], v[2], v[2], v[2]};
    }

    template<class I>
    AVML_FINL Vector4I<I> zzzw(Vector4I<I> v) {
        return {v[2], v[2], v[2], v[3]};
    }

    template<class I>
    AVML_FINL Vector4I<I> zzwx(Vector4I<I> v) {
        return {v[2], v[2], v[3], v[0]};
    }

    template<class I>
    AVML_FINL Vector4I<I> zzwy(Vector4I<I> v) {
        return {v[2], v[2], v[3], v[1]};
    }

    template<class I>
    AVML_FINL Vector4I<I> zzwz(Vector4I<I> v) {
        return {v[2], v[2], v[3], v[2]};
    }

    template<class I>
    AVML_FINL Vector4I<I> zzww(Vector4I<I> v) {
        return {v[2], v[2], v[3], v[3]};
    }

    template<class I>
    AVML_FINL Vector4I<I> zwxx(Vector4I<I> v) {
        return {v[2], v[3], v[0], v[0]};
    }

    template<class I>
    AVML_FINL Vector4I<I> zwxy(Vector4I<I> v) {
        return {v[2], v[3], v[0], v[1]};
    }

    template<class I>
    AVML_FINL Vector4I<I> zwxz(Vector4I<I> v) {
        return {v[2], v[3], v[0], v[2]};
    }

    template<class I>
    AVML_FINL Vector4I<I> zwxw(Vector4I<I> v) {
        return {v[2], v[3], v[0], v[3]};
    }

    template<class I>
    AVML_FINL Vector4I<I> zwyx(Vector4I<I> v) {
        return {v[2], v[3], v[1], v[0]};
    }

    template<class I>
    AVML_FINL Vector4I<I> zwyy(Vector4I<I> v) {
        return {v[2], v[3], v[1], v[1]};
    }

    template<class I>
    AVML_FINL Vector4I<I> zwyz(Vector4I<I> v) {
        return {v[2], v[3], v[1], v[2]};
    }

    template<class I>
    AVML_FINL Vector4I<I> zwyw(Vector4I<I> v) {
        return {v[2], v[3], v[1], v[3]};
    }

    template<class I>
    AVML_FINL Vector4I<I> zwzx(Vector4I<I> v) {
        return {v[2], v[3], v[2], v[0]};
    }

    template<class I>
    AVML_FINL Vector4I<I> zwzy(Vector4I<I> v) {
        return {v[2], v[3], v[2], v[1]};
    }

    template<class I>
    AVML_FINL Vector4I<I> zwzz(Vector4I<I> v) {
        return {v[2], v[3], v[2], v[2]};
    }

    template<class I>
    AVML_FINL Vector4I<I> zwzw(Vector4I<I> v) {
        return {v[2], v[3], v[2], v[3]};
    }

    template<class I>
    AVML_FINL Vector4I<I> zwwx(Vector4I<I> v) {
        return {v[2], v[3], v[3], v[0]};
    }

    template<class I>
    AVML_FINL Vector4I<I> zwwy(Vector4I<I> v) {
        return {v[2], v[3], v[3], v[1]};
    }

    template<class I>
    AVML_FINL Vector4I<I> zwwz(Vector4I<I> v) {
        return {v[2], v[3], v[3], v[2]};
    }

    template<class I>
    AVML_FINL Vector4I<I> zwww(Vector4I<I> v) {
        return {v[2], v[3], v[3], v[3]};
    }

    template<class I>
    AVML_FINL Vector4I<I> wxxx(Vector4I<I> v) {
        return {v[3], v[0], v[0], v[0]};
    }

    template<class I>
    AVML_FINL Vector4I<I> wxxy(Vector4I<I> v) {
        return {v[3], v[0], v[0], v[1]};
    }

    template<class I>
    AVML_FINL Vector4I<I> wxxz(Vector4I<I> v) {
        return {v[3], v[0], v[0], v[2]};
    }

    template<class I>
    AVML_FINL Vector4I<I> wxxw(Vector4I<I> v) {
        return {v[3], v[0], v[0], v[3]};
    }

    template<class I>
    AVML_FINL Vector4I<I> wxyx(Vector4I<I> v) {
        return {v[3], v[0], v[1], v[0]};
    }

    template<class I>
    AVML_FINL Vector4I<I> wxyy(Vector4I<I> v) {
        return {v[3], v[0], v[1], v[1]};
    }

    template<class I>
    AVML_FINL Vector4I<I> wxyz(Vector4I<I> v) {
        return {v[3], v[0], v[1], v[2]};
    }

    template<class I>
    AVML_FINL Vector4I<I> wxyw(Vector4I<I> v) {
        return {v[3], v[0], v[1], v[3]};
    }

    template<class I>
    AVML_FINL Vector4I<I> wxzx(Vector4I<I> v) {
        return {v[3], v[0], v[2], v[0]};
    }

    template<class I>
    AVML_FINL Vector4I<I> wxzy(Vector4I<I> v) {
        return {v[3], v[0], v[2], v[1]};
    }

    template<class I>
    AVML_FINL Vector4I<I> wxzz(Vector4I<I> v) {
        return {v[3], v[0], v[2], v[2]};
    }

    template<class I>
    AVML_FINL Vector4I<I> wxzw(Vector4I<I> v) {
        return {v[3], v[0], v[2], v[3]};
    }

    template<class I>
    AVML_FINL Vector4I<I> wxwx(Vector4I<I> v) {
        return {v[3], v[0], v[3], v[0]};
    }

    template<class I>
    AVML_FINL Vector4I<I> wxwy(Vector4I<I> v) {
        return {v[3], v[0], v[3], v[1]};
    }

    template<class I>
    AVML_FINL Vector4I<I> wxwz(Vector4I<I> v) {
        return {v[3], v[0], v[3], v[2]};
    }

    template<class I>
    AVML_FINL Vector4I<I> wxww(Vector4I<I> v) {
        return {v[3], v[0], v[3], v[3]};
    }

    template<class I>
    AVML_FINL Vector4I<I> wyxx(Vector4I<I> v) {
        return {v[3], v[1], v[0], v[0]};
    }

    template<class I>
    AVML_FINL Vector4I<I> wyxy(Vector4I<I> v) {
        return {v[3], v[1], v[0], v[1]};
    }

    template<class I>
    AVML_FINL Vector4I<I> wyxz(Vector4I<I> v) {
        return {v[3], v[1], v[0], v[2]};
    }

    template<class I>
    AVML_FINL Vector4I<I> wyxw(Vector4I<I> v) {
        return {v[3], v[1], v[0], v[3]};
    }

    template<class I>
    AVML_FINL Vector4I<I> wyyx(Vector4I<I> v) {
        return {v[3], v[1], v[1], v[0]};
    }

    template<class I>
    AVML_FINL Vector4I<I> wyyy(Vector4I<I> v) {
        return {v[3], v[1], v[1], v[1]};
    }

    template<class I>
    AVML_FINL Vector4I<I> wyyz(Vector4I<I> v) {
        return {v[3], v[1], v[1], v[2]};
    }

    template<class I>
    AVML_FINL Vector4I<I> wyyw(Vector4I<I> v) {
        return {v[3], v[1], v[1], v[3]};
    }

    template<class I>
    AVML_FINL Vector4I<I> wyzx(Vector4I<I> v) {
        return {v[3], v[1], v[2], v[0]};
    }

    template<class I>
    AVML_FINL Vector4I<I> wyzy(Vector4I<I> v) {
        return {v[3], v[1], v[2], v[1]};
    }

    template<class I>
    AVML_FINL Vector4I<I> wyzz(Vector4I<I> v) {
        return {v[3], v[1], v[2], v[2]};
    }

    template<class I>
    AVML_FINL Vector4I<I> wyzw(Vector4I<I> v) {
        return {v[3], v[1], v[2], v[3]};
    }

    template<class I>
    AVML_FINL Vector4I<I> wywx(Vector4I<I> v) {
        return {v[3], v[1], v[3], v[0]};
    }

    template<class I>
    AVML_FINL Vector4I<I> wywy(Vector4I<I> v) {
        return {v[3], v[1], v[3], v[1]};
    }

    template<class I>
    AVML_FINL Vector4I<I> wywz(Vector4I<I> v) {
        return {v[3], v[1], v[3], v[2]};
    }

    template<class I>
    AVML_FINL Vector4I<I> wyww(Vector4I<I> v) {
        return {v[3], v[1], v[3], v[3]};
    }

    template<class I>
    AVML_FINL Vector4I<I> wzxx(Vector4I<I> v) {
        return {v[3], v[2], v[0], v[0]};
    }

    template<class I>
    AVML_FINL Vector4I<I> wzxy(Vector4I<I> v) {
        return {v[3], v[2], v[0], v[1]};
    }

    template<class I>
    AVML_FINL Vector4I<I> wzxz(Vector4I<I> v) {
        return {v[3], v[2], v[0], v[2]};
    }

    template<class I>
    AVML_FINL Vector4I<I> wzxw(Vector4I<I> v) {
        return {v[3], v[2], v[0], v[3]};
    }

    template<class I>
    AVML_FINL Vector4I<I> wzyx(Vector4I<I> v) {
        return {v[3], v[2], v[1], v[0]};
    }

    template<class I>
    AVML_FINL Vector4I<I> wzyy(Vector4I<I> v) {
        return {v[3], v[2], v[1], v[1]};
    }

    template<class I>
    AVML_FINL Vector4I<I> wzyz(Vector4I<I> v) {
        return {v[3], v[2], v[1], v[2]};
    }

    template<class I>
    AVML_FINL Vector4I<I> wzyw(Vector4I<I> v) {
        return {v[3], v[2], v[1], v[3]};
    }

    template<class I>
    AVML_FINL Vector4I<I> wzzx(Vector4I<I> v) {
        return {v[3], v[2], v[2], v[0]};
    }

    template<class I>
    AVML_FINL Vector4I<I> wzzy(Vector4I<I> v) {
        return {v[3], v[2], v[2], v[1]};
    }

    template<class I>
    AVML_FINL Vector4I<I> wzzz(Vector4I<I> v) {
        return {v[3], v[2], v[2], v[2]};
    }

    template<class I>
    AVML_FINL Vector4I<I> wzzw(Vector4I<I> v) {
        return {v[3], v[2], v[2], v[3]};
    }

    template<class I>
    AVML_FINL Vector4I<I> wzwx(Vector4I<I> v) {
        return {v[3], v[2], v[3], v[0]};
    }

    template<class I>
    AVML_FINL Vector4I<I> wzwy(Vector4I<I> v) {
        return {v[3], v[2], v[3], v[1]};
    }

    template<class I>
    AVML_FINL Vector4I<I> wzwz(Vector4I<I> v) {
        return {v[3], v[2], v[3], v[2]};
    }

    template<class I>
    AVML_FINL Vector4I<I> wzww(Vector4I<I> v) {
        return {v[3], v[2], v[3], v[3]};
    }

    template<class I>
    AVML_FINL Vector4I<I> wwxx(Vector4I<I> v) {
        return {v[3], v[3], v[0], v[0]};
    }

    template<class I>
    AVML_FINL Vector4I<I> wwxy(Vector4I<I> v) {
        return {v[3], v[3], v[0], v[1]};
    }

    template<class I>
    AVML_FINL Vector4I<I> wwxz(Vector4I<I> v) {
        return {v[3], v[3], v[0], v[2]};
    }

    template<class I>
    AVML_FINL Vector4I<I> wwxw(Vector4I<I> v) {
        return {v[3], v[3], v[0], v[3]};
    }

    template<class I>
    AVML_FINL Vector4I<I> wwyx(Vector4I<I> v) {
        return {v[3], v[3], v[1], v[0]};
    }

    template<class I>
    AVML_FINL Vector4I<I> wwyy(Vector4I<I> v) {
        return {v[3], v[3], v[1], v[1]};
    }

    template<class I>
    AVML_FINL Vector4I<I> wwyz(Vector4I<I> v) {
        return {v[3], v[3], v[1], v[2]};
    }

    template<class I>
    AVML_FINL Vector4I<I> wwyw(Vector4I<I> v) {
        return {v[3], v[3], v[1], v[3]};
    }

    template<class I>
    AVML_FINL Vector4I<I> wwzx(Vector4I<I> v) {
        return {v[3], v[3], v[2], v[0]};
    }

    template<class I>
    AVML_FINL Vector4I<I> wwzy(Vector4I<I> v) {
        return {v[3], v[3], v[2], v[1]};
    }

    template<class I>
    AVML_FINL Vector4I<I> wwzz(Vector4I<I> v) {
        return {v[3], v[3], v[2], v[2]};
    }

    template<class I>
    AVML_FINL Vector4I<I> wwzw(Vector4I<I> v) {
        return {v[3], v[3], v[2], v[3]};
    }

    template<class I>
    AVML_FINL Vector4I<I> wwwx(Vector4I<I> v) {
        return {v[3], v[3], v[3], v[0]};
    }

    template<class I>
    AVML_FINL Vector4I<I> wwwy(Vector4I<I> v) {
        return {v[3], v[3], v[3], v[1]};
    }

    template<class I>
    AVML_FINL Vector4I<I> wwwz(Vector4I<I> v) {
        return {v[3], v[3], v[3], v[2]};
    }

    template<class I>
    AVML_FINL Vector4I<I> wwww(Vector4I<I> v) {
        return {v[3], v[3], v[3], v[3]};
    }

}

#endif
