#ifndef AVML_DEF_UVEC3F_IPP
#define AVML_DEF_UVEC3F_IPP

namespace avml {

    template<>
    class alignas(sizeof(float) * 1) Unit_vector<float, 3> {
    public:

        using scalar = float;

        static constexpr unsigned width = 3;

        //=================================================
        // Creation functions
        //=================================================

        AVML_FINL static Unit_vector read(const float* p) {
            return Unit_vector{p[0], p[1], p[2]};
        }

        AVML_FINL static Unit_vector read_aligned(const float* p) {
            return Unit_vector{p[0], p[1], p[2]};
        }

        //=================================================
        // -ctors
        //=================================================

        AVML_FINL Unit_vector(float x, float y, float z):
            elements() {
            float length = std::sqrt(x * x + y * y + z * z);

            elements[0] = x / length;
            elements[1] = y / length;
            elements[2] = z / length;
        }

        AVML_FINL Unit_vector(uvec2f v):
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

        AVML_FINL const float& operator[](unsigned i) const {
            return elements[i];
        }

        AVML_FINL const float* data() const {
            return elements;
        }

    private:

        //=================================================
        // Instance members
        //=================================================

        float elements[width] = {1.0f, 0.0f, 0.0f};

    };

    AVML_FINL uvec3f cross(uvec3f lhs, uvec3f rhs) {
        float data[3] = {
            lhs[1] * rhs[2] - lhs[2] * rhs[1],
            lhs[2] * rhs[0] - lhs[0] * rhs[2],
            lhs[0] * rhs[1] - lhs[1] * rhs[0]
        };

        return uvec3f::read(data);
    }

    //=====================================================
    // Vectorized math
    //=====================================================

    AVML_FINL uvec3f abs(uvec3f v) {
        alignas(alignof(uvec3f)) float data[uvec3f::width];
        data[0] = std::abs(v[0]);
        data[1] = std::abs(v[1]);
        data[2] = std::abs(v[2]);
        return uvec3f::read_aligned(data);
    }

}

#endif
