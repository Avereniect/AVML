namespace avml {

    template<>
    class alignas(alignof(float) * 2) Vector2R<float> {
    public:

        using scalar = float;

        static constexpr unsigned width = 2;

        //=================================================
        // Creation functions
        //=================================================

        AVML_FINL static Vector2R read(const float* p) {
            return Vector2R{p[0], p[1]};
        }

        AVML_FINL static Vector2R read_aligned(const float* p) {
            return Vector2R{p[0], p[1]};
        }

        //=================================================
        // -ctors
        //=================================================

        //TODO: Implement conversions from other vectors

        //explicit AVML_FINL Vector2R(Vector2R<double> v):
        //    elements{} {}

        AVML_FINL Vector2R(float v):
            elements{} {

            #if defined(AVML_AVX)
            __m128 r = _mm_set_ss(v);
            r = _mm_permute_ps(r, 0x00);
            avml_impl::store2f(elements, r);

            #elif defined(AVML_SSE)
            __m128 r = _mm_set_ss(v);
            r = _mm_shuffle_ps(r, r, 0x00);
            avml_impl::store2f(elements, r);

            #else
            elements[0] = v;
            elements[1] = v;
            #endif
        }

        AVML_FINL Vector2R(float x, float y):
            elements{x, y} {}

        AVML_FINL Vector2R(uvec2f v):
            elements{v[0], v[1]} {}

        Vector2R() = default;
        Vector2R(const Vector2R&) = default;
        Vector2R(Vector2R&&) = default;
        ~Vector2R() = default;

        //=================================================
        // Assignment operators
        //=================================================

        Vector2R& operator=(const Vector2R&) = default;
        Vector2R& operator=(Vector2R&&) = default;

        //=================================================
        // Unary arithmetic operators
        //=================================================

        AVML_FINL Vector2R operator+() const {
            return *this;
        }

        AVML_FINL Vector2R operator-() const {
            return Vector2R{
                -elements[0],
                -elements[1]
            };
        }

        //=================================================
        // Arithmetic assignment operators
        //=================================================

        AVML_FINL Vector2R& operator+=(const Vector2R& rhs) {
            #if defined(AVML_SSE)
            __m128 r0 = avml_impl::load2f(elements);
            __m128 r1 = avml_impl::load2f(rhs.elements);

            __m128 writeback = _mm_add_ps(r0, r1);
            avml_impl::store2f(elements, writeback);
            #else
            for (unsigned i = 0; i < width; ++i) {
                elements[i] += rhs[i];
            }
            #endif
            return *this;
        }

        AVML_FINL Vector2R& operator-=(const Vector2R& rhs) {
            #if defined(AVML_SSE)
            __m128 r0 = avml_impl::load2f(elements);
            __m128 r1 = avml_impl::load2f(rhs.elements);

            __m128 writeback = _mm_sub_ps(r0, r1);
            avml_impl::store2f(elements, writeback);
            #else
            for (unsigned i = 0; i < width; ++i) {
                elements[i] -= rhs[i];
            }
            #endif
            return *this;
        }

        AVML_FINL Vector2R& operator*=(const Vector2R rhs) {
            #if defined(AVML_SSE)
            __m128 r0 = avml_impl::load2f(elements);
            __m128 r1 = avml_impl::load2f(rhs.elements);

            __m128 writeback = _mm_mul_ps(r0, r1);
            avml_impl::store2f(elements, writeback);
            #else
            for (unsigned i = 0; i < width; ++i) {
                elements[i] *= rhs[i];
            }
            #endif
            return *this;
        }

        AVML_FINL Vector2R& operator*=(const scalar rhs) {

            return *this;
        }

        AVML_FINL Vector2R& operator/=(const Vector2R rhs) {
            for (unsigned i = 0; i < width; ++i) {
                elements[i] /= rhs[i];
            }
            return *this;
        }

        AVML_FINL Vector2R& operator/=(const scalar rhs) {
            for (unsigned i = 0; i < width; ++i) {
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

        //=================================================
        // Conversion operators
        //=================================================

        /*
        template<class R, class = typename std::enable_if<>::type>
        explicit operator Vector2R<R>() const {

        }

        template<class I, class = typename std::enable_if<>::type>
        explicit operator Vector2I<I>() const {

        }
        */

    private:

        //=================================================
        // Instance members
        //=================================================

        float elements[width] = {0.0f, 0.0f};

    };

    //=====================================================
    // Comparison operators
    //=====================================================

    AVML_FINL bool operator==(vec2f lhs, vec2f rhs) {
        return
            (lhs[0] == rhs[0]) &&
            (lhs[1] == rhs[1]);
    }

    AVML_FINL bool operator!=(vec2f lhs, vec2f rhs) {
        return
            (lhs[0] != rhs[0]) ||
            (lhs[1] != rhs[1]);
    }

    //=====================================================
    // Arithmetic operators
    //=====================================================

    AVML_FINL vec2f operator+(vec2f lhs, vec2f rhs) {
        lhs += rhs;
        return lhs;
    }

    AVML_FINL vec2f operator-(vec2f lhs, vec2f rhs) {
        lhs -= rhs;
        return lhs;
    }

    AVML_FINL vec2f operator*(vec2f lhs, vec2f rhs) {
        lhs *= rhs;
        return lhs;
    }

    AVML_FINL vec2f operator*(vec2f lhs, float rhs) {
        lhs *= rhs;
        return lhs;
    }

    AVML_FINL vec2f operator*(float lhs, vec2f rhs) {
        rhs *= lhs;
        return rhs;
    }

    AVML_FINL vec2f operator/(vec2f lhs, float rhs) {
        lhs /= rhs;
        return lhs;
    }

    AVML_FINL vec2f operator/(vec2f lhs, vec2f rhs) {
        lhs /= rhs;
        return lhs;
    }

    //=====================================================
    // Vector math
    //=====================================================

    AVML_FINL float dot(vec2f lhs, vec2f rhs) {
        return
            lhs[0] * rhs[0] +
            lhs[1] * rhs[1];
    }

    AVML_FINL float length2(uvec2f) = delete;

    AVML_FINL float length2(vec2f v) {
        return dot(v, v);
    }

    AVML_FINL float length(uvec2f) = delete;

    AVML_FINL float length(vec2f v) {
        return std::sqrt(length2(v));
    }

    AVML_FINL uvec2f normalize(vec2f v) {
        v /= length(v);
        return uvec2f::read_aligned(v.data());
    }

    AVML_FINL uvec2f assume_normalized(vec2f v) {
        return uvec2f::read_aligned(v.data());
    }

    AVML_FINL vec2f project(vec2f a, vec2f b) {
        return (dot(a, b) / dot(b, b)) * b;
    }

    AVML_FINL vec2f project(vec2f a, uvec2f b) {
        return dot(a, b) * b;
    }

    AVML_FINL vec2f rotate(vec2f v, float angle) {
        float cos = std::cos(angle);
        float sin = std::sin(angle);

        return vec2f{
            v[0] * cos - v[1] * sin,
            v[0] * sin + v[1] * cos
        };
    }

    AVML_FINL vec2f reflect(vec2f v, uvec2f normal) {
        return 2 * dot(v, normal) * normal - v;
    }

    AVML_FINL uvec2f reflect(uvec2f v, uvec2f normal) {
        return uvec2f::read_aligned(reflect(static_cast<vec2f>(v), normal).data());
    }

    //=====================================================
    // Vectorized math
    //=====================================================

    AVML_FINL vec2f abs(vec2f v) {
        v[0] = std::abs(v[0]);
        v[1] = std::abs(v[1]);
        return v;
    }

    AVML_FINL vec2f max(vec2f u, vec2f v) {
        u[0] = std::max(u[0], v[0]);
        u[1] = std::max(u[1], v[1]);
        return u;
    }

    AVML_FINL vec2f min(vec2f u, vec2f v) {
        u[0] = std::min(u[0], v[0]);
        u[1] = std::min(u[1], v[1]);
        return u;
    }

    //=====================================================
    // Swizzling
    //=====================================================

    // Single component

    AVML_FINL float x(vec2f v) {
        return v[0];
    }

    AVML_FINL float y(vec2f v) {
        return v[1];
    }

    // Two component

    AVML_FINL vec2f xy(vec2f v) {
        return v;
    }

    AVML_FINL vec2f yx(vec2f v) {
        return {v[1], v[0]};
    }

}
