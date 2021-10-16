#ifndef AVML_DEF_VEC3_IPP
#define AVML_DEF_VEC3_IPP

namespace avml {

    template<class R>
    class alignas(alignof(R) * 1) Vector3 {
    public:

        using scalar = R;

        static constexpr unsigned width = 3;

        //=================================================
        // Creation functions
        //=================================================

        AVML_FINL static Vector3 read(const R* p) {
            return Vector3{p[0], p[1], p[2]};
        }

        AVML_FINL static Vector3 read_aligned(const R* p) {
            return Vector3{p[0], p[1], p[2]};
        }

        //=================================================
        // -ctors
        //=================================================

        AVML_FINL Vector3(R v):
            elements{v, v, v} {}

        AVML_FINL Vector3(R x, R y, R z):
            elements{x, y, z} {}

        AVML_FINL Vector3(Unit_vector3<R> v):
            elements{v[0], v[1], v[2]} {}

        AVML_FINL Vector3(Vector3<R> v, R z):
            elements{v[0], v[1], z} {}

        AVML_FINL Vector3(R w, Vector3<R> v):
            elements{w, v[0], v[1]} {}

        Vector3() = default;
        Vector3(const Vector3&) = default;
        Vector3(Vector3&&) = default;
        ~Vector3() = default;

        //=================================================
        // Assignment operators
        //=================================================

        Vector3& operator=(const Vector3&) = default;
        Vector3& operator=(Vector3&&) = default;

        //=================================================
        // Unary arithmetic operators
        //=================================================

        AVML_FINL Vector3 operator+() const {
            return *this;
        }

        AVML_FINL Vector3 operator-() const {
            return Vector3{
                -elements[0],
                -elements[1],
                -elements[2],
            };
        }

        //=================================================
        // Arithmetic assignment operators
        //=================================================

        AVML_FINL Vector3& operator+=(const Vector3& rhs) {
            for (unsigned i = 0; i < width; ++i) {
                elements[i] += rhs[i];
            }
            return *this;
        }

        AVML_FINL Vector3& operator-=(const Vector3& rhs) {
            for (unsigned i = 0; i < width; ++i) {
                elements[i] -= rhs[i];
            }
            return *this;
        }

        AVML_FINL Vector3& operator*=(const scalar rhs) {
            for (unsigned i = 0; i < width; ++i) {
                elements[i] *= rhs;
            }
            return *this;
        }

        AVML_FINL Vector3& operator*=(const Vector3 rhs) {
            for (unsigned i = 0; i < width; ++i) {
                elements[i] *= rhs[i];
            }
            return *this;
        }

        AVML_FINL Vector3& operator/=(const Vector3 rhs) {
            for (unsigned i = 0; i < width; ++i) {
                elements[i] /= rhs[i];
            }
            return *this;
        }

        AVML_FINL Vector3& operator/=(const scalar rhs) {
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
      bool operator==(Vector3<R> lhs, Vector3<R> rhs) {
        return
            (lhs[0] == rhs[0]) &&
            (lhs[1] == rhs[1]) &&
            (lhs[2] == rhs[2]);
    }

    template<class R>bool operator!=(Vector3<R> lhs, Vector3<R> rhs) {
        return
            (lhs[0] != rhs[0]) ||
            (lhs[1] != rhs[1]) ||
            (lhs[2] != rhs[2]);
    }

    //=====================================================
    // Arithmetic operators
    //=====================================================

    template<class R>Vector3<R> operator+(Vector3<R> lhs, Vector3<R> rhs) {
        lhs += rhs;
        return lhs;
    }

    template<class R>
    Vector3<R> operator-(Vector3<R> lhs, Vector3<R> rhs) {
        lhs -= rhs;
        return lhs;
    }

    template<class R>
    Vector3<R> operator*(Vector3<R> lhs, Vector3<R> rhs) {
        lhs *= rhs;
        return lhs;
    }

    template<class R>
    Vector3<R> operator*(Vector3<R> lhs, R rhs) {
        lhs *= rhs;
        return lhs;
    }

    template<class R>
    Vector3<R> operator*(R lhs, Vector3<R> rhs) {
        rhs *= lhs;
        return rhs;
    }

    template<class R>
    Vector3<R> operator/(Vector3<R> lhs, R rhs) {
        lhs /= rhs;
        return lhs;
    }

    template<class R>
    Vector3<R> operator/(Vector3<R> lhs, Vector3<R> rhs) {
        lhs /= rhs;
        return lhs;
    }

    //=====================================================
    // Vector math
    //=====================================================

    template<class R>
    R dot(Vector3<R> lhs, Vector3<R> rhs) {
        return
            lhs[0] * rhs[0] +
            lhs[1] * rhs[1] +
            lhs[2] * rhs[2];
    }

    template<class R>
    R length2(Unit_vector3<R>) = delete;

    template<class R>
    R length2(Vector3<R> v) {
        return dot(v, v);
    }

    template<class R>
    R length(Unit_vector3<R>) = delete;

    template<class R>
    R length(Vector3<R> v) {
        using std::sqrt;
        return sqrt(length2(v));
    }

    template<class R>
    Unit_vector3<R> assume_normalized(Vector3<R> v) {
        return Unit_vector3<R>::read_aligned(v.data());
    }

    template<class R>
    Unit_vector3<R> normalize(Vector3<R> v) {
        v /= length(v);
        return assume_normalized(v);
    }

    template<class R>
    Vector3<R> cross(Vector3<R> lhs, Vector3<R> rhs) {
        return Vector3<R> {
            lhs[1] * rhs[2] - lhs[2] * rhs[1],
            lhs[2] * rhs[0] - lhs[0] * rhs[2],
            lhs[0] * rhs[1] - lhs[1] * rhs[0]
        };
    }

    template<class R>
    Vector3<R> project(Vector3<R> a, Vector3<R> b) {
        return (dot(a, b) / dot(b, b)) * b;
    }

    template<class R>
    Vector3<R> project(Vector3<R> a, Unit_vector3<R> b) {
        return dot(a, b) * b;
    }

    template<class R>
    Vector3<R> project_onto_plane(Vector3<R> v, Unit_vector3<R> normal) {
        return (v - project(v, normal));
    }

    template<class R>
    Vector3<R> rotate(Vector3<R> v, R angle, Unit_vector3<R> axis) {
        using std::sin;
        using std::cos;

        R s = sin(angle);
        R c = cos(angle);

        return (v * c) + (cross(axis, v) * s) + (axis * dot(axis, v) * (1 - c));
    }

    template<class R>
    Unit_vector3<R> rotate(Unit_vector3<R> v, R angle, Unit_vector3<R> axis) {
        return Unit_vector3<R>::read_aligned(rotate(static_cast<Vector3<R>>(v), angle, axis).data());
    }

    template<class R>
    Vector3<R> rotate_x(Vector3<R> v, R angle) {
        using std::sin;
        using std::cos;

        R s = sin(angle);
        R c = cos(angle);

        v[1] = v[1] * c - v[2] * s;
        v[2] = v[1] * s + v[2] * c;

        return assume_normalized(v);
    }

    template<class R>
    Vector3<R> rotate_y(Vector3<R> v, R angle) {
        using std::sin;
        using std::cos;

        R s = sin(angle);
        R c = cos(angle);

        v[0] = v[0] * c + v[2] * s;
        v[2] = v[2] * c - v[0] * s;

        return assume_normalized(v);
    }

    template<class R>
    Vector3<R> rotate_z(Vector3<R> v, R angle) {
        using std::sin;
        using std::cos;

        R s = sin(angle);
        R c = cos(angle);

        v[0] = v[0] * c - v[1] * s;
        v[1] = v[0] * s + v[1] * c;

        return assume_normalized(v);
    }

    template<class R>
    Vector3<R> reflect(Vector3<R> v, Unit_vector3<R> normal) {
        return 2 * dot(v, normal) * normal - v;
    }

    template<class R>
    Unit_vector3<R> reflect(Unit_vector3<R> v, Unit_vector3<R> normal) {
        return Unit_vector3<R>::read_aligned(reflect(static_cast<Vector3<R>>(v), normal).data());
    }

    //=====================================================
    // Vectorized math
    //=====================================================

    template<class R>
    Vector3<R> abs(Vector3<R> v) {
        using std::abs;
        v[0] = abs(v[0]);
        v[1] = abs(v[1]);
        v[2] = abs(v[2]);
        return v;
    }

    template<class R>
    Vector3<R> max(Vector3<R> u, Vector3<R> v) {
        using std::max;
        u[0] = max(u[0], v[0]);
        u[1] = max(u[1], v[1]);
        u[2] = max(u[2], v[2]);
        return u;
    }

    template<class R>
    Vector3<R> min(Vector3<R> u, Vector3<R> v) {
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
    R x(Vector3<R> v) {
        return v[0];
    }

    template<class R>
    R y(Vector3<R> v) {
        return v[1];
    }

    template<class R>
    R z(Vector3<R> v) {
        return v[2];
    }

    // Two components

    template<class R>
    Vector3<R> xx(Vector3<R> v) {
        return {v[0], v[0]};
    }

    template<class R>
    Vector3<R> xy(Vector3<R> v) {
        return {v[0], v[1]};
    }

    template<class R>
    Vector3<R> xz(Vector3<R> v) {
        return {v[0], v[2]};
    }

    template<class R>
    Vector3<R> yx(Vector3<R> v) {
        return {v[1], v[0]};
    }

    template<class R>
    Vector3<R> yy(Vector3<R> v) {
        return {v[1], v[1]};
    }

    template<class R>
    Vector3<R> yz(Vector3<R> v) {
        return {v[1], v[2]};
    }

    template<class R>
    Vector3<R> zx(Vector3<R> v) {
        return {v[2], v[0]};
    }

    template<class R>
    Vector3<R> zy(Vector3<R> v) {
        return {v[2], v[1]};
    }

    template<class R>
    Vector3<R> zz(Vector3<R> v) {
        return {v[2], v[2]};
    }

    // Three components

    template<class R>
    Vector3<R> xxx(Vector3<R> v) {
        return {v[0], v[0], v[0]};
    }

    template<class R>
    Vector3<R> xxy(Vector3<R> v) {
        return {v[0], v[0], v[1]};
    }

    template<class R>
    Vector3<R> xxz(Vector3<R> v) {
        return {v[0], v[0], v[2]};
    }

    template<class R>
    Vector3<R> xyx(Vector3<R> v) {
        return {v[0], v[1], v[0]};
    }

    template<class R>
    Vector3<R> xyy(Vector3<R> v) {
        return {v[0], v[1], v[1]};
    }

    template<class R>
    Vector3<R> xyz(Vector3<R> v) {
        return {v[0], v[1], v[2]};
    }

    template<class R>
    Vector3<R> xzx(Vector3<R> v) {
        return {v[0], v[2], v[0]};
    }

    template<class R>
    Vector3<R> xzy(Vector3<R> v) {
        return {v[0], v[2], v[1]};
    }

    template<class R>
    Vector3<R> xzz(Vector3<R> v) {
        return {v[0], v[2], v[2]};
    }

    template<class R>
    Vector3<R> yxx(Vector3<R> v) {
        return {v[1], v[0], v[0]};
    }

    template<class R>
    Vector3<R> yxy(Vector3<R> v) {
        return {v[1], v[0], v[1]};
    }

    template<class R>
    Vector3<R> yxz(Vector3<R> v) {
        return {v[1], v[0], v[2]};
    }

    template<class R>
    Vector3<R> yyx(Vector3<R> v) {
        return {v[1], v[1], v[0]};
    }

    template<class R>
    Vector3<R> yyy(Vector3<R> v) {
        return {v[1], v[1], v[1]};
    }

    template<class R>
    Vector3<R> yyz(Vector3<R> v) {
        return {v[1], v[1], v[2]};
    }

    template<class R>
    Vector3<R> yzx(Vector3<R> v) {
        return {v[1], v[2], v[0]};
    }

    template<class R>
    Vector3<R> yzy(Vector3<R> v) {
        return {v[1], v[2], v[1]};
    }

    template<class R>
    Vector3<R> yzz(Vector3<R> v) {
        return {v[1], v[2], v[2]};
    }

    template<class R>
    Vector3<R> zxx(Vector3<R> v) {
        return {v[2], v[0], v[0]};
    }

    template<class R>
    Vector3<R> zxy(Vector3<R> v) {
        return {v[2], v[0], v[1]};
    }

    template<class R>
    Vector3<R> zxz(Vector3<R> v) {
        return {v[2], v[0], v[2]};
    }

    template<class R>
    Vector3<R> zyx(Vector3<R> v) {
        return {v[2], v[1], v[0]};
    }

    template<class R>
    Vector3<R> zyy(Vector3<R> v) {
        return {v[2], v[1], v[1]};
    }

    template<class R>
    Vector3<R> zyz(Vector3<R> v) {
        return {v[2], v[1], v[2]};
    }

    template<class R>
    Vector3<R> zzx(Vector3<R> v) {
        return {v[2], v[2], v[0]};
    }

    template<class R>
    Vector3<R> zzy(Vector3<R> v) {
        return {v[2], v[2], v[1]};
    }

    template<class R>
    Vector3<R> zzz(Vector3<R> v) {
        return {v[2], v[2], v[2]};
    }

}

#endif
