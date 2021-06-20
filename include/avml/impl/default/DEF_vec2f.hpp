namespace avml {

    template<>
    class Vector<float, 2> {
    public:

        using scalar = float;

        static constexpr unsigned width = 2;

        //=================================================
        // Creation functions
        //=================================================

        AVML_FINL static Vector read(const float* p) {
            return Vector{p[0], p[1]};
        }

        AVML_FINL static Vector read_aligned(const float* p) {
            return Vector{p[0], p[1]};
        }

        //=================================================
        // -ctors
        //=================================================

        AVML_FINL Vector(float x, float y):
            elements{x, y} {}

        AVML_FINL Vector(Uvec2f v):
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

    private:

        //=================================================
        // Instance members
        //=================================================

        float elements[width] = {0.0f, 0.0f};

    };

    AVML_FINL bool operator==(Vec2f lhs, Vec2f rhs) {
        return
            (lhs[0] == rhs[0]) &&
            (lhs[1] == rhs[1]);
    }

    AVML_FINL bool operator!=(Vec2f lhs, Vec2f rhs) {
        return
            (lhs[0] != rhs[0]) ||
            (lhs[1] != rhs[1]);
    }

    AVML_FINL Vec2f operator+(Vec2f lhs, Vec2f rhs) {
        lhs[0] += rhs[0];
        lhs[1] += rhs[1];
        return lhs;
    }

    AVML_FINL Vec2f operator-(Vec2f lhs, Vec2f rhs) {
        lhs[0] -= rhs[0];
        lhs[1] -= rhs[1];
        return lhs;
    }

    AVML_FINL Vec2f operator*(Vec2f lhs, float rhs) {
        lhs[0] *= rhs;
        lhs[1] *= rhs;
        return lhs;
    }

    AVML_FINL Vec2f operator*(float lhs, Vec2f rhs) {
        rhs[0] *= lhs;
        rhs[1] *= lhs;
        return rhs;
    }

    AVML_FINL Vec2f operator/(Vec2f lhs, float rhs) {
        lhs[0] /= rhs;
        lhs[1] /= rhs;
        return lhs;
    }

    AVML_FINL float dot(Vec2f lhs, Vec2f rhs) {
        return
            lhs[0] * rhs[0] +
            lhs[1] * rhs[1];
    }

    AVML_FINL float length2(Uvec2f) = delete;

    AVML_FINL float length2(Vec2f v) {
        return dot(v, v);
    }

    AVML_FINL float length(Uvec2f) = delete;

    AVML_FINL float length(Vec2f v) {
        return std::sqrt(length2(v));
    }

    AVML_FINL Uvec2f normalize(Vec2f v) {
        v /= length(v);
        return Uvec2f::read_aligned(v.data());
    }

    AVML_FINL Vec2f project(Vec2f a, Vec2f b) {
        return (dot(a, b) / dot(b, b)) * b;
    }

    AVML_FINL Vec2f project(Vec2f a, Uvec2f b) {
        return dot(a, b) * b;
    }

    AVML_FINL Vec2f rotate(Vec2f v, float angle) {
        float cos = std::cos(angle);
        float sin = std::sin(angle);

        return Vec2f{
            v[0] * cos - v[1] * sin,
            v[0] * sin + v[1] * cos
        };
    }

    AVML_FINL Vec2f reflect(Vec2f v, Uvec2f normal) {
        return 2 * dot(v, normal) * normal - v;
    }

    AVML_FINL Uvec2f reflect(Uvec2f v, Uvec2f normal) {
        return Uvec2f::read_aligned(reflect(static_cast<Vec2f>(v), normal).data());
    }

}
