#ifndef AVML_DEF_UVEC2F_IPP
#define AVML_DEF_UVEC2F_IPP

namespace avml {

    template<>
    class alignas(sizeof(float) * 2) Unit_vector2R<float> {
    public:

        using scalar = float;

        static constexpr unsigned width = 2;

        //=================================================
        // Creation functions
        //=================================================

        AVML_FINL static Unit_vector2R read(const float* p) {
            return Unit_vector2R{p[0], p[1]};
        }

        AVML_FINL static Unit_vector2R read_aligned(const float* p) {
            return Unit_vector2R{p[0], p[1]};
        }

        //=================================================
        // -ctors
        //=================================================

        AVML_FINL Unit_vector2R(float x, float y):
            elements() {
            float length = std::sqrt(x * x + y * y);

            elements[0] = x / length;
            elements[1] = y / length;
        }

        Unit_vector2R() = default;
        Unit_vector2R(const Unit_vector2R&) = default;
        Unit_vector2R(Unit_vector2R&&) = default;
        ~Unit_vector2R() = default;

        //=================================================
        // Assignment operators
        //=================================================

        Unit_vector2R& operator=(const Unit_vector2R&) = default;
        Unit_vector2R& operator=(Unit_vector2R&&) = default;

        //=================================================
        // Unary arithmetic operators
        //=================================================

        AVML_FINL Unit_vector2R operator+() const {
            return *this;
        }

        AVML_FINL Unit_vector2R operator-() const {
            Unit_vector2R ret;
            ret.elements[0] = -elements[0];
            ret.elements[1] = -elements[1];
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

        //=================================================
        // Conversion operators
        //=================================================

        template<class U>
        explicit operator Unit_vector2R<U>() const {
            Unit_vector2R<U> ret;
            ret.elements[0] = static_cast<U>(elements[0]);
            ret.elements[1] = static_cast<U>(elements[1]);
            return ret;
        }

    private:

        //=================================================
        // Instance members
        //=================================================

        float elements[width] = {1.0f, 0.0f};

    };

    //=====================================================
    // Vectorized math
    //=====================================================

    AVML_FINL uvec2f abs(uvec2f v) {
        alignas(alignof(uvec2f)) float data[uvec2f::width];
        data[0] = std::abs(v[0]);
        data[1] = std::abs(v[1]);
        return uvec2f::read_aligned(data);
    }

}

#endif
