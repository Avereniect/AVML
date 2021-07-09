#ifndef AVML_DEF_UVEC4F_IPP
#define AVML_DEF_UVEC4F_IPP

namespace avml {

    template<>
    class alignas(sizeof(float) * 4) Unit_vector<float, 4> {
    public:

        using scalar = float;

        static constexpr unsigned width = 4;

        //=================================================
        // Creation functions
        //=================================================

        AVML_FINL static Unit_vector read(const float* p) {
            return Unit_vector{p[0], p[1], p[2], p[3]};
        }

        AVML_FINL static Unit_vector read_aligned(const float* p) {
            return Unit_vector{p[0], p[1], p[2], p[3]};
        }

        //=================================================
        // -ctors
        //=================================================

        AVML_FINL Unit_vector(float x, float y, float z, float w) :
            elements() {
            float length = std::sqrt(x * x + y * y + z * z + w * w);

            elements[0] = x / length;
            elements[1] = y / length;
            elements[2] = z / length;
            elements[3] = w / length;
        }

        AVML_FINL Unit_vector(uvec3f v) :
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

        float elements[width] = {1.0f, 0.0f, 0.0f, 0.0f};

    };

    //=====================================================
    // Vectorized math
    //=====================================================

    AVML_FINL uvec4f abs(uvec4f v) {
        alignas(alignof(uvec4f)) float data[uvec4f::width];
        data[0] = std::abs(v[0]);
        data[1] = std::abs(v[1]);
        data[2] = std::abs(v[2]);
        return uvec4f::read_aligned(data);
    }

}

#endif
