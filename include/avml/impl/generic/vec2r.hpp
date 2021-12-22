#ifndef AVML_GEN_VEC2R_HPP
#define AVML_GEN_VEC2R_HPP

namespace avml {

    template<class R>
    class alignas(avml_impl::vector_alignment<R, 2>()) Vector2R {
    public:

        using scalar = R;

        static constexpr unsigned width = 2;

        //=================================================
        // Creation functions
        //=================================================

        AVML_FINL static Vector2R read(const R* p) {
            return Vector2R{p[0], p[1]};
        }

        AVML_FINL static Vector2R read_aligned(const R* p) {
            return Vector2R{p[0], p[1]};
        }

        //=================================================
        // -ctors
        //=================================================

        explicit AVML_FINL Vector2R(R v):
            elements{v, v} {}

        AVML_FINL Vector2R(R x, R y):
            elements{x, y} {}

        AVML_FINL Vector2R(Unit_vector2R<R> v):
            elements{v[0], v[1]} {}

        template<class U>
        explicit AVML_FINL Vector2R(Vector2R<U> v):
            elements{
                static_cast<R>(v[0]),
                static_cast<R>(v[1]),
            } {}

        Vector2R() = default;
        Vector2R(const Vector2R&) = default;
        Vector2R(Vector2R&&) noexcept = default;
        ~Vector2R() = default;

        //=================================================
        // Assignment operators
        //=================================================

        Vector2R& operator=(const Vector2R&) = default;
        Vector2R& operator=(Vector2R&&) noexcept = default;

        //=================================================
        // Unary arithmetic operators
        //=================================================

        AVML_FINL Vector2R operator+() const {
            return *this;
        }

        AVML_FINL Vector2R operator-() const {
            return Vector2R{
                -elements[0],
                -elements[1]
            };
        }

        //=================================================
        // Arithmetic assignment operators
        //=================================================

        AVML_FINL Vector2R& operator+=(const Vector2R& rhs) {
            for (unsigned i = 0; i < width; ++i) {
                elements[i] += rhs[i];
            }
            return *this;
        }

        AVML_FINL Vector2R& operator-=(const Vector2R& rhs) {
            for (unsigned i = 0; i < width; ++i) {
                elements[i] -= rhs[i];
            }
            return *this;
        }

        AVML_FINL Vector2R& operator*=(const Vector2R rhs) {
            for (unsigned i = 0; i < width; ++i) {
                elements[i] *= rhs[i];
            }
            return *this;
        }

        AVML_FINL Vector2R& operator*=(const scalar rhs) {
            for (unsigned i = 0; i < width; ++i) {
                elements[i] *= rhs;
            }
            return *this;
        }

        AVML_FINL Vector2R& operator/=(const Vector2R rhs) {
            for (unsigned i = 0; i < width; ++i) {
                elements[i] /= rhs[i];
            }
            return *this;
        }

        AVML_FINL Vector2R& operator/=(const scalar rhs) {
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
    AVML_FINL bool operator==(Vector2R<R> lhs, Vector2R<R> rhs) {
        return
            (lhs[0] == rhs[0]) &&
            (lhs[1] == rhs[1]);
    }

    template<class R>
    AVML_FINL bool operator!=(Vector2R<R> lhs, Vector2R<R> rhs) {
        return
            (lhs[0] != rhs[0]) ||
            (lhs[1] != rhs[1]);
    }

    //=====================================================
    // Arithmetic operators
    //=====================================================

    template<class R>
    AVML_FINL Vector2R<R> operator+(Vector2R<R> lhs, Vector2R<R> rhs) {
        lhs += rhs;
        return lhs;
    }

    template<class R>
    AVML_FINL Vector2R<R> operator-(Vector2R<R> lhs, Vector2R<R> rhs) {
        lhs -= rhs;
        return lhs;
    }

    template<class R>
    AVML_FINL Vector2R<R> operator*(Vector2R<R> lhs, Vector2R<R> rhs) {
        lhs *= rhs;
        return lhs;
    }

    template<class R>
    AVML_FINL Vector2R<R> operator*(Vector2R<R> lhs, R rhs) {
        lhs *= rhs;
        return lhs;
    }

    template<class R>
    AVML_FINL Vector2R<R> operator*(R lhs, Vector2R<R> rhs) {
        rhs *= lhs;
        return rhs;
    }

    template<class R>
    AVML_FINL Vector2R<R> operator/(Vector2R<R> lhs, R rhs) {
        lhs /= rhs;
        return lhs;
    }

    template<class R>
    AVML_FINL Vector2R<R> operator/(Vector2R<R> lhs, Vector2R<R> rhs) {
        lhs /= rhs;
        return lhs;
    }

    //=====================================================
    // Vector math
    //=====================================================

    template<class R>
    AVML_FINL R dot(Vector2R<R> lhs, Vector2R<R> rhs) {
        return
            lhs[0] * rhs[0] +
            lhs[1] * rhs[1];
    }

    template<class R>
    AVML_FINL R length2(Vector2R<R> v) {
        return dot(v, v);
    }

    template<class R>
    AVML_FINL R length(Vector2R<R> v) {
        return std::sqrt(length2(v));
    }

    template<class R>
    AVML_FINL Unit_vector2R<R> normalize(Vector2R<R> v) {
        v /= length(v);
        return Unit_vector2R<R>::read_aligned(v.data());
    }

    template<class R>
    AVML_FINL Unit_vector2R<R> assume_normalized(Vector2R<R> v) {
        return Unit_vector2R<R>::read_aligned(v.data());
    }

    template<class R>
    AVML_FINL Vector2R<R> project(Vector2R<R> a, Vector2R<R> b) {
        return (dot(a, b) / dot(b, b)) * b;
    }

    template<class R>
    AVML_FINL Vector2R<R> project(Vector2R<R> a, Unit_vector2R<R> b) {
        return dot(a, b) * b;
    }

    template<class R>
    AVML_FINL Vector2R<R> rotate(Vector2R<R> v, R angle) {
        using std::cos;
        using std::sin;

        R c = cos(angle);
        R s = sin(angle);

        return Vector2R<R>{
            v[0] * c - v[1] * s,
            v[0] * s + v[1] * c
        };
    }

    template<class R>
    AVML_FINL Vector2R<R> reflect(Vector2R<R> v, Unit_vector2R<R> normal) {
        return R{2} * dot(v, normal) * normal - v;
    }

    template<class R>
    AVML_FINL Unit_vector2R<R> reflect(Unit_vector2R<R> v, Unit_vector2R<R> normal) {
        return Unit_vector2R<R>::read_aligned(reflect(static_cast<Vector2R<R>>(v), normal).data());
    }

    //=====================================================
    // Vectorized math
    //=====================================================

    template<class R>
    AVML_FINL Vector2R<R> abs(Vector2R<R> v) {
        using std::min;
        v[0] = abs(v[0]);
        v[1] = abs(v[1]);
        return v;
    }

    template<class R>
    AVML_FINL Vector2R<R> max(Vector2R<R> u, Vector2R<R> v) {
        using std::max;
        u[0] = max(u[0], v[0]);
        u[1] = max(u[1], v[1]);
        return u;
    }

    template<class R>
    AVML_FINL Vector2R<R> min(Vector2R<R> u, Vector2R<R> v) {
        using std::min;
        u[0] = min(u[0], v[0]);
        u[1] = min(u[1], v[1]);
        return u;
    }

    //=====================================================
    // Swizzling
    //=====================================================

    // Single component

    template<class R>
    AVML_FINL R x(Vector2R<R> v) {
        return v[0];
    }

    template<class R>
    AVML_FINL R y(Vector2R<R> v) {
        return v[1];
    }

    // Two component

    template<class R>
    AVML_FINL Vector2R<R> xy(Vector2R<R> v) {
        return v;
    }

    template<class R>
    AVML_FINL Vector2R<R> yx(Vector2R<R> v) {
        return {v[1], v[0]};
    }

}

#endif
