namespace avml {

    template<>
    class alignas(sizeof(float) * 1) Point<float, 3> {
    public:

        using scalar = float;

        static constexpr unsigned width = 3;

        //=================================================
        // Creation functions
        //=================================================

        AVML_FINL static Point read(float* p) {
            return Point{p[0], p[1], p[2]};
        }

        AVML_FINL static Point read_aligned(float* p) {
            return Point{p[0], p[1], p[2]};
        }

        //=================================================
        // -ctors
        //=================================================

        AVML_FINL Point(float x, float y, float z):
            elements{x, y, z} {}

        AVML_FINL Point(Pt2f v, float z):
            elements{v[0], v[1], z} {}

        AVML_FINL Point(float x, Pt2f v):
            elements{x, v[0], v[1]} {}

        explicit AVML_FINL Point(Vec3f v):
            elements{v[0], v[1], v[2]} {}

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

        AVML_FINL Point& operator+=(Vec3f rhs) {
            elements[0] += rhs[0];
            elements[1] += rhs[1];
            elements[2] += rhs[2];
            return *this;
        }

        AVML_FINL Point& operator-=(Vec3f rhs) {
            elements[0] -= rhs[0];
            elements[1] -= rhs[1];
            elements[2] -= rhs[2];
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

        AVML_FINL explicit operator Vec3f() const {
            return Vec3f{
                elements[0],
                elements[1],
                elements[2]
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

    AVML_FINL bool operator==(Pt3f lhs, Pt3f rhs) {
        return
            lhs[0] == rhs[0] &&
            lhs[1] == rhs[1] &&
            lhs[2] == rhs[2];
    }

    AVML_FINL bool operator!=(Pt3f lhs, Pt3f rhs) {
        return
            lhs[0] != rhs[0] &&
            lhs[1] != rhs[1] &&
            lhs[2] != rhs[2];
    }

    //=====================================================
    // Arithmetic operators
    //=====================================================

    AVML_FINL Pt3f operator+(Pt3f lhs, Vec3f rhs) {
        lhs += rhs;
        return lhs;
    }

    AVML_FINL Pt3f operator+(Vec3f lhs, Pt3f rhs) {
        rhs += lhs;
        return rhs;
    }

    AVML_FINL Pt3f operator-(Pt3f lhs, Vec3f rhs) {
        lhs -= rhs;
        return lhs;
    }

    AVML_FINL Vec3f operator-(Pt3f lhs, Pt3f rhs) {
        return Vec3f {
          lhs[0] - rhs[0],
          lhs[1] - rhs[1],
          lhs[2] - rhs[2]
        };
    }

    //=====================================================
    // Vectorized math
    //=====================================================

    AVML_FINL Pt3f abs(Pt3f v) {
        v[0] = std::abs(v[0]);
        v[1] = std::abs(v[1]);
        v[2] = std::abs(v[2]);
        return v;
    }

    AVML_FINL Pt3f max(Pt3f u, Pt3f v) {
        u[0] = std::max(u[0], v[0]);
        u[1] = std::max(u[1], v[1]);
        u[2] = std::max(u[2], v[2]);
        return u;
    }

    AVML_FINL Pt3f min(Pt3f u, Pt3f v) {
        u[0] = std::min(u[0], v[0]);
        u[1] = std::min(u[1], v[1]);
        u[2] = std::min(u[2], v[2]);
        return u;
    }

}
