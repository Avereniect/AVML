namespace avml {

    template<>
    class Vector<float, 4> {
    public:

        using scalar = float;

        static constexpr unsigned width = 4;

        //=================================================
        // Creation functions
        //=================================================

        AVML_FINL static Vector read(const float* p) {
            return Vector{p[0], p[1], p[2], p[3]};
        }

        AVML_FINL static Vector read_aligned(const float* p) {
            return Vector{p[0], p[1], p[2], p[3]};
        }

        //=================================================
        // -ctors
        //=================================================

        AVML_FINL Vector(float x, float y, float z, float w):
            elements{x, y, z, w} {}

        AVML_FINL Vector(Uvec4f v):
            elements{v[0], v[1], v[2], v[3]} {}

        AVML_FINL Vector(Vec2f v, float z, float w):
            elements{v[0], v[1], z, w} {}

        AVML_FINL Vector(float x, Vec2f v, float w):
            elements{x, v[0], v[1], w} {}

        AVML_FINL Vector(float x, float y, Vec2f v):
            elements{x, y, v[0], v[1]} {}

        AVML_FINL Vector(Vec2f v, Vec2f u):
            elements{v[0], v[1], u[0], u[1]} {}

        AVML_FINL Vector(Vec3f v, float w):
            elements{v[0], v[1], v[2], w} {}

        AVML_FINL Vector(float x, Vec3f v):
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

        AVML_FINL Vector& operator+=(const Vector& rhs) {
            for (int i = 0; i < width; ++i) {
                elements[i] += rhs[i];
            }
            return *this;
        }

        AVML_FINL Vector& operator-=(const Vector& rhs) {
            for (int i = 0; i < width; ++i) {
                elements[i] -= rhs[i];
            }
            return *this;
        }

        AVML_FINL Vector& operator*=(const scalar rhs) {
            for (int i = 0; i < width; ++i) {
                elements[i] *= rhs;
            }
            return *this;
        }

        AVML_FINL Vector& operator/=(const scalar rhs) {
            for (int i = 0; i < width; ++i) {
                elements[i] /= rhs;
            }
            return *this;
        }

        //=================================================
        // Accessors
        //=================================================

        AVML_FINL float& operator[](unsigned i) {
            return elements[i];
        }

        AVML_FINL const float& operator[](unsigned i) const {
            return elements[i];
        }

        AVML_FINL float* data() {
            return elements;
        }

        AVML_FINL const float* data() const {
            return elements;
        }

        AVML_FINL float length2() const {
            return
                elements[0] * elements[0] +
                elements[1] * elements[1] +
                elements[2] * elements[2] +
                elements[3] * elements[3];
        }

        AVML_FINL float length() const {
            return std::sqrt(length2());
        }

    private:

        //=================================================
        // Instance members
        //=================================================

        float elements[width] = {0.0f, 0.0f, 0.0f, 0.0f};

    };

    AVML_FINL bool operator==(Vec4f lhs, Vec4f rhs) {
        return
            (lhs[0] == rhs[0]) &&
            (lhs[1] == rhs[1]) &&
            (lhs[2] == rhs[2]) &&
            (lhs[3] == rhs[3]);
    }

    AVML_FINL bool operator!=(Vec4f lhs, Vec4f rhs) {
        return
            (lhs[0] != rhs[0]) ||
            (lhs[1] != rhs[1]) ||
            (lhs[2] != rhs[2]) ||
            (lhs[3] != rhs[3]);
    }

    AVML_FINL Vec4f operator+(Vec4f lhs, Vec4f rhs) {
        lhs[0] += rhs[0];
        lhs[1] += rhs[1];
        lhs[2] += rhs[2];
        lhs[3] += rhs[3];
        return lhs;
    }

    AVML_FINL Vec4f operator-(Vec4f lhs, Vec4f rhs) {
        lhs[0] -= rhs[0];
        lhs[1] -= rhs[1];
        lhs[2] -= rhs[2];
        lhs[3] -= rhs[3];
        return lhs;
    }

    AVML_FINL Vec4f operator*(Vec4f lhs, float rhs) {
        lhs[0] *= rhs;
        lhs[1] *= rhs;
        lhs[2] *= rhs;
        lhs[3] *= rhs;
        return lhs;
    }

    AVML_FINL Vec4f operator*(float lhs, Vec4f rhs) {
        rhs[0] *= lhs;
        rhs[1] *= lhs;
        rhs[2] *= lhs;
        rhs[3] *= lhs;
        return rhs;
    }

    AVML_FINL Vec4f operator/(Vec4f lhs, float rhs) {
        lhs[0] /= rhs;
        lhs[1] /= rhs;
        lhs[2] /= rhs;
        lhs[3] /= rhs;
        return lhs;
    }

    AVML_FINL Unit_vector<float, 4> normalize(Vec4f v) {
        v /= v.length();
        return Unit_vector<float, 4>::read_aligned(v.data());
    }

    AVML_FINL float dot(Vec4f lhs, Vec4f rhs) {
        return
            lhs[0] * rhs[0] +
            lhs[1] * rhs[1] +
            lhs[2] * rhs[2] +
            lhs[3] * rhs[2];
    }

    AVML_FINL Vec4f project(Vec4f a, Vec4f b) {
        return (dot(a, b) / dot(b, b)) * b;
    }

    AVML_FINL Vec4f project(Vec4f a, Uvec4f b) {
        return dot(a, b) * b;
    }

    AVML_FINL Vec4f reflect(Vec4f v, Uvec4f normal) {
        return 2 * dot(v, normal) * normal - v;
    }

    AVML_FINL Uvec4f reflect(Uvec4f v, Uvec4f normal) {
        return Uvec4f::read_aligned(reflect(static_cast<Vec4f>(v), normal).data());
    }

}
