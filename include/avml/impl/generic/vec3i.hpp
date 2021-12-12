#ifndef AVML_GEN_VEC3I_HPP
#define AVML_GEN_VEC3I_HPP

namespace avml {

    template<class I>
    class alignas(avml_impl::vector_alignment<I, 3>()) Vector3I {
    public:

        using scalar = I;

        static constexpr unsigned width = 3;

        //=================================================
        // Creation functions
        //=================================================

        AVML_FINL static Vector3I read(const I* p) {
            return Vector3I{p[0], p[1], p[2]};
        }

        AVML_FINL static Vector3I read_aligned(const I* p) {
            return Vector3I{p[0], p[1], p[2]};
        }

        //=================================================
        // -ctors
        //=================================================

        explicit AVML_FINL Vector3I(I v):
            elements{v, v, v} {}

        AVML_FINL Vector3I(I x, I y, I z):
            elements{x, y, z} {}

        AVML_FINL Vector3I(Vector2I <I> v, I z):
            elements{v[0], v[1], z} {}

        AVML_FINL Vector3I(I w, Vector2I <I> v):
            elements{w, v[0], v[1]} {}

        template<class U>
        explicit AVML_FINL Vector3I(Vector3I<U> v):
            elements{
                static_cast<I>(v[0]),
                static_cast<I>(v[1]),
                static_cast<I>(v[2])
            } {}

        template<class R>
        explicit AVML_FINL Vector3I(Vector3R<R> v):
            elements{
                static_cast<I>(v[0]),
                static_cast<I>(v[1]),
                static_cast<I>(v[2])
            } {}

        Vector3I() = default;
        Vector3I(const Vector3I&) = default;
        Vector3I(Vector3I&&) noexcept = default;
        ~Vector3I() = default;

        //=================================================
        // Assignment operators
        //=================================================

        Vector3I& operator=(const Vector3I&) = default;
        Vector3I& operator=(Vector3I&&) noexcept = default;

        //=================================================
        // Unary arithmetic operators
        //=================================================

        AVML_FINL Vector3I operator+() const {
            return *this;
        }

        AVML_FINL Vector3I operator-() const {
            return Vector3I{
                -elements[0],
                -elements[1],
                -elements[2],
            };
        }

        //=================================================
        // Arithmetic assignment operators
        //=================================================

        AVML_FINL Vector3I& operator+=(const Vector3I& rhs) {
            for (unsigned i = 0; i < width; ++i) {
                elements[i] += rhs[i];
            }
            return *this;
        }

        AVML_FINL Vector3I& operator-=(const Vector3I& rhs) {
            for (unsigned i = 0; i < width; ++i) {
                elements[i] -= rhs[i];
            }
            return *this;
        }

        AVML_FINL Vector3I& operator*=(const scalar rhs) {
            for (unsigned i = 0; i < width; ++i) {
                elements[i] *= rhs;
            }
            return *this;
        }

        AVML_FINL Vector3I& operator*=(const Vector3I rhs) {
            for (unsigned i = 0; i < width; ++i) {
                elements[i] *= rhs[i];
            }
            return *this;
        }

        AVML_FINL Vector3I& operator/=(const Vector3I rhs) {
            for (unsigned i = 0; i < width; ++i) {
                elements[i] /= rhs[i];
            }
            return *this;
        }

        AVML_FINL Vector3I& operator/=(const scalar rhs) {
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

        I elements[width] = {0, 0, 0};

    };

    //=====================================================
    // Comparison operators
    //=====================================================

    template<class I>
    AVML_FINL bool operator==(Vector3I<I> lhs, Vector3I<I> rhs) {
        return
            (lhs[0] == rhs[0]) &&
            (lhs[1] == rhs[1]) &&
            (lhs[2] == rhs[2]);
    }

    template<class I>
    AVML_FINL bool operator!=(Vector3I<I> lhs, Vector3I<I> rhs) {
        return
            (lhs[0] != rhs[0]) ||
            (lhs[1] != rhs[1]) ||
            (lhs[2] != rhs[2]);
    }

    //=====================================================
    // Arithmetic operators
    //=====================================================

    template<class I>
    AVML_FINL Vector3I<I> operator+(Vector3I<I> lhs, Vector3I<I> rhs) {
        lhs += rhs;
        return lhs;
    }

    template<class I>
    AVML_FINL Vector3I<I> operator-(Vector3I<I> lhs, Vector3I<I> rhs) {
        lhs -= rhs;
        return lhs;
    }

    template<class I>
    AVML_FINL Vector3I<I> operator*(Vector3I<I> lhs, Vector3I<I> rhs) {
        lhs *= rhs;
        return lhs;
    }

    template<class I>
    AVML_FINL Vector3I<I> operator*(Vector3I<I> lhs, I rhs) {
        lhs *= rhs;
        return lhs;
    }

    template<class I>
    AVML_FINL Vector3I<I> operator*(I lhs, Vector3I<I> rhs) {
        rhs *= lhs;
        return rhs;
    }

    template<class I>
    AVML_FINL Vector3I<I> operator/(Vector3I<I> lhs, I rhs) {
        lhs /= rhs;
        return lhs;
    }

    template<class I>
    AVML_FINL Vector3I<I> operator/(Vector3I<I> lhs, Vector3I<I> rhs) {
        lhs /= rhs;
        return lhs;
    }

    //=====================================================
    // Vector math
    //=====================================================

    template<class I>
    AVML_FINL I dot(Vector3I<I> lhs, Vector3I<I> rhs) {
        return
            lhs[0] * rhs[0] +
            lhs[1] * rhs[1] +
            lhs[2] * rhs[2];
    }

    template<class I>
    AVML_FINL I length2(Vector3I<I> v) {
        return dot(v, v);
    }

    template<class I>
    AVML_FINL Vector3I<I> cross(Vector3I<I> lhs, Vector3I<I> rhs) {
        return Vector3I<I>{
            lhs[1] * rhs[2] - lhs[2] * rhs[1],
            lhs[2] * rhs[0] - lhs[0] * rhs[2],
            lhs[0] * rhs[1] - lhs[1] * rhs[0]
        };
    }

    //=====================================================
    // Vectorized math
    //=====================================================

    template<class I>
    AVML_FINL Vector3I<I> abs(Vector3I<I> v) {
        using std::abs;
        v[0] = abs(v[0]);
        v[1] = abs(v[1]);
        v[2] = abs(v[2]);
        return v;
    }

    template<class I>
    AVML_FINL Vector3I<I> max(Vector3I<I> u, Vector3I<I> v) {
        using std::max;
        u[0] = max(u[0], v[0]);
        u[1] = max(u[1], v[1]);
        u[2] = max(u[2], v[2]);
        return u;
    }

    template<class I>
    AVML_FINL Vector3I<I> min(Vector3I<I> u, Vector3I<I> v) {
        using std::min;
        u[0] = min(u[0], v[0]);
        u[1] = min(u[1], v[1]);
        u[2] = min(u[2], v[2]);
        return u;
    }

    //=====================================================
    // Swizzling
    //=====================================================

    // Single component

    template<class I>
    AVML_FINL I x(Vector3I<I> v) {
        return v[0];
    }

    template<class I>
    AVML_FINL I y(Vector3I<I> v) {
        return v[1];
    }

    template<class I>
    AVML_FINL I z(Vector3I<I> v) {
        return v[2];
    }

    // Two components

    template<class I>
    AVML_FINL Vector2I <I> xx(Vector3I<I> v) {
        return {v[0], v[0]};
    }

    template<class I>
    AVML_FINL Vector2I <I> xy(Vector3I<I> v) {
        return {v[0], v[1]};
    }

    template<class I>
    AVML_FINL Vector2I <I> xz(Vector3I<I> v) {
        return {v[0], v[2]};
    }

    template<class I>
    AVML_FINL Vector2I <I> yx(Vector3I<I> v) {
        return {v[1], v[0]};
    }

    template<class I>
    AVML_FINL Vector2I <I> yy(Vector3I<I> v) {
        return {v[1], v[1]};
    }

    template<class I>
    AVML_FINL Vector2I <I> yz(Vector3I<I> v) {
        return {v[1], v[2]};
    }

    template<class I>
    AVML_FINL Vector2I <I> zx(Vector3I<I> v) {
        return {v[2], v[0]};
    }

    template<class I>
    AVML_FINL Vector2I <I> zy(Vector3I<I> v) {
        return {v[2], v[1]};
    }

    template<class I>
    AVML_FINL Vector2I <I> zz(Vector3I<I> v) {
        return {v[2], v[2]};
    }

    // Three components

    template<class I>
    AVML_FINL Vector3I<I> xxx(Vector3I<I> v) {
        return {v[0], v[0], v[0]};
    }

    template<class I>
    AVML_FINL Vector3I<I> xxy(Vector3I<I> v) {
        return {v[0], v[0], v[1]};
    }

    template<class I>
    AVML_FINL Vector3I<I> xxz(Vector3I<I> v) {
        return {v[0], v[0], v[2]};
    }

    template<class I>
    AVML_FINL Vector3I<I> xyx(Vector3I<I> v) {
        return {v[0], v[1], v[0]};
    }

    template<class I>
    AVML_FINL Vector3I<I> xyy(Vector3I<I> v) {
        return {v[0], v[1], v[1]};
    }

    template<class I>
    AVML_FINL Vector3I<I> xyz(Vector3I<I> v) {
        return {v[0], v[1], v[2]};
    }

    template<class I>
    AVML_FINL Vector3I<I> xzx(Vector3I<I> v) {
        return {v[0], v[2], v[0]};
    }

    template<class I>
    AVML_FINL Vector3I<I> xzy(Vector3I<I> v) {
        return {v[0], v[2], v[1]};
    }

    template<class I>
    AVML_FINL Vector3I<I> xzz(Vector3I<I> v) {
        return {v[0], v[2], v[2]};
    }

    template<class I>
    AVML_FINL Vector3I<I> yxx(Vector3I<I> v) {
        return {v[1], v[0], v[0]};
    }

    template<class I>
    AVML_FINL Vector3I<I> yxy(Vector3I<I> v) {
        return {v[1], v[0], v[1]};
    }

    template<class I>
    AVML_FINL Vector3I<I> yxz(Vector3I<I> v) {
        return {v[1], v[0], v[2]};
    }

    template<class I>
    AVML_FINL Vector3I<I> yyx(Vector3I<I> v) {
        return {v[1], v[1], v[0]};
    }

    template<class I>
    AVML_FINL Vector3I<I> yyy(Vector3I<I> v) {
        return {v[1], v[1], v[1]};
    }

    template<class I>
    AVML_FINL Vector3I<I> yyz(Vector3I<I> v) {
        return {v[1], v[1], v[2]};
    }

    template<class I>
    AVML_FINL Vector3I<I> yzx(Vector3I<I> v) {
        return {v[1], v[2], v[0]};
    }

    template<class I>
    AVML_FINL Vector3I<I> yzy(Vector3I<I> v) {
        return {v[1], v[2], v[1]};
    }

    template<class I>
    AVML_FINL Vector3I<I> yzz(Vector3I<I> v) {
        return {v[1], v[2], v[2]};
    }

    template<class I>
    AVML_FINL Vector3I<I> zxx(Vector3I<I> v) {
        return {v[2], v[0], v[0]};
    }

    template<class I>
    AVML_FINL Vector3I<I> zxy(Vector3I<I> v) {
        return {v[2], v[0], v[1]};
    }

    template<class I>
    AVML_FINL Vector3I<I> zxz(Vector3I<I> v) {
        return {v[2], v[0], v[2]};
    }

    template<class I>
    AVML_FINL Vector3I<I> zyx(Vector3I<I> v) {
        return {v[2], v[1], v[0]};
    }

    template<class I>
    AVML_FINL Vector3I<I> zyy(Vector3I<I> v) {
        return {v[2], v[1], v[1]};
    }

    template<class I>
    AVML_FINL Vector3I<I> zyz(Vector3I<I> v) {
        return {v[2], v[1], v[2]};
    }

    template<class I>
    AVML_FINL Vector3I<I> zzx(Vector3I<I> v) {
        return {v[2], v[2], v[0]};
    }

    template<class I>
    AVML_FINL Vector3I<I> zzy(Vector3I<I> v) {
        return {v[2], v[2], v[1]};
    }

    template<class I>
    AVML_FINL Vector3I<I> zzz(Vector3I<I> v) {
        return {v[2], v[2], v[2]};
    }

}

#endif
