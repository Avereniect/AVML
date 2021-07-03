namespace avml {

    template<>
    class  alignas(sizeof(float) * 2) Point<float, 2> {
    public:

        using scalar = float;

        static constexpr unsigned width = 2;

        //=================================================
        // Creation functions
        //=================================================

        static Point read(float* p) {
            return Point{p[0], p[1]};
        }

        static Point read_aligned(float* p) {
            return Point{p[0], p[1]};
        }

        //=================================================
        // -ctors
        //=================================================

        AVML_FINL Point(float x, float y) :
            elements{x, y} {}

        explicit AVML_FINL Point(Vec2f v) :
            elements{v[0], v[1]} {}

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

        AVML_FINL Point& operator+=(Vec2f rhs) {
            elements[0] += rhs[0];
            elements[1] += rhs[1];
            return *this;
        }

        AVML_FINL Point& operator-=(Vec2f rhs) {
            elements[0] -= rhs[0];
            elements[1] -= rhs[1];
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

        AVML_FINL explicit operator Vec2f() const {
            return Vec2f{
                elements[0],
                elements[1]
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

    AVML_FINL bool operator==(Pt2f lhs, Pt2f rhs) {
        return
            lhs[0] == rhs[0] &&
            lhs[1] == rhs[1];
    }

    AVML_FINL bool operator!=(Pt2f lhs, Pt2f rhs) {
        return
            lhs[0] != rhs[0] &&
            lhs[1] != rhs[1];
    }

    //=====================================================
    // Arithmetic operators
    //=====================================================

    AVML_FINL Pt2f operator+(Pt2f lhs, Vec2f rhs) {
        lhs += rhs;
        return lhs;
    }

    AVML_FINL Pt2f operator+(Vec2f lhs, Pt2f rhs) {
        rhs += lhs;
        return rhs;
    }

    AVML_FINL Pt2f operator-(Pt2f lhs, Vec2f rhs) {
        lhs -= rhs;
        return lhs;
    }

    AVML_FINL Vec2f operator-(Pt2f lhs, Pt2f rhs) {
        return Vec2f {
          lhs[0] - rhs[0],
          lhs[1] - rhs[1]
        };
    }

    //=====================================================
    // Vectorized math
    //=====================================================

    AVML_FINL Pt2f abs(Pt2f v) {
        v[0] = std::abs(v[0]);
        v[1] = std::abs(v[1]);
        return v;
    }

    AVML_FINL Pt2f max(Pt2f u, Pt2f v) {
        u[0] = std::max(u[0], v[0]);
        u[1] = std::max(u[1], v[1]);
        return u;
    }

    AVML_FINL Pt2f min(Pt2f u, Pt2f v) {
        u[0] = std::min(u[0], v[0]);
        u[1] = std::min(u[1], v[1]);
        return u;
    }

}
