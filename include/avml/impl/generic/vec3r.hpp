#ifndef AVML_GEN_VEC3R_HPP
#define AVML_GEN_VEC3R_HPP

namespace avml {

    template<class R>
    class alignas(avml_impl::vector_alignment<R, 3>()) Vector3R {
    public:

        using scalar = R;

        static constexpr unsigned width = 3;

        //=================================================
        // Creation functions
        //=================================================

        AVML_FINL static Vector3R read(const R* p) {
            return Vector3R{p[0], p[1], p[2]};
        }

        AVML_FINL static Vector3R read_aligned(const R* p) {
            return Vector3R{p[0], p[1], p[2]};
        }

        //=================================================
        // -ctors
        //=================================================

        explicit AVML_FINL Vector3R(R v):
            elements{v, v, v} {}

        AVML_FINL Vector3R(R x, R y, R z):
            elements{x, y, z} {}

        AVML_FINL Vector3R(Unit_vector3R <R> v):
            elements{v[0], v[1], v[2]} {}

        AVML_FINL Vector3R(Vector2R <R> v, R z):
            elements{v[0], v[1], z} {}

        AVML_FINL Vector3R(R w, Vector2R <R> v):
            elements{w, v[0], v[1]} {}

        template<class U>
        explicit AVML_FINL Vector3R(Vector3R<U> v):
            elements{
                static_cast<R>(v[0]),
                static_cast<R>(v[1]),
                static_cast<R>(v[2])
            } {}

        Vector3R() = default;
        Vector3R(const Vector3R&) = default;
        Vector3R(Vector3R&&) noexcept = default;
        ~Vector3R() = default;

        //=================================================
        // Assignment operators
        //=================================================

        Vector3R& operator=(const Vector3R&) = default;
        Vector3R& operator=(Vector3R&&) noexcept = default;

        //=================================================
        // Unary arithmetic operators
        //=================================================

        AVML_FINL Vector3R operator+() const {
            return *this;
        }

        AVML_FINL Vector3R operator-() const {
            return Vector3R{
                -elements[0],
                -elements[1],
                -elements[2],
            };
        }

        //=================================================
        // Arithmetic assignment operators
        //=================================================

        AVML_FINL Vector3R& operator+=(const Vector3R& rhs) {
            for (unsigned i = 0; i < width; ++i) {
                elements[i] += rhs[i];
            }
            return *this;
        }

        AVML_FINL Vector3R& operator-=(const Vector3R& rhs) {
            for (unsigned i = 0; i < width; ++i) {
                elements[i] -= rhs[i];
            }
            return *this;
        }

        AVML_FINL Vector3R& operator*=(const scalar rhs) {
            for (unsigned i = 0; i < width; ++i) {
                elements[i] *= rhs;
            }
            return *this;
        }

        AVML_FINL Vector3R& operator*=(const Vector3R rhs) {
            for (unsigned i = 0; i < width; ++i) {
                elements[i] *= rhs[i];
            }
            return *this;
        }

        AVML_FINL Vector3R& operator/=(const Vector3R rhs) {
            for (unsigned i = 0; i < width; ++i) {
                elements[i] /= rhs[i];
            }
            return *this;
        }

        AVML_FINL Vector3R& operator/=(const scalar rhs) {
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

        R elements[width] = {0.0f, 0.0f, 0.0f};

    };

    //=====================================================
    // Comparison operators
    //=====================================================

    template<class R>
    AVML_FINL bool operator==(Vector3R<R> lhs, Vector3R<R> rhs) {
        return
            (lhs[0] == rhs[0]) &&
            (lhs[1] == rhs[1]) &&
            (lhs[2] == rhs[2]);
    }

    template<class R>
    AVML_FINL bool operator!=(Vector3R<R> lhs, Vector3R<R> rhs) {
        return
            (lhs[0] != rhs[0]) ||
            (lhs[1] != rhs[1]) ||
            (lhs[2] != rhs[2]);
    }

    //=====================================================
    // Arithmetic operators
    //=====================================================

    template<class R>
    AVML_FINL Vector3R<R> operator+(Vector3R<R> lhs, Vector3R<R> rhs) {
        lhs += rhs;
        return lhs;
    }

    template<class R>
    AVML_FINL Vector3R<R> operator-(Vector3R<R> lhs, Vector3R<R> rhs) {
        lhs -= rhs;
        return lhs;
    }

    template<class R>
    AVML_FINL Vector3R<R> operator*(Vector3R<R> lhs, Vector3R<R> rhs) {
        lhs *= rhs;
        return lhs;
    }

    template<class R>
    AVML_FINL Vector3R<R> operator*(Vector3R<R> lhs, R rhs) {
        lhs *= rhs;
        return lhs;
    }

    template<class R>
    AVML_FINL Vector3R<R> operator*(R lhs, Vector3R<R> rhs) {
        rhs *= lhs;
        return rhs;
    }

    template<class R>
    AVML_FINL Vector3R<R> operator/(Vector3R<R> lhs, R rhs) {
        lhs /= rhs;
        return lhs;
    }

    template<class R>
    AVML_FINL Vector3R<R> operator/(Vector3R<R> lhs, Vector3R<R> rhs) {
        lhs /= rhs;
        return lhs;
    }

    //=====================================================
    // Vector math
    //=====================================================

    template<class R>
    AVML_FINL R dot(Vector3R<R> lhs, Vector3R<R> rhs) {
        return
            lhs[0] * rhs[0] +
            lhs[1] * rhs[1] +
            lhs[2] * rhs[2];
    }

    template<class R>
    AVML_FINL R length2(Vector3R<R> v) {
        return dot(v, v);
    }

    template<class R>
    AVML_FINL R length(Vector3R<R> v) {
        using std::sqrt;
        return sqrt(length2(v));
    }

    template<class R>
    AVML_FINL Unit_vector3R<R> assume_normalized(Vector3R<R> v) {
        return Unit_vector3R<R>::read_aligned(v.data());
    }

    template<class R>
    AVML_FINL Unit_vector3R <R> normalize(Vector3R<R> v) {
        v /= length(v);
        return assume_normalized(v);
    }

    template<class R>
    AVML_FINL Vector3R<R> cross(Vector3R<R> lhs, Vector3R<R> rhs) {
        return Vector3R<R>{
            lhs[1] * rhs[2] - lhs[2] * rhs[1],
            lhs[2] * rhs[0] - lhs[0] * rhs[2],
            lhs[0] * rhs[1] - lhs[1] * rhs[0]
        };
    }

    template<class R>
    AVML_FINL Vector3R<R> project(Vector3R<R> a, Vector3R<R> b) {
        return (dot(a, b) / dot(b, b)) * b;
    }

    template<class R>
    AVML_FINL Vector3R<R> project(Vector3R<R> a, Unit_vector3R <R> b) {
        return dot(a, b) * b;
    }

    template<class R>
    AVML_FINL Vector3R<R> project_onto_plane(Vector3R<R> v, Unit_vector3R <R> normal) {
        return (v - project(v, normal));
    }

    template<class R>
    AVML_FINL Vector3R<R> rotate(Vector3R<R> v, R angle, Unit_vector3R <R> axis) {
        using std::sin;
        using std::cos;
        R s = sin(angle);
        R c = cos(angle);

        return (v * c) + (cross(axis, v) * s) + (axis * dot(axis, v) * (1 - c));
    }

    template<class R>
    AVML_FINL Unit_vector3R <R> rotate(Unit_vector3R <R> v, R angle, Unit_vector3R <R> axis) {
        return Unit_vector3R<R>::read_aligned(rotate(static_cast<Vector3R<R>>(v), angle, axis).data());
    }

    template<class R>
    AVML_FINL Vector3R<R> rotate_x(Vector3R<R> v, R angle) {
        using std::sin;
        using std::cos;
        R s = sin(angle);
        R c = cos(angle);

        v[1] = v[1] * c - v[2] * s;
        v[2] = v[1] * s + v[2] * c;

        return assume_normalized(v);
    }

    template<class R>
    AVML_FINL Vector3R<R> rotate_y(Vector3R<R> v, R angle) {
        using std::sin;
        using std::cos;
        R s = sin(angle);
        R c = cos(angle);

        v[0] = v[0] * c + v[2] * s;
        v[2] = v[2] * c - v[0] * s;

        return assume_normalized(v);
    }

    template<class R>
    AVML_FINL Vector3R<R> rotate_z(Vector3R<R> v, R angle) {
        using std::sin;
        using std::cos;
        R s = sin(angle);
        R c = cos(angle);

        v[0] = v[0] * c - v[1] * s;
        v[1] = v[0] * s + v[1] * c;

        return assume_normalized(v);
    }

    template<class R>
    AVML_FINL Vector3R<R> reflect(Vector3R<R> v, Unit_vector3R <R> normal) {
        return R{2} * dot(v, normal) * normal - v;
    }

    template<class R>
    AVML_FINL Unit_vector3R <R> reflect(Unit_vector3R <R> v, Unit_vector3R <R> normal) {
        return Unit_vector3R<R>::read_aligned(reflect(static_cast<Vector3R<R>>(v), normal).data());
    }

    //=====================================================
    // Vectorized math
    //=====================================================

    template<class R>
    AVML_FINL Vector3R<R> abs(Vector3R<R> v) {
        using std::abs;
        v[0] = abs(v[0]);
        v[1] = abs(v[1]);
        v[2] = abs(v[2]);
        return v;
    }

    template<class R>
    AVML_FINL Vector3R<R> max(Vector3R<R> u, Vector3R<R> v) {
        using std::max;
        u[0] = max(u[0], v[0]);
        u[1] = max(u[1], v[1]);
        u[2] = max(u[2], v[2]);
        return u;
    }

    template<class R>
    AVML_FINL Vector3R<R> min(Vector3R<R> u, Vector3R<R> v) {
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

    template<class R>
    AVML_FINL R x(Vector3R<R> v) {
        return v[0];
    }

    template<class R>
    AVML_FINL R y(Vector3R<R> v) {
        return v[1];
    }

    template<class R>
    AVML_FINL R z(Vector3R<R> v) {
        return v[2];
    }

    // Two components

    template<class R>
    AVML_FINL Vector2R <R> xx(Vector3R<R> v) {
        return {v[0], v[0]};
    }

    template<class R>
    AVML_FINL Vector2R <R> xy(Vector3R<R> v) {
        return {v[0], v[1]};
    }

    template<class R>
    AVML_FINL Vector2R <R> xz(Vector3R<R> v) {
        return {v[0], v[2]};
    }

    template<class R>
    AVML_FINL Vector2R <R> yx(Vector3R<R> v) {
        return {v[1], v[0]};
    }

    template<class R>
    AVML_FINL Vector2R <R> yy(Vector3R<R> v) {
        return {v[1], v[1]};
    }

    template<class R>
    AVML_FINL Vector2R <R> yz(Vector3R<R> v) {
        return {v[1], v[2]};
    }

    template<class R>
    AVML_FINL Vector2R <R> zx(Vector3R<R> v) {
        return {v[2], v[0]};
    }

    template<class R>
    AVML_FINL Vector2R <R> zy(Vector3R<R> v) {
        return {v[2], v[1]};
    }

    template<class R>
    AVML_FINL Vector2R <R> zz(Vector3R<R> v) {
        return {v[2], v[2]};
    }

    // Three components

    template<class R>
    AVML_FINL Vector3R<R> xxx(Vector3R<R> v) {
        return {v[0], v[0], v[0]};
    }

    template<class R>
    AVML_FINL Vector3R<R> xxy(Vector3R<R> v) {
        return {v[0], v[0], v[1]};
    }

    template<class R>
    AVML_FINL Vector3R<R> xxz(Vector3R<R> v) {
        return {v[0], v[0], v[2]};
    }

    template<class R>
    AVML_FINL Vector3R<R> xyx(Vector3R<R> v) {
        return {v[0], v[1], v[0]};
    }

    template<class R>
    AVML_FINL Vector3R<R> xyy(Vector3R<R> v) {
        return {v[0], v[1], v[1]};
    }

    template<class R>
    AVML_FINL Vector3R<R> xyz(Vector3R<R> v) {
        return {v[0], v[1], v[2]};
    }

    template<class R>
    AVML_FINL Vector3R<R> xzx(Vector3R<R> v) {
        return {v[0], v[2], v[0]};
    }

    template<class R>
    AVML_FINL Vector3R<R> xzy(Vector3R<R> v) {
        return {v[0], v[2], v[1]};
    }

    template<class R>
    AVML_FINL Vector3R<R> xzz(Vector3R<R> v) {
        return {v[0], v[2], v[2]};
    }

    template<class R>
    AVML_FINL Vector3R<R> yxx(Vector3R<R> v) {
        return {v[1], v[0], v[0]};
    }

    template<class R>
    AVML_FINL Vector3R<R> yxy(Vector3R<R> v) {
        return {v[1], v[0], v[1]};
    }

    template<class R>
    AVML_FINL Vector3R<R> yxz(Vector3R<R> v) {
        return {v[1], v[0], v[2]};
    }

    template<class R>
    AVML_FINL Vector3R<R> yyx(Vector3R<R> v) {
        return {v[1], v[1], v[0]};
    }

    template<class R>
    AVML_FINL Vector3R<R> yyy(Vector3R<R> v) {
        return {v[1], v[1], v[1]};
    }

    template<class R>
    AVML_FINL Vector3R<R> yyz(Vector3R<R> v) {
        return {v[1], v[1], v[2]};
    }

    template<class R>
    AVML_FINL Vector3R<R> yzx(Vector3R<R> v) {
        return {v[1], v[2], v[0]};
    }

    template<class R>
    AVML_FINL Vector3R<R> yzy(Vector3R<R> v) {
        return {v[1], v[2], v[1]};
    }

    template<class R>
    AVML_FINL Vector3R<R> yzz(Vector3R<R> v) {
        return {v[1], v[2], v[2]};
    }

    template<class R>
    AVML_FINL Vector3R<R> zxx(Vector3R<R> v) {
        return {v[2], v[0], v[0]};
    }

    template<class R>
    AVML_FINL Vector3R<R> zxy(Vector3R<R> v) {
        return {v[2], v[0], v[1]};
    }

    template<class R>
    AVML_FINL Vector3R<R> zxz(Vector3R<R> v) {
        return {v[2], v[0], v[2]};
    }

    template<class R>
    AVML_FINL Vector3R<R> zyx(Vector3R<R> v) {
        return {v[2], v[1], v[0]};
    }

    template<class R>
    AVML_FINL Vector3R<R> zyy(Vector3R<R> v) {
        return {v[2], v[1], v[1]};
    }

    template<class R>
    AVML_FINL Vector3R<R> zyz(Vector3R<R> v) {
        return {v[2], v[1], v[2]};
    }

    template<class R>
    AVML_FINL Vector3R<R> zzx(Vector3R<R> v) {
        return {v[2], v[2], v[0]};
    }

    template<class R>
    AVML_FINL Vector3R<R> zzy(Vector3R<R> v) {
        return {v[2], v[2], v[1]};
    }

    template<class R>
    AVML_FINL Vector3R<R> zzz(Vector3R<R> v) {
        return {v[2], v[2], v[2]};
    }

}

#endif
