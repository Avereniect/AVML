#ifndef AVML_GEN_UVEC2F_IPP
#define AVML_GEN_UVEC2F_IPP

namespace avml {

    template<class R>
    class alignas(avml_impl::vector_alignment<R, 2>()) Unit_vector2 {
    public:

        using scalar = R;

        static constexpr unsigned width = 2;

        //=================================================
        // Creation functions
        //=================================================

        AVML_FINL static Unit_vector2 read(const R* p) {
            return Unit_vector2{p[0], p[1]};
        }

        AVML_FINL static Unit_vector2 read_aligned(const R* p) {
            return Unit_vector2{p[0], p[1]};
        }

        //=================================================
        // -ctors
        //=================================================

        AVML_FINL Unit_vector2(R x, R y):
            elements() {
            using std::sqrt;
            R length = sqrt(x * x + y * y);

            elements[0] = x / length;
            elements[1] = y / length;
        }

        Unit_vector2() = default;
        Unit_vector2(const Unit_vector2&) = default;
        Unit_vector2(Unit_vector2&&) noexcept = default;
        ~Unit_vector2() = default;

        //=================================================
        // Assignment operators
        //=================================================

        Unit_vector2& operator=(const Unit_vector2&) = default;
        Unit_vector2& operator=(Unit_vector2&&) noexcept = default;

        //=================================================
        // Unary arithmetic operators
        //=================================================

        AVML_FINL Unit_vector2 operator+() const {
            return *this;
        }

        AVML_FINL Unit_vector2 operator-() const {
            Unit_vector2 ret;
            ret.elements[0] = -elements[0];
            ret.elements[1] = -elements[1];
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

        R elements[width] = {1.0f, 0.0f};

    };

    //=====================================================
    // Vectorized math
    //=====================================================

    template<class R>
    AVML_FINL Unit_vector2<R> abs(Unit_vector2<R> v) {
        alignas(alignof(Unit_vector2<R>)) R data[Unit_vector2<R>::width];
        using std::abs;
        data[0] = abs(v[0]);
        data[1] = abs(v[1]);
        return Unit_vector2<R>::read_aligned(data);
    }

}

#endif