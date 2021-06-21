namespace avml {

    template<>
    class alignas(sizeof(float) * 1) Vector<float, 3> {
    public:

        using scalar = float;

        static constexpr unsigned width = 3;

        //=================================================
        // Creation functions
        //=================================================

        AVML_FINL static Vector read(const float* p) {
            return Vector{p[0], p[1], p[2]};
        }

        AVML_FINL static Vector read_aligned(const float* p) {
            return Vector{p[0], p[1], p[2]};
        }

        //=================================================
        // -ctors
        //=================================================

        AVML_FINL Vector(float v):
            elements{v, v, v} {}

        AVML_FINL Vector(float x, float y, float z):
            elements{x, y, z} {}

        AVML_FINL Vector(Unit_vector<float, 3> v):
            elements{v[0], v[1], v[2]} {}

        AVML_FINL Vector(Vector<float, 2> v, float z):
            elements{v[0], v[1], z} {}

        AVML_FINL Vector(float w, Vector<float, 2> v):
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

        float elements[width] = {0.0f, 0.0f, 0.0f};

    };

    AVML_FINL bool operator==(Vec3f lhs, Vec3f rhs) {
        return
            (lhs[0] == rhs[0]) &&
            (lhs[1] == rhs[1]) &&
            (lhs[2] == rhs[2]);
    }

    AVML_FINL bool operator!=(Vec3f lhs, Vec3f rhs) {
        return
            (lhs[0] != rhs[0]) ||
            (lhs[1] != rhs[1]) ||
            (lhs[2] != rhs[2]);
    }

    AVML_FINL Vec3f operator+(Vec3f lhs, Vec3f rhs) {
        lhs[0] += rhs[0];
        lhs[1] += rhs[1];
        lhs[2] += rhs[2];
        return lhs;
    }

    AVML_FINL Vec3f operator-(Vec3f lhs, Vec3f rhs) {
        lhs[0] -= rhs[0];
        lhs[1] -= rhs[1];
        lhs[2] -= rhs[2];
        return lhs;
    }

    AVML_FINL Vec3f operator*(Vec3f lhs, float rhs) {
        lhs[0] *= rhs;
        lhs[1] *= rhs;
        lhs[2] *= rhs;
        return lhs;
    }

    AVML_FINL Vec3f operator*(float lhs, Vec3f rhs) {
        rhs[0] *= lhs;
        rhs[1] *= lhs;
        rhs[2] *= lhs;
        return rhs;
    }

    AVML_FINL Vec3f operator/(Vec3f lhs, float rhs) {
        lhs[0] /= rhs;
        lhs[1] /= rhs;
        lhs[2] /= rhs;
        return lhs;
    }

    AVML_FINL float dot(Vec3f lhs, Vec3f rhs) {
        return
            lhs[0] * rhs[0] +
            lhs[1] * rhs[1] +
            lhs[2] * rhs[2];
    }

    AVML_FINL float length2(Uvec3f) = delete;

    AVML_FINL float length2(Vec3f v) {
        return dot(v, v);
    }

    AVML_FINL float length(Uvec3f) = delete;

    AVML_FINL float length(Vec3f v) {
        return std::sqrt(length2(v));
    }

    AVML_FINL Unit_vector<float, 3> normalize(Vec3f v) {
        v /= length(v);
        return Unit_vector<float, 3>::read_aligned(v.data());
    }

    AVML_FINL Vec3f cross(Vec3f lhs, Vec3f rhs) {
        return Vec3f {
            lhs[1] * rhs[2] - lhs[2] * rhs[1],
            lhs[0] * rhs[2] - lhs[2] * rhs[0],
            lhs[0] * rhs[1] - lhs[1] * rhs[0]
        };
    }

    AVML_FINL Vec3f project(Vec3f a, Vec3f b) {
        return (dot(a, b) / dot(b, b)) * b;
    }

    AVML_FINL Vec3f project(Vec3f a, Uvec3f b) {
        return dot(a, b) * b;
    }

    AVML_FINL Vec3f project_onto_plane(Vec3f v, Uvec3f normal) {
        return (v - project(v, normal));
    }

    AVML_FINL Vec3f rotate(Vec3f v, float angle, Uvec3f axis) {
        float s = std::sin(angle);
        float c = std::cos(angle);

        return (v * c) + (cross(axis, v) * s) + (axis * dot(axis, v) * (1 - c));
    }

    AVML_FINL Uvec3f rotate(Uvec3f v, float angle, Uvec3f axis) {
        return Uvec3f::read_aligned(rotate(static_cast<Vec3f>(v), angle, axis).data());
    }

    AVML_FINL Vec3f reflect(Vec3f v, Uvec3f normal) {
        return 2 * dot(v, normal) * normal - v;
    }

    AVML_FINL Uvec3f reflect(Uvec3f v, Uvec3f normal) {
        return Uvec3f::read_aligned(reflect(static_cast<Vec3f>(v), normal).data());
    }

}
