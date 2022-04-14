#include "gtest/gtest.h"
#include "ratio.hpp"
#include <iostream>

using namespace isl;

TEST(RatioTest, Comparison) {
    EXPECT_EQ((ratio_equal<ratio<2, 3>, ratio<4, 6>>::value), true);

    EXPECT_EQ((ratio_not_equal<ratio<2,3>, ratio<1,3>>::value), true);

    EXPECT_EQ((ratio_less<ratio<23,37>, ratio<57,90>>::value), true);

    EXPECT_EQ((ratio_less_equal<ratio<1, 2>, ratio<3, 4>>::value), true);
    EXPECT_EQ((ratio_less_equal<ratio<10,11>, ratio<11,12>>::value), true);

    EXPECT_EQ((ratio_greater<ratio<3, 4>, ratio<1, 2>>::value), true);
    EXPECT_EQ((ratio_greater<ratio<11, 12>, ratio<10, 11>>::value), true);

    EXPECT_EQ((ratio_greater_equal<ratio<2, 3>, ratio<2, 3>>::value), true);
    EXPECT_EQ((ratio_greater_equal<ratio<2,1>, ratio<1, 2>>::value), true);
    EXPECT_EQ((ratio_greater_equal<ratio<1,2>, ratio<1, 2>>::value), true);
}

TEST(RatioTest, Arithmetic) {
    using two_third = ratio<2, 3>;
    using one_sixth = ratio<1, 6>;

    using sum = ratio_add<two_third, one_sixth>;
    EXPECT_TRUE(sum::num == 5 && sum::den == 6);

    using diff = ratio_subtract<two_third, one_sixth>;
    EXPECT_TRUE(diff::num == 1 && diff::den == 2);

    using product = ratio_multiply<two_third, one_sixth>;
    EXPECT_TRUE(product::num == 1 && product::den == 9);

    using quotient = ratio_divide<two_third, one_sixth>;
    EXPECT_TRUE(quotient::num == 4 && quotient::den == 1);
}