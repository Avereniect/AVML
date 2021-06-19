#include <gtest/gtest.h>

#include "Unit_vector_tests.hpp"
#include "Vector_tests.hpp"
#include "Matrix_tests.hpp"

int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
