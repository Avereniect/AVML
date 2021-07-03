#ifndef AVML_VECTOR_TESTS_HPP
#define AVML_VECTOR_TESTS_HPP

#include <avml/AVML.hpp>

namespace avml_test {

    using namespace avml;

    TEST(Vec2f, Constructors) {
        Vec2f v0{};
        EXPECT_EQ(v0[0], 0.0f);
        EXPECT_EQ(v0[1], 0.0f);

        Vec2f v1{1.0f, 2.0f};
        EXPECT_EQ(v1[0], 1.0f);
        EXPECT_EQ(v1[1], 2.0f);
    }

    TEST(Vec3f, Constructors) {
        Vec3f v0{};
        EXPECT_EQ(v0[0], 0.0f);
        EXPECT_EQ(v0[1], 0.0f);
        EXPECT_EQ(v0[2], 0.0f);

        Vec3f v1{1.0f, 2.0f, 3.0f};
        EXPECT_EQ(v1[0], 1.0f);
        EXPECT_EQ(v1[1], 2.0f);
        EXPECT_EQ(v1[2], 3.0f);

        Vec2f t{1.0f, 2.0f};
        Vec3f v2{t, 3.0f};
        EXPECT_EQ(v2[0], 1.0f);
        EXPECT_EQ(v2[1], 2.0f);
        EXPECT_EQ(v2[2], 3.0f);

        Vec3f v3{0.0, t};
        EXPECT_EQ(v3[0], 0.0f);
        EXPECT_EQ(v3[1], 1.0f);
        EXPECT_EQ(v3[2], 2.0f);
    }

    TEST(Vec4, Constructors) {
        Vec4f v0{};
        EXPECT_EQ(v0[0], 0.0f);
        EXPECT_EQ(v0[0], 0.0f);
        EXPECT_EQ(v0[0], 0.0f);

        Vec4f v1{1.0f, 2.0f, 3.0f, 4.0f};
        EXPECT_EQ(v1[0], 1.0f);
        EXPECT_EQ(v1[1], 2.0f);
        EXPECT_EQ(v1[2], 3.0f);
        EXPECT_EQ(v1[3], 4.0f);

        Vec2f t0{1.0f, 2.0f};

        Vec4f v2{t0, t0};
        EXPECT_EQ(v2[0], 1.0f);
        EXPECT_EQ(v2[1], 2.0f);
        EXPECT_EQ(v2[2], 1.0f);
        EXPECT_EQ(v2[3], 2.0f);

        Vec4f v3{t0, 3.0, 4.0f};
        EXPECT_EQ(v3[0], 1.0f);
        EXPECT_EQ(v3[1], 2.0f);
        EXPECT_EQ(v3[2], 3.0f);
        EXPECT_EQ(v3[3], 4.0f);

        Vec4f v4{-1.0, 0.0f, t0};
        EXPECT_EQ(v4[0], -1.0f);
        EXPECT_EQ(v4[1], 0.0f);
        EXPECT_EQ(v4[2], 1.0f);
        EXPECT_EQ(v4[3], 2.0f);

        Vec4f v5(0.0f, t0, 3.0f);
        EXPECT_EQ(v5[0], 0.0f);
        EXPECT_EQ(v5[1], 1.0f);
        EXPECT_EQ(v5[2], 2.0f);
        EXPECT_EQ(v5[3], 3.0f);

        Vec3f t1{1.0f, 2.0f, 3.0f};
        Vec4f v6{t1, 4.0f};
        EXPECT_EQ(v6[0], 1.0f);
        EXPECT_EQ(v6[1], 2.0f);
        EXPECT_EQ(v6[2], 3.0f);
        EXPECT_EQ(v6[3], 4.0f);

        Vec4f v7{0.0f, t1};
        EXPECT_EQ(v7[0], 0.0f);
        EXPECT_EQ(v7[1], 1.0f);
        EXPECT_EQ(v7[2], 2.0f);
        EXPECT_EQ(v7[3], 3.0f);
    }

    TEST(Vec2, Addition_assignment_operators) {
        Vec2f x{1.0f, 2.0f};
        x += Vec2f{2.0f, 4.0f};

        EXPECT_EQ(x[0], 3.0);
        EXPECT_EQ(x[1], 6.0f);
    }

    TEST(Vec2, Addition_operator) {
        Vec2f x{1.0f, 2.0f};
        Vec2f y{2.0f, 4.0f};

        auto z = x + y;
        EXPECT_EQ(z[0], 3.0f);
        EXPECT_EQ(z[1], 6.0f);
    }

    TEST(Vec2, Subtraction_assignment_operators) {
        Vec2f x{1.0f, 2.0f};
        x -= Vec2f{2.0f, 4.0f};

        EXPECT_EQ(x[0], -1.0);
        EXPECT_EQ(x[1], -2.0f);
    }

    TEST(Vec2, Subtraction_operator) {
        Vec2f x{1.0f, 2.0f};
        Vec2f y{2.0f, 4.0f};

        Vec2f z = x - y;
        EXPECT_EQ(z[0], -1.0f);
        EXPECT_EQ(z[1], -2.0f);
    }

}

#endif //AVML_VECTOR_TESTS_HPP
