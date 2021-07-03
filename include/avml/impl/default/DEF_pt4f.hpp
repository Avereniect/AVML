namespace avml {

    template<>
    class alignas(sizeof(float) * 4) Point<float, 4> {
    public:

        using scalar = float;

        static constexpr unsigned width = 4;

        //=================================================
        // Creation functions
        //=================================================

        static Point read(float* p) {
            return Point{p[0], p[1], p[2], p[3]};
        }

        static Point read_aligned(float* p) {
            return Point{p[0], p[1], p[2], p[3]};
        }

        //=================================================
        // -ctors
        //=================================================

        AVML_FINL Point(float x, float y, float z, float w):
            elements{x, y, z, w} {}

        AVML_FINL Point(Pt2f v, float z, float w):
            elements{v[0], v[1], z, w} {}

        AVML_FINL Point(float x, Pt2f v, float w):
            elements{x, v[0], v[1], w} {}

        AVML_FINL Point(float x, float y, Pt2f v):
            elements{x, y, v[0], v[1]} {}

        AVML_FINL Point(Pt2f v, Pt2f u):
            elements{v[0], v[1], u[0], u[1]} {}

        AVML_FINL Point(Pt3f v, float w):
            elements{v[0], v[1], v[2], w} {}

        AVML_FINL Point(float x, Pt3f v):
            elements{x, v[0], v[1], v[2]} {}

        explicit AVML_FINL Point(Vec4f v):
            elements{v[0], v[1], v[2], v[3]} {}

        Point() = default;
        Point(const Point&) = default;
        Point(Point&&) = default;
        ~Point() = default;

        //=================================================
        // Assignment operators
        //=================================================

        Point& operator=(const Point&) = default;
        Point& operator=(Point&&) = default;

        //=================================================
        // Arithmetic assignment operators
        //=================================================

        AVML_FINL Point& operator+=(Vec4f rhs) {
            elements[0] += rhs[0];
            elements[1] += rhs[1];
            elements[2] += rhs[2];
            elements[3] += rhs[3];
            return *this;
        }

        AVML_FINL Point& operator-=(Vec4f rhs) {
            elements[0] -= rhs[0];
            elements[1] -= rhs[1];
            elements[2] -= rhs[2];
            elements[3] -= rhs[3];
            return *this;
        }

        //=================================================
        // Accessors
        //=================================================

        AVML_FINL float& operator[](unsigned i) {
            return  elements[i];
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

        AVML_FINL explicit operator Vec4f() const {
            return Vec4f{
                elements[0],
                elements[1],
                elements[2],
                elements[3]
            };
        }

    private:

        //=================================================
        // Instance members
        //=================================================

        float elements[width];

    };

    //=====================================================
    // Comparison operators
    //=====================================================

    AVML_FINL bool operator==(Pt4f lhs, Pt4f rhs) {
        return
            lhs[0] == rhs[0] &&
            lhs[1] == rhs[1] &&
            lhs[2] == rhs[2] &&
            lhs[3] == rhs[3];
    }

    AVML_FINL bool operator!=(Pt4f lhs, Pt4f rhs) {
        return
            lhs[0] != rhs[0] &&
            lhs[1] != rhs[1] &&
            lhs[2] != rhs[2] &&
            lhs[3] != rhs[3];
    }

    //=====================================================
    // Arithmetic operators
    //=====================================================

    AVML_FINL Pt4f operator+(Pt4f lhs, Vec4f rhs) {
        lhs += rhs;
        return lhs;
    }

    AVML_FINL Pt4f operator+(Vec4f lhs, Pt4f rhs) {
        rhs += lhs;
        return rhs;
    }

    AVML_FINL Pt4f operator-(Pt4f lhs, Vec4f rhs) {
        lhs -= rhs;
        return lhs;
    }

    AVML_FINL Vec4f operator-(Pt4f lhs, Pt4f rhs) {
        return Vec4f {
          lhs[0] - rhs[0],
          lhs[1] - rhs[1],
          lhs[2] - rhs[2],
          lhs[3] - rhs[3]
        };
    }

    //=====================================================
    // Vectorized math
    //=====================================================

    AVML_FINL Pt4f abs(Pt4f v) {
        v[0] = std::abs(v[0]);
        v[1] = std::abs(v[1]);
        v[2] = std::abs(v[2]);
        v[3] = std::abs(v[3]);
        return v;
    }

    AVML_FINL Pt4f max(Pt4f u, Pt4f v) {
        u[0] = std::max(u[0], v[0]);
        u[1] = std::max(u[1], v[1]);
        u[2] = std::max(u[2], v[2]);
        u[3] = std::max(u[3], v[3]);
        return u;
    }

    AVML_FINL Pt4f min(Pt4f u, Pt4f v) {
        u[0] = std::min(u[0], v[0]);
        u[1] = std::min(u[1], v[1]);
        u[2] = std::min(u[2], v[2]);
        u[3] = std::min(u[3], v[3]);
        return u;
    }

}
