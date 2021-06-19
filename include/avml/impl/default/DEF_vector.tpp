#ifndef AVML_DEF_Unit_vector2f_HPP
#define AVML_DEF_Unit_vector2f_HPP

#include <cmath>

namespace avml {

    //=========================================================================
    // Unit vector template specializations
    //=========================================================================

    template<>
    class alignas(sizeof(float) * 2) Unit_vector<float, 2> {
    public:

        using scalar = float;

        static constexpr unsigned width = 2;

        //=================================================
        // Creation functions
        //=================================================

        static Unit_vector read(float* p) {
            return Unit_vector{p[0], p[1]};
        }

        static Unit_vector read_aligned(float* p) {
            return Unit_vector{p[0], p[1]};
        }

        //=================================================
        // -ctors
        //=================================================

        Unit_vector(float x, float y):
            elements() {
            float length = std::sqrt(x * x + y * y);

            elements[0] = x / length;
            elements[1] = y / length;
        }

        Unit_vector() = default;
        Unit_vector(const Unit_vector&) = default;
        Unit_vector(Unit_vector&&) = default;
        ~Unit_vector() = default;
        
        //=================================================
        // Assignment operators
        //=================================================

        Unit_vector& operator=(const Unit_vector&) = default;
        Unit_vector& operator=(Unit_vector&&) = default;

        //=================================================
        // Arithmetic operators
        //=================================================

        AVML_FINL Unit_vector operator-() const {
            Unit_vector ret;
            ret.elements[0] = -elements[0];
            ret.elements[1] = -elements[1];
            return ret;
        }

        //=================================================
        // Accessors
        //=================================================

        const float& operator[](unsigned i) const {
            return elements[i];
        }

        const float* data() const {
            return elements;
        }

    private:

        //=================================================
        // Instance members
        //=================================================

        float elements[2] = {1.0f, 0.0f};

    };





    template<>
    class alignas(sizeof(float) * 1) Unit_vector<float, 3> {
    public:

        using scalar = float;

        static constexpr unsigned width = 3;

        //=================================================
        // Creation functions
        //=================================================

        static Unit_vector read(float* p) {
            return Unit_vector{p[0], p[1], p[2]};
        }

        static Unit_vector read_aligned(float* p) {
            return Unit_vector{p[0], p[1], p[2]};
        }

        //=================================================
        // -ctors
        //=================================================

        Unit_vector(float x, float y, float z):
            elements() {
            float length = std::sqrt(x * x + y * y + z * z);

            elements[0] = x / length;
            elements[1] = y / length;
            elements[2] = z / length;
        }

        Unit_vector(Uvec2 v):
            elements{v[0], v[1], 0.0f} {}

        Unit_vector() = default;
        Unit_vector(const Unit_vector&) = default;
        Unit_vector(Unit_vector&&) = default;
        ~Unit_vector() = default;

        //=================================================
        // Assignment operators
        //=================================================

        Unit_vector& operator=(const Unit_vector&) = default;
        Unit_vector& operator=(Unit_vector&&) = default;

        //=================================================
        // Arithmetic operators
        //=================================================

        AVML_FINL Unit_vector operator-() const {
            Unit_vector ret;
            ret.elements[0] = -elements[0];
            ret.elements[1] = -elements[1];
            ret.elements[2] = -elements[2];
            return ret;
        }

        //=================================================
        // Accessors
        //=================================================

        const float& operator[](unsigned i) const {
            return elements[i];
        }

        const float* data() const {
            return elements;
        }

    private:

        //=================================================
        // Instance members
        //=================================================

        float elements[3] = {1.0f, 0.0f, 0.0f};

    };





    template<>
    class alignas(sizeof(float) * 4) Unit_vector<float, 4> {
    public:

        using scalar = float;

        static constexpr unsigned width = 4;

        //=================================================
        // Creation functions
        //=================================================

        static Unit_vector read(float* p) {
            return Unit_vector{p[0], p[1], p[2], p[3]};
        }

        static Unit_vector read_aligned(float* p) {
            return Unit_vector{p[0], p[1], p[2], p[3]};
        }

        //=================================================
        // -ctors
        //=================================================

        Unit_vector(float x, float y, float z, float w):
            elements() {
            float length = std::sqrt(x * x + y * y + z * z + w * w);

            elements[0] = x / length;
            elements[1] = y / length;
            elements[2] = z / length;
            elements[3] = w / length;
        }

        Unit_vector(Uvec3 v):
            elements{v[0], v[1], v[2], 0.0f} {}

        Unit_vector() = default;
        Unit_vector(const Unit_vector&) = default;
        Unit_vector(Unit_vector&&) = default;
        ~Unit_vector() = default;

        //=================================================
        // Assignment operators
        //=================================================

        Unit_vector& operator=(const Unit_vector&) = default;
        Unit_vector& operator=(Unit_vector&&) = default;

        //=================================================
        // Arithmetic operators
        //=================================================

        AVML_FINL Unit_vector operator-() const {
            Unit_vector ret;
            ret.elements[0] = -elements[0];
            ret.elements[1] = -elements[1];
            ret.elements[2] = -elements[2];
            ret.elements[3] = -elements[3];
            return ret;
        }

        //=================================================
        // Accessors
        //=================================================

        const float& operator[](unsigned i) const {
            return elements[i];
        }

        const float* data() const {
            return elements;
        }

    private:

        //=================================================
        // Instance members
        //=================================================

        float elements[4] = {1.0f, 0.0f, 0.0f, 0.0f};

    };

    //=========================================================================
    // Vector template specializations
    //=========================================================================

    template<>
    class Vector<float, 2> {
    public:

        using scalar = float;

        static constexpr unsigned width = 2;

        //=================================================
        // Creation functions
        //=================================================

        static Vector read(float* p) {
            return Vector{p[0], p[1]};
        }

        static Vector read_aligned(float* p) {
            return Vector{p[0], p[1]};
        }

        //=================================================
        // -ctors
        //=================================================

        Vector(float x, float y):
            elements{x, y} {}

        Vector(Uvec2 v):
            elements{v[0], v[1]} {}

        Vector() = default;
        Vector(const Vector&) = default;
        Vector(Vector&&) = default;
        ~Vector() = default;

        //=================================================
        // Assignment operators
        //=================================================

        Vector& operator=(const Vector&) = default;
        Vector& operator=(Vector&&) = default;

        //=================================================
        // Arithmetic assignment operators
        //=================================================

        Vector& operator+=(const Vector& rhs) {
            for (int i = 0; i < width; ++i) {
                elements[i] += rhs[i];
            }
            return *this;
        }

        Vector& operator-=(const Vector& rhs) {
            for (int i = 0; i < width; ++i) {
                elements[i] -= rhs[i];
            }
            return *this;
        }

        //=================================================
        // Accessors
        //=================================================

        float& operator[](unsigned i) {
            return elements[i];
        }

        const float& operator[](unsigned i) const {
            return elements[i];
        }

        float* data() {
            return elements;
        }

        const float* data() const {
            return elements;
        }

        float length2() const {
            return
                elements[0] * elements[0] +
                elements[1] * elements[1];
        }

        float length() const {
            return std::sqrt(length2());
        }

    private:

        //=================================================
        // Instance members
        //=================================================

        float elements[2] = {0.0f, 0.0f};

    };




    template<>
    class Vector<float, 3> {
    public:

        using scalar = float;

        static constexpr unsigned width = 3;

        //=================================================
        // Creation functions
        //=================================================

        static Vector read(float* p) {
            return Vector{p[0], p[1], p[2]};
        }

        static Vector read_aligned(float* p) {
            return Vector{p[0], p[1], p[2]};
        }

        //=================================================
        // -ctors
        //=================================================

        Vector(float x, float y, float z):
            elements{x, y, z} {}

        Vector(Uvec3 v):
            elements{v[0], v[1], v[2]} {}

        Vector(Vec2 v, float z):
            elements{v[0], v[1], z} {}

        Vector(float w, Vec2 v):
            elements{w, v[0], v[1]} {}

        Vector() = default;
        Vector(const Vector&) = default;
        Vector(Vector&&) = default;
        ~Vector() = default;

        //=================================================
        // Assignment operators
        //=================================================

        Vector& operator=(const Vector&) = default;
        Vector& operator=(Vector&&) = default;

        //=================================================
        // Arithmetic assignment operators
        //=================================================

        Vector& operator+=(const Vector& rhs) {
            for (int i = 0; i < width; ++i) {
                elements[i] += rhs[i];
            }
            return *this;
        }

        Vector& operator-=(const Vector& rhs) {
            for (int i = 0; i < width; ++i) {
                elements[i] -= rhs[i];
            }
            return *this;
        }

        //=================================================
        // Accessors
        //=================================================

        float& operator[](unsigned i) {
            return elements[i];
        }

        const float& operator[](unsigned i) const {
            return elements[i];
        }

        float* data() {
            return elements;
        }

        const float* data() const {
            return elements;
        }

        float length2() const {
            return
                elements[0] * elements[0] +
                elements[1] * elements[1] +
                elements[2] * elements[2];
        }

        float length() const {
            return std::sqrt(length2());
        }

    private:

        //=================================================
        // Instance members
        //=================================================

        float elements[3] = {0.0f, 0.0f, 0.0f};

    };




    template<>
    class Vector<float, 4> {
    public:

        using scalar = float;

        static constexpr unsigned width = 4;

        //=================================================
        // Creation functions
        //=================================================

        static Vector read(float* p) {
            return Vector{p[0], p[1], p[2], p[3]};
        }

        static Vector read_aligned(float* p) {
            return Vector{p[0], p[1], p[2], p[3]};
        }

        //=================================================
        // -ctors
        //=================================================

        Vector(float x, float y, float z, float w):
            elements{x, y, z, w} {}

        Vector(Uvec4 v):
            elements{v[0], v[1], v[2], v[3]} {}

        Vector(Vec2 v, float z, float w):
            elements{v[0], v[1], z, w} {}

        Vector(float x, Vec2 v, float w):
            elements{x, v[0], v[1], w} {}

        Vector(float x, float y, Vec2 v):
            elements{x, y, v[0], v[1]} {}

        Vector(Vec2 v, Vec2 u):
            elements{v[0], v[1], u[0], u[1]} {}

        Vector(Vec3 v, float w):
            elements{v[0], v[1], v[2], w} {}

        Vector(float x, Vec3 v):
            elements{x, v[0], v[1], v[2]} {}

        Vector() = default;
        Vector(const Vector&) = default;
        Vector(Vector&&) = default;
        ~Vector() = default;

        //=================================================
        // Assignment operators
        //=================================================

        Vector& operator=(const Vector&) = default;
        Vector& operator=(Vector&&) = default;

        //=================================================
        // Arithmetic assignment operators
        //=================================================

        Vector& operator+=(const Vector& rhs) {
            for (int i = 0; i < width; ++i) {
                elements[i] += rhs[i];
            }
            return *this;
        }

        Vector& operator-=(const Vector& rhs) {
            for (int i = 0; i < width; ++i) {
                elements[i] -= rhs[i];
            }
            return *this;
        }

        //=================================================
        // Accessors
        //=================================================

        float& operator[](unsigned i) {
            return elements[i];
        }

        const float& operator[](unsigned i) const {
            return elements[i];
        }

        float* data() {
            return elements;
        }

        const float* data() const {
            return elements;
        }

        float length2() const {
            return
                elements[0] * elements[0] +
                elements[1] * elements[1] +
                elements[2] * elements[2] +
                elements[3] * elements[3];
        }

        float length() const {
            return std::sqrt(length2());
        }

    private:

        //=================================================
        // Instance members
        //=================================================

        float elements[4] = {0.0f, 0.0f, 0.0f, 0.0f};

    };

    //=========================================================================
    // Vector operator specializations
    //=========================================================================

    template<class T, unsigned N>
    AVML_FINL bool operator==(const Vector<T, N>& lhs, const Vector<T, N>& rhs) {
        bool ret = true;

        for (int i = 0; i < Vector<T, N>::width; ++i) {
            ret &= (lhs[i] == rhs[i]);
        }

        return ret;
    }

    template<class T, unsigned N>
    AVML_FINL bool operator!=(const Vector<T, N> lhs, const Vector<T, N> rhs) {
        bool ret = true;

        for (int i = 0; i < N; ++i) {
            ret &= (lhs[i] != rhs[i]);
        }

        return ret;
    }

    template<class T, unsigned N>
    AVML_FINL Vector<T, N> operator-(Vector<T, N> v) {
        for (unsigned i = 0; i < N; ++i) {
            v[i] = -v[i];
        }
        return v;
    }

    template<class T, unsigned N>
    AVML_FINL Vector<T, N> operator+(Vector<T, N> u, Vector<T, N> v) {
        for (unsigned i = 0; i < N; ++i) {
            u[i] += v[i];
        }
        return u;
    }

    template<class T, unsigned N>
    AVML_FINL Vector<T, N> operator-(Vector<T, N> u, Vector<T, N> v) {
        for (unsigned i = 0; i < N; ++i) {
            u[i] -= v[i];
        }
        return u;
    }

    template<class T, unsigned N, class U, class = typename std::enable_if<std::is_convertible<U, T>::value, U>::type>
    AVML_FINL Vector<T, N> operator*(Vector<T, N> lhs, U rhs) {
        for (int i = 0; i < N; ++i) {
            lhs[i] *= rhs;
        }
        return lhs;
    }

    template<class T, unsigned N, class U, class = typename std::enable_if<std::is_convertible<U, T>::value, U>::type>
    AVML_FINL Vector<T, N> operator*(U lhs, Vector<T, N> rhs) {
        return rhs * lhs;
    }

    template<class T, unsigned N>
    AVML_FINL Vector<T, N> operator/(Vector<T, N> lhs, typename Vector<T, N>::scalar rhs) {
        for (int i = 0; i < N; ++i) {
            lhs[i] /= rhs;
        }
        return lhs;
    }

    //=========================================================================
    // Vector function specializations
    //=========================================================================

    template<
        unsigned e0,
        unsigned e1,
        class T
    >
    AVML_FINL Vector<T, 2> swizzle(Vector<T, 2> v) {
        static_assert(e0 < 2 && e1 < 2);

        return Vector<T, 2> {
            v[e0],
            v[e1]
        };
    }

    template<
        unsigned e0,
        unsigned e1,
        unsigned e2,
        class T
    >
    AVML_FINL Vector<T, 3> swizzle(Vector<T, 3> v) {
        static_assert(e0 < 3 && e1 < 3 && e2 < 3);

        return Vector<T, 3> {
            v[e0],
            v[e1],
            v[e2]
        };
    }

    template<
        unsigned e0,
        unsigned e1,
        unsigned e2,
        unsigned e3,
        class T
    >
    AVML_FINL Vector<T, 4> swizzle(Vector<T, 4> v) {
        static_assert(e0 < 4 && e1 < 4 && e2 < 4 && e3 < 4);

        return Vector<T, 4> {
            v[e0],
            v[e1],
            v[e2],
            v[e3],
        };
    }

    template<class T, unsigned N>
    AVML_FINL Unit_vector<T, N> normalize(Vector<T, N> v) {
        v /= v.length();
        return Unit_vector<T, N>::read_aligned(v.data());
    }

    template<class T, unsigned N>
    AVML_FINL T dot(Vector<T, N> lhs, Vector<T, N> rhs) {
        T ret = 0.0f;
        for (int i = 0; i < Vector<T, N>::width; ++i) {
            ret += (lhs[i] * rhs[i]);
        }
        return ret;
    }

    template<class T, unsigned N>
    AVML_FINL T dot(Vector<T, N> lhs, Unit_vector<T, N> rhs) {
        return dot(lhs, static_cast<Vector<T, N>>(rhs));
    }

    template<class T, unsigned N>
    AVML_FINL T dot(Unit_vector<T, N> lhs, Vector<T, N> rhs) {
        return dot(static_cast<Vector<T, N>>(lhs), rhs);
    }

    template<class T, unsigned N>
    AVML_FINL T dot(Unit_vector<T, N> lhs, Unit_vector<T, N> rhs) {
        return dot(static_cast<Vector<T, N>>(lhs), static_cast<Vector<T, N>>(rhs));
    }

    template<class T>
    AVML_FINL Unit_vector<T, 3> cross(Unit_vector<T, 3> lhs, Vector<T, 3> rhs) {
        float data[3] = {
            lhs[1] * rhs[2] - lhs[2] * rhs[1],
            lhs[0] * rhs[2] - lhs[2] * rhs[0],
            lhs[0] * rhs[1] - lhs[1] * rhs[0]
        };

        return Unit_vector<T, 3>::read(data);
    }

    template<class T>
    AVML_FINL Vector<T, 3> cross(Vector<T, 3> lhs, Vector<T, 3> rhs) {
        return Vector<T, 3> {
            lhs[1] * rhs[2] - lhs[2] * rhs[1],
            lhs[0] * rhs[2] - lhs[2] * rhs[0],
            lhs[0] * rhs[1] - lhs[1] * rhs[0]
        };
    }

    template<class T, unsigned N>
    AVML_FINL Vector<T, 3> project(Vector<T, N> a, Vector<T, N> b) {
        return (dot(a, b) / dot(b, b)) * b;
    }

    template<class T, unsigned N>
    AVML_FINL Vector<T, 3> project(Vector<T, N> a, Unit_vector<T, N> b) {
        return dot(a, b) * b;
    }

    template<class T>
    AVML_FINL Vector<T, 3> project_onto_plane(Vector<T, 3> v, Unit_vector<T, 3> normal) {
        return (v - project(v, normal));
    }

    template<class T>
    AVML_FINL Unit_vector<T, 2> rotate(Unit_vector<T, 2> v, T angle) {
        float cos = std::cos(angle);
        float sin = std::sin(angle);

        return Unit_vector<T, 2> {
            v[0] * cos - v[1] * sin,
            v[0] * sin + v[1] * cos
        };
    }

    template<class T>
    AVML_FINL Vector<T, 2> rotate(Vector<T, 2> v, T angle) {
        float cos = std::cos(angle);
        float sin = std::sin(angle);

        return Vector<T, 2> {
            v[0] * cos - v[1] * sin,
            v[0] * sin + v[1] * cos
        };
    }

    template<class T>
    AVML_FINL Unit_vector<T, 3> rotate(Unit_vector<T, 3> v, T angle, Unit_vector<T, 3> axis) {
        T s = std::sin(angle);
        T c = std::cos(angle);

        return (v * c) + (cross(axis, v) * s) + (axis * dot(axis, v) * (1 - c));
    }

    template<class T>
    AVML_FINL Vector<T, 3> rotate(Vector<T, 3> v, T angle, Unit_vector<T, 3> axis) {
        T s = std::sin(angle);
        T c = std::cos(angle);

        return (v * c) + (cross(axis, v) * s) + (axis * dot(axis, v) * (1 - c));
    }

    template<class T, unsigned N>
    AVML_FINL Unit_vector<T, N> reflect(Unit_vector<T, N> v, Unit_vector<T, N> normal) {
        return Unit_vector<T, N>::read_aligned((2 * dot(v, normal) * normal - v).data());
    }

    template<class T, unsigned N>
    AVML_FINL Vector<T, N> reflect(Vector<T, N> v, Unit_vector<T, N> normal) {
        return 2 * dot(v, normal) * normal - v;
    }

}

#endif //AVML_DEF_Unit_vector2f_HPP
