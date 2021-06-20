namespace avml {

    template<>
    class Point<float, 3> {
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

        AVML_FINL explicit Point(Vec3f v):
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

        Point& operator+=(Vec3f rhs) {
            elements[0] += rhs[0];
            elements[1] += rhs[1];
            elements[2] += rhs[2];
            return *this;
        }

        Point& operator-=(Vec3f rhs) {
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

}
