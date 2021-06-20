namespace avml {

    template<>
    class alignas(sizeof(float) * 2) Unit_vector<float, 2> {
    public:

        using scalar = float;

        static constexpr unsigned width = 2;

        //=================================================
        // Creation functions
        //=================================================

        AVML_FINL static Unit_vector read(const float* p) {
            return Unit_vector{p[0], p[1]};
        }

        AVML_FINL static Unit_vector read_aligned(const float* p) {
            return Unit_vector{p[0], p[1]};
        }

        //=================================================
        // -ctors
        //=================================================

        AVML_FINL Unit_vector(float x, float y):
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

        float elements[width] = {1.0f, 0.0f};

    };

}
