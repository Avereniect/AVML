#ifndef AVML_DEF_VEC2_IPP
#define AVML_DEF_VEC2_IPP

namespace avml {

    template<class R>
    class alignas(alignof(R) * 2) Vector2 {
    public:

        using scalar = R;

        static constexpr unsigned width = 2;

        //=================================================
        // Creation functions
        //=================================================

        AVML_FINL static Vector2 read(const R* p) {
            return Vector2{p[0], p[1]};
        }

        AVML_FINL static Vector2 read_aligned(const R* p) {
            return Vector2{p[0], p[1]};
        }

        //=================================================
        // -ctors
        //=================================================

        AVML_FINL Vector2(R v):
            elements{v, v} {}

        AVML_FINL Vector2(R x, R y):
            elements{x, y} {}

        AVML_FINL Vector2(Unit_vector2<R> v):
            elements{v[0], v[1]} {}

        Vector2() = default;
        Vector2(const Vector2&) = default;
        Vector2(Vector2&&) = default;
        ~Vector2() = default;

        //=================================================
        // Assignment operators
        //=================================================

        Vector2& operator=(const Vector2&) = default;
        Vector2& operator=(Vector2&&) = default;

        //=================================================
        // Unary arithmetic operators
        //=================================================

        AVML_FINL Vector2 operator+() const {
            return *this;
        }

        AVML_FINL Vector2 operator-() const {
            return Vector2{
                -elements[0],
                -elements[1]
            };
        }

        //=================================================
        // Arithmetic assignment operators
        //=================================================

        AVML_FINL Vector2& operator+=(const Vector2& rhs) {
            for (unsigned i = 0; i < width; ++i) {
                elements[i] += rhs[i];
            }
            return *this;
        }

        AVML_FINL Vector2& operator-=(const Vector2& rhs) {
            for (unsigned i = 0; i < width; ++i) {
                elements[i] -= rhs[i];
            }
            return *this;
        }

        AVML_FINL Vector2& operator*=(const Vector2 rhs) {
            for (unsigned i = 0; i < width; ++i) {
                elements[i] *= rhs[i];
            }
            return *this;
        }

        AVML_FINL Vector2& operator*=(const scalar rhs) {
            for (unsigned i = 0; i < width; ++i) {
                elements[i] *= rhs;
            }
            return *this;
        }

        AVML_FINL Vector2& operator/=(const Vector2 rhs) {
            for (unsigned i = 0; i < width; ++i) {
                elements[i] /= rhs[i];
            }
            return *this;
        }

        AVML_FINL Vector2& operator/=(const scalar rhs) {
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

        R elements[width] = {0.0f, 0.0f};

    };

    //=====================================================
    // Comparison operators
    //=====================================================

    template<class R>
    AVML_FINL bool operator==(Vector2<R> lhs, Vector2<R> rhs) {
        return
            (lhs[0] == rhs[0]) &&
            (lhs[1] == rhs[1]);
    }

    template<class R>
    AVML_FINL bool operator!=(Vector2<R> lhs, Vector2<R> rhs) {
        return
            (lhs[0] != rhs[0]) ||
            (lhs[1] != rhs[1]);
    }

    //=====================================================
    // Arithmetic operators
    //=====================================================

    template<class R>
    AVML_FINL Vector2<R> operator+(Vector2<R> lhs, Vector2<R> rhs) {
        lhs += rhs;
        return lhs;
    }

    template<class R>
    AVML_FINL Vector2<R> operator-(Vector2<R> lhs, Vector2<R> rhs) {
        lhs -= rhs;
        return lhs;
    }

    template<class R>
    AVML_FINL Vector2<R> operator*(Vector2<R> lhs, Vector2<R> rhs) {
        lhs *= rhs;
        return lhs;
    }

    template<class R>
    AVML_FINL Vector2<R> operator*(Vector2<R> lhs, R rhs) {
        lhs *= rhs;
        return lhs;
    }

    template<class R>
    AVML_FINL Vector2<R> operator*(R lhs, Vector2<R> rhs) {
        rhs *= lhs;
        return rhs;
    }

    template<class R>
    AVML_FINL Vector2<R> operator/(Vector2<R> lhs, R rhs) {
        lhs /= rhs;
        return lhs;
    }

    template<class R>
    AVML_FINL Vector2<R> operator/(Vector2<R> lhs, Vector2<R> rhs) {
        lhs /= rhs;
        return lhs;
    }

    //=====================================================
    // Vector math
    //=====================================================

    template<class R>
    AVML_FINL R dot(Vector2<R> lhs, Vector2<R> rhs) {
        return
            lhs[0] * rhs[0] +
            lhs[1] * rhs[1];
    }

    template<class R>
    AVML_FINL R length2(Unit_vector2<R>) = delete;

    template<class R>
    AVML_FINL R length2(Vector2<R> v) {
        return dot(v, v);
    }

    template<class R>
    AVML_FINL R length(Unit_vector2<R>) = delete;

    template<class R>
    AVML_FINL R length(Vector2<R> v) {
        using std::sqrt;
        return sqrt(length2(v));
    }

    template<class R>
    AVML_FINL Unit_vector2<R> normalize(Vector2<R> v) {
        v /= length(v);
        return Unit_vector2<R>::read_aligned(v.data());
    }

    template<class R>
    AVML_FINL Unit_vector2<R> assume_normalized(Vector2<R> v) {
        return Unit_vector2<R>::read_aligned(v.data());
    }

    template<class R>
    AVML_FINL Vector2<R> project(Vector2<R> a, Vector2<R> b) {
        return (dot(a, b) / dot(b, b)) * b;
    }

    template<class R>
    AVML_FINL Vector2<R> project(Vector2<R> a, Unit_vector2<R> b) {
        return dot(a, b) * b;
    }

    template<class R>
    AVML_FINL Vector2<R> rotate(Vector2<R> v, R angle) {
        using std::cos;
        using std::sin;

        R c = cos(angle);
        R s = sin(angle);

        return Vector2<R>{
            v[0] * c - v[1] * s,
            v[0] * s + v[1] * c
        };
    }

    template<class R>
    AVML_FINL Vector2<R> reflect(Vector2<R> v, Unit_vector2<R> normal) {
        return 2 * dot(v, normal) * normal - v;
    }

    template<class R>
    AVML_FINL Unit_vector2<R> reflect(Unit_vector2<R> v, Unit_vector2<R> normal) {
        return Unit_vector2<R>::read_aligned(reflect(static_cast<Vector2<R>>(v), normal).data());
    }

    //=====================================================
    // Vectorized math
    //=====================================================

    template<class R>
    AVML_FINL Vector2<R> abs(Vector2<R> v) {
        using std::abs;
        v[0] = abs(v[0]);
        v[1] = abs(v[1]);
        return v;
    }

    template<class R>
    AVML_FINL Vector2<R> max(Vector2<R> u, Vector2<R> v) {
        using std::max;
        u[0] = max(u[0], v[0]);
        u[1] = max(u[1], v[1]);
        return u;
    }

    template<class R>
    AVML_FINL Vector2<R> min(Vector2<R> u, Vector2<R> v) {
        using std::max;
        u[0] = min(u[0], v[0]);
        u[1] = min(u[1], v[1]);
        return u;
    }

    //=====================================================
    // Swizzling
    //=====================================================

    // Single component

    template<class R>
    AVML_FINL R x(Vector2<R> v) {
        return v[0];
    }

    template<class R>
    AVML_FINL R y(Vector2<R> v) {
        return v[1];
    }

    // Two component

    template<class R>
    AVML_FINL Vector2<R> xy(Vector2<R> v) {
        return v;
    }

    template<class R>
    AVML_FINL Vector2<R> yx(Vector2<R> v) {
        return {v[1], v[0]};
    }

}

#endif
