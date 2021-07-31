namespace avml {

    template<>
    class alignas(4 * alignof(float)) Quaternion3Df {
    public:

        //=================================================
        // Creation methods
        //=================================================

        static Quaternion3Df read(const float* ptr) {
            Quaternion3Df ret;
            ret.components[0] = ptr[0];
            ret.components[1] = ptr[1];
            ret.components[2] = ptr[2];
            ret.components[3] = ptr[3];
            return ret;
        }

        static Quaternion3Df read_aligned(const float* ptr) {
            Quaternion3Df ret;
            ret.components[0] = ptr[0];
            ret.components[1] = ptr[1];
            ret.components[2] = ptr[2];
            ret.components[3] = ptr[3];
            return ret;
        }

        //=================================================
        // Constructors
        //=================================================

        Quaternion3Df(float angle, uvec3f axis):
            components{
                axis[0] * std::sin(angle * 0.5f),
                axis[1] * std::sin(angle * 0.5f),
                axis[2] * std::sin(angle * 0.5f),
                std::cos(angle * 0.5f)
            } {}

        Quaternion3Df() = default;
        Quaternion3Df(const Quaternion3Df&) = default;
        Quaternion3Df(Quaternion3Df&&) = default
        ~Quaternion3Df() = default;

        //=================================================
        // Assignment operators
        //=================================================

        Quaternion3Df& operator=(const Quaternion3Df&) = default;
        Quaternion3Df& operator=(Quaternion3Df&&) = default;

        //=================================================
        // Arithmetic operations
        //=================================================

        Quaternion3Df& operator*=(float f);

        //=================================================
        // Accessors
        //=================================================

        float operator[](unsigned i) const {
            return components[i];
        }

        float* data() const {
            return components;
        }

        //=================================================
        // Instance members
        //=================================================

    private:

        float components[4] = {0.0f, 0.0f, 0.0f, 1.0f};

    };

    Quaternion3Df operator-(Quaternion3Df q);

}
