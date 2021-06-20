namespace avml {

    template<>
    class Point<float, 2> {
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

        Point(float x, float y) :
            elements{x, y} {}

        explicit Point(Vec2f v) :
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

        Point& operator+=(Vec2f rhs) {
            elements[0] += rhs[0];
            elements[1] += rhs[1];
            return *this;
        }

        Point& operator-=(Vec2f rhs) {
            elements[0] -= rhs[0];
            elements[1] -= rhs[1];
            return *this;
        }

        //=================================================
        // Accessors
        //=================================================

        float& operator[](unsigned i) {
            return elements[i];
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

        explicit operator Vec2f() const {
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

}
