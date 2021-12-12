#ifndef AVML_GEN_VEC2I_HPP
#define AVML_GEN_VEC2I_HPP

namespace avml {

    template<class I>
    class alignas(avml_impl::vector_alignment<I, 2>) Vector2I {
    public:

        using scalar = I;

        static constexpr unsigned width = 2;

        //=================================================
        // Creation functions
        //=================================================

        AVML_FINL static Vector2I read(const I* p) {
            return Vector2I{p[0], p[1]};
        }

        AVML_FINL static Vector2I read_aligned(const I* p) {
            return Vector2I{p[0], p[1]};
        }

        //=================================================
        // -ctors
        //=================================================

        explicit AVML_FINL Vector2I(I v):
            elements{v, v} {}

        AVML_FINL Vector2I(I x, I y):
            elements{x, y} {}

        template<class U>
        explicit AVML_FINL Vector2I(Vector2I<U> v):
            elements{
                static_cast<I>(v[0]),
                static_cast<I>(v[1])
            } {}

        template<class R>
        explicit AVML_FINL Vector2I(Vector2R<R> v):
            elements{
                static_cast<I>(v[0]),
                static_cast<I>(v[1])
            } {}

        Vector2I() = default;
        Vector2I(const Vector2I&) = default;
        Vector2I(Vector2I&&) noexcept = default;
        ~Vector2I() = default;

        //=================================================
        // Assignment operators
        //=================================================

        Vector2I& operator=(const Vector2I&) = default;
        Vector2I& operator=(Vector2I&&) noexcept = default;

        //=================================================
        // Unary arithmetic operators
        //=================================================

        AVML_FINL Vector2I operator+() const {
            return *this;
        }

        AVML_FINL Vector2I operator-() const {
            return Vector2I{
                -elements[0],
                -elements[1]
            };
        }

        //=================================================
        // Arithmetic assignment operators
        //=================================================

        AVML_FINL Vector2I& operator+=(const Vector2I& rhs) {
            for (unsigned i = 0; i < width; ++i) {
                elements[i] += rhs[i];
            }
            return *this;
        }

        AVML_FINL Vector2I& operator-=(const Vector2I& rhs) {
            for (unsigned i = 0; i < width; ++i) {
                elements[i] -= rhs[i];
            }
            return *this;
        }

        AVML_FINL Vector2I& operator*=(const Vector2I rhs) {
            for (unsigned i = 0; i < width; ++i) {
                elements[i] *= rhs[i];
            }
            return *this;
        }

        AVML_FINL Vector2I& operator*=(const scalar rhs) {
            for (unsigned i = 0; i < width; ++i) {
                elements[i] *= rhs;
            }
            return *this;
        }

        AVML_FINL Vector2I& operator/=(const Vector2I rhs) {
            for (unsigned i = 0; i < width; ++i) {
                elements[i] /= rhs[i];
            }
            return *this;
        }

        AVML_FINL Vector2I& operator/=(const scalar rhs) {
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

        //=================================================
        // Conversion operators
        //=================================================

        template<class U>
        explicit operator Vector2I<U>() const {
            Vector2I<U> ret;
            ret.elements[0] = static_cast<U>(elements[0]);
            ret.elements[1] = static_cast<U>(elements[1]);
            return ret;
        }

        template<class R>
        explicit operator Vector2R<R>() const {
            Vector2R<R> ret;
            ret.elements[0] = static_cast<R>(elements[0]);
            ret.elements[1] = static_cast<R>(elements[1]);
            return ret;
        }

    private:

        //=================================================
        // Instance members
        //=================================================

        I elements[width] = {0, 0};

    };

    //=====================================================
    // Comparison operators
    //=====================================================

    template<class I>
    AVML_FINL bool operator==(Vector2I<I> lhs, Vector2I<I> rhs) {
        return
            (lhs[0] == rhs[0]) &&
            (lhs[1] == rhs[1]);
    }

    template<class I>
    AVML_FINL bool operator!=(Vector2I<I> lhs, Vector2I<I> rhs) {
        return
            (lhs[0] != rhs[0]) ||
            (lhs[1] != rhs[1]);
    }

    //=====================================================
    // Arithmetic operators
    //=====================================================

    template<class I>
    AVML_FINL Vector2I<I> operator+(Vector2I<I> lhs, Vector2I<I> rhs) {
        lhs += rhs;
        return lhs;
    }

    template<class I>
    AVML_FINL Vector2I<I> operator-(Vector2I<I> lhs, Vector2I<I> rhs) {
        lhs -= rhs;
        return lhs;
    }

    template<class I>
    AVML_FINL Vector2I<I> operator*(Vector2I<I> lhs, Vector2I<I> rhs) {
        lhs *= rhs;
        return lhs;
    }

    template<class I>
    AVML_FINL Vector2I<I> operator*(Vector2I<I> lhs, I rhs) {
        lhs *= rhs;
        return lhs;
    }

    template<class I>
    AVML_FINL Vector2I<I> operator*(I lhs, Vector2I<I> rhs) {
        rhs *= lhs;
        return rhs;
    }

    template<class I>
    AVML_FINL Vector2I<I> operator/(Vector2I<I> lhs, I rhs) {
        lhs /= rhs;
        return lhs;
    }

    template<class I>
    AVML_FINL Vector2I<I> operator/(Vector2I<I> lhs, Vector2I<I> rhs) {
        lhs /= rhs;
        return lhs;
    }

    //=====================================================
    // Vector math
    //=====================================================

    template<class I>
    AVML_FINL I dot(Vector2I<I> lhs, Vector2I<I> rhs) {
        return
            lhs[0] * rhs[0] +
            lhs[1] * rhs[1];
    }

    template<class I>
    AVML_FINL I length2(Vector2I<I> v) {
        return dot(v, v);
    }

    //=====================================================
    // Vectorized math
    //=====================================================

    template<class I>
    AVML_FINL Vector2I<I> abs(Vector2I<I> v) {
        v[0] = std::abs(v[0]);
        v[1] = std::abs(v[1]);
        return v;
    }

    template<class I>
    AVML_FINL Vector2I<I> max(Vector2I<I> u, Vector2I<I> v) {
        u[0] = std::max(u[0], v[0]);
        u[1] = std::max(u[1], v[1]);
        return u;
    }

    template<class I>
    AVML_FINL Vector2I<I> min(Vector2I<I> u, Vector2I<I> v) {
        u[0] = std::min(u[0], v[0]);
        u[1] = std::min(u[1], v[1]);
        return u;
    }

    //=====================================================
    // Swizzling
    //=====================================================

    // Single component

    template<class I>
    AVML_FINL I x(Vector2I<I> v) {
        return v[0];
    }

    template<class I>
    AVML_FINL I y(Vector2I<I> v) {
        return v[1];
    }

    // Two component

    template<class I>
    AVML_FINL Vector2I<I> xy(Vector2I<I> v) {
        return v;
    }

    template<class I>
    AVML_FINL Vector2I<I> yx(Vector2I<I> v) {
        return {v[1], v[0]};
    }

}

#endif
