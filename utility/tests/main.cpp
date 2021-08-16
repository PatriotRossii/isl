#include <gtest/gtest.h>

#include "../utility.hpp" // isl::integral_constant

TEST(utility, TestSwap) {
    int a = 5, b = 3;

    ASSERT_EQ(a, 5);
    ASSERT_EQ(b, 3);

    isl::swap(a, b);

    ASSERT_EQ(a, 3);
    ASSERT_EQ(b, 5);
}

int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
