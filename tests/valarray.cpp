#include "gtest/gtest.h"
#include "valarray.hpp"

using namespace isl;

TEST(ValarrayTest, Slice) {
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
