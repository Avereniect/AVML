#ifndef AVML_DEF_UVEC4_IPP
#define AVML_DEF_UVEC4_IPP

namespace avml {

    template<class R>
    class alignas(alignof(R) * 4) Unit_vector4 {
    public:

        using scalar = R;

        static constexpr unsigned width = 4;

        //=================================================
        // Creation functions
        //=================================================

        AVML_FINL static Unit_vector4 read(const R* p) {
            return Unit_vector4{p[0], p[1], p[2], p[3]};
        }

        AVML_FINL static Unit_vector4 read_aligned(const R* p) {
            return Unit_vector4{p[0], p[1], p[2], p[3]};
        }

        //=================================================
        // -ctors
        //=================================================

        AVML_FINL Unit_vector4(R x, R y, R z, R w) :
            elements() {
            R length = std::sqrt(x * x + y * y + z * z + w * w);

            elements[0] = x / length;
            elements[1] = y / length;
            elements[2] = z / length;
            elements[3] = w / length;
        }

        AVML_FINL Unit_vector4(Unit_vector3<R> v) :
            elements{v[0], v[1], v[2], 0.0f} {}

        Unit_vector4() = default;
        Unit_vector4(const Unit_vector4&) = default;
        Unit_vector4(Unit_vector4&&) = default;
        ~Unit_vector4() = default;

        //=================================================
        // Assignment operators
        //=================================================

        Unit_vector4& operator=(const Unit_vector4&) = default;
        Unit_vector4& operator=(Unit_vector4&&) = default;

        //=================================================
        // Unary arithmetic operators
        //=================================================

        AVML_FINL Unit_vector4 operator+() const {
            return *this;
        }

        AVML_FINL Unit_vector4 operator-() const {
            Unit_vector4 ret;
            ret.elements[0] = -elements[0];
            ret.elements[1] = -elements[1];
            ret.elements[2] = -elements[2];
            ret.elements[3] = -elements[3];
            return ret;
        }

        //=================================================
        // Accessors
        //=================================================

        AVML_FINL const R& operator[](unsigned i) const {
            return elements[i];
        }

        AVML_FINL const R* data() const {
            return elements;
        }

    private:

        //=================================================
        // Instance members
        //=================================================

        R elements[width] = {1.0f, 0.0f, 0.0f, 0.0f};

    };

    //=====================================================
    // Vectorized math
    //=====================================================

    template<class R>
    AVML_FINL Unit_vector4<R> abs(Unit_vector4<R> v) {
        alignas(alignof(Unit_vector4<R>)) R data[Unit_vector4<R>::width];
        using std::abs;
        data[0] = abs(v[0]);
        data[1] = abs(v[1]);
        data[2] = abs(v[2]);
        data[3] = abs(v[3]);
        return Unit_vector4<R>::read_aligned(data);
    }

}

#endif
