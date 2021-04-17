#include "Matrix_tests.hpp"

using namespace avml;

int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();

    /*
    Vec2 v2{1.0f, 2.0f};
    Vec3 v3{1.0f, 2.0f, 3.0f};
    Vec4 v4{1.0f, 2.0f, 3.0f, 4.0f};

    Uvec2 uv2{1.0f, 0.0f};
    Uvec3 uv3{1.0f, 0.0f, 0.0f};
    Uvec4 uv4{1.0f, 0.0f, 0.0f, 0.0f};

    Pt2 p2{1.0f, 2.0f};
    Pt3 p3{1.0f, 2.0f, 3.0f};
    Pt4 p4{1.0f, 2.0f, 3.0f, 4.0f};

    Pt2 x00 = p2 + v2;
    Pt3 x10 = p3 + v3;
    Pt4 x20 = p4 + v4;

    Pt2 x01 = p2 + (v2 + uv2) * 2.0f;
    Pt3 x11 = p3 + (v3 + uv3) * 3.0f;
    Pt4 x21 = p4 + (v4 + uv4) * 4.0f;

    Vec2 y0 = p2 - x01;
    Vec3 y1 = p3 - x11;
    Vec4 y2 = p4 - x21;

    Arr2 arr0{1.0f, 2.0f};
    Arr3 arr1{1.0f, 2.0f, 3.0f};
    Arr4 arr2{1.0f, 2.0f, 3.0f, 4.0f};

    arr0 = static_cast<Arr2>(v2);
    arr1 = static_cast<Arr3>(v3);
    arr2 = static_cast<Arr4>(v4);

    arr0 = static_cast<Arr2>(uv2);
    arr1 = static_cast<Arr3>(uv3);
    arr2 = static_cast<Arr4>(uv4);

    arr0 = static_cast<Arr2>(p2);
    arr1 = static_cast<Arr3>(p3);
    arr2 = static_cast<Arr4>(p4);

    Mat2x2 mat2{
        {1.0f, 0.0},
        {0.0f, 1.0f}
    };

    Mat3x3 mat3{
        {1.0f, 0.0f, 0.0f},
        {0.0f, 1.0f, 0.0f},
        {0.0f, 0.0f, 1.0f}
    };

    Mat4x4 mat4{
        {1.0f, 0.0f, 0.0f, 0.0f},
        {0.0f, 1.0f, 0.0f, 0.0f},
        {0.0f, 0.0f, 1.0f, 0.0f},
        {0.0f, 0.0f, 0.0f, 1.0f}
    };
    */
}
