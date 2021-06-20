namespace avml {

    template<>
    class Point<float, 4> {
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

        Point(float x, float y, float z, float w):
            elements{x, y, z, w} {}

        explicit Point(Vec4f v):
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

        Point& operator+=(Vec4f rhs) {
            elements[0] += rhs[0];
            elements[1] += rhs[1];
            elements[2] += rhs[2];
            elements[3] += rhs[3];
            return *this;
        }

        Point& operator-=(Vec4f rhs) {
            elements[0] -= rhs[0];
            elements[1] -= rhs[1];
            elements[2] -= rhs[2];
            elements[3] -= rhs[3];
            return *this;
        }

        //=================================================
        // Accessors
        //=================================================

        float& operator[](unsigned i) {
            return  elements[i];
        }

        const float& operator[](unsigned i) const {
            return elements[i];
        }

        float* data() {
            return elements;
        }

        const float* data() const {
            return elements;
        }

        //=================================================
        // Conversion operators
        //=================================================

        explicit operator Vec4f() const {
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

}
