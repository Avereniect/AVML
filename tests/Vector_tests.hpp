#ifndef AVML_VECTOR_TESTS_HPP
#define AVML_VECTOR_TESTS_HPP

#include <avml/AVML.hpp>

namespace avml_test {

    using namespace avml;

    TEST(Vec2, Constructors) {
        Vec2 v0{};
        EXPECT_EQ(v0[0], 0.0f);
        EXPECT_EQ(v0[1], 0.0f);

        Vec2 v1{1.0f, 2.0f};
        EXPECT_EQ(v1[0], 1.0f);
        EXPECT_EQ(v1[1], 2.0f);
    }

    TEST(Vec3, Constructors) {
        Vec3 v0{};
        EXPECT_EQ(v0[0], 0.0f);
        EXPECT_EQ(v0[1], 0.0f);
        EXPECT_EQ(v0[2], 0.0f);

        Vec3 v1{1.0f, 2.0f, 3.0f};
        EXPECT_EQ(v1[0], 1.0f);
        EXPECT_EQ(v1[1], 2.0f);
        EXPECT_EQ(v1[2], 3.0f);

        Vec2 t{1.0f, 2.0f};
        Vec3 v2{t, 3.0f};
        EXPECT_EQ(v2[0], 1.0f);
        EXPECT_EQ(v2[1], 2.0f);
        EXPECT_EQ(v2[2], 3.0f);

        Vec3 v3{0.0, t};
        EXPECT_EQ(v3[0], 0.0f);
        EXPECT_EQ(v3[1], 1.0f);
        EXPECT_EQ(v3[2], 2.0f);
    }

    TEST(Vec4, Constructors) {
        Vec4 v0{};
        EXPECT_EQ(v0[0], 0.0f);
        EXPECT_EQ(v0[0], 0.0f);
        EXPECT_EQ(v0[0], 0.0f);

        Vec4 v1{1.0f, 2.0f, 3.0f, 4.0f};
        EXPECT_EQ(v1[0], 1.0f);
        EXPECT_EQ(v1[1], 2.0f);
        EXPECT_EQ(v1[2], 3.0f);
        EXPECT_EQ(v1[3], 4.0f);

        Vec2 t0{1.0f, 2.0f};

        Vec4 v2{t0, t0};
        EXPECT_EQ(v2[0], 1.0f);
        EXPECT_EQ(v2[1], 2.0f);
        EXPECT_EQ(v2[2], 1.0f);
        EXPECT_EQ(v2[3], 2.0f);

        Vec4 v3{t0, 3.0, 4.0f};
        EXPECT_EQ(v3[0], 1.0f);
        EXPECT_EQ(v3[1], 2.0f);
        EXPECT_EQ(v3[2], 3.0f);
        EXPECT_EQ(v3[3], 4.0f);

        Vec4 v4{-1.0, 0.0f, t0};
        EXPECT_EQ(v4[0], -1.0f);
        EXPECT_EQ(v4[1], 0.0f);
        EXPECT_EQ(v4[2], 1.0f);
        EXPECT_EQ(v4[3], 2.0f);

        Vec4 v5(0.0f, t0, 3.0f);
        EXPECT_EQ(v5[0], 0.0f);
        EXPECT_EQ(v5[1], 1.0f);
        EXPECT_EQ(v5[2], 2.0f);
        EXPECT_EQ(v5[3], 3.0f);

        Vec3 t1{1.0f, 2.0f, 3.0f};
        Vec4 v6{t1, 4.0f};
        EXPECT_EQ(v6[0], 1.0f);
        EXPECT_EQ(v6[1], 2.0f);
        EXPECT_EQ(v6[2], 3.0f);
        EXPECT_EQ(v6[3], 4.0f);

        Vec4 v7{0.0f, t1};
        EXPECT_EQ(v7[0], 0.0f);
        EXPECT_EQ(v7[1], 1.0f);
        EXPECT_EQ(v7[2], 2.0f);
        EXPECT_EQ(v7[3], 3.0f);
    }

    TEST(Vec2, Addition_assignment_operators) {
        Vec2 x{1.0f, 2.0f};
        x += Vec2{2.0f, 4.0f};

        EXPECT_EQ(x[0], 3.0);
        EXPECT_EQ(x[1], 6.0f);
    }

    TEST(Vec2, Addition_operator) {
        Vec2 x{1.0f, 2.0f};
        Vec2 y{2.0f, 4.0f};

        auto z = x + y;
        EXPECT_EQ(z[0], 3.0f);
        EXPECT_EQ(z[1], 6.0f);
    }

    TEST(Vec2, Subtraction_assignment_operators) {
        Vec2 x{1.0f, 2.0f};
        x -= Vec2{2.0f, 4.0f};

        EXPECT_EQ(x[0], -1.0);
        EXPECT_EQ(x[1], -2.0f);
    }

    TEST(Vec2, Subtraction_operator) {
        Vec2 x{1.0f, 2.0f};
        Vec2 y{2.0f, 4.0f};

        Vec2 z = x - y;
        EXPECT_EQ(z[0], -1.0f);
        EXPECT_EQ(z[1], -2.0f);
    }

}

#endif //AVML_VECTOR_TESTS_HPP
