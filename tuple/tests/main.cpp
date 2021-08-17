#include <gtest/gtest.h>
#include <string>

#include "../tuple.hpp"

TEST(utility, TestTupleDefaultConstructor) {
    isl::tuple<int, double, std::string> pair;

    ASSERT_EQ(
        isl::get<2>(pair), std::string()
    );
    ASSERT_EQ(
        isl::get<1>(pair), 0.0
    );
    ASSERT_EQ(
        isl::get<0>(pair), 0
    );
}

TEST(utility, TestTupleArgumentConstruction) {
    isl::tuple<int, double, std::string> pair{
        5, 2.0, "Hello"
    };

    ASSERT_EQ(
        isl::get<0>(pair), 5
    );
    ASSERT_EQ(
        isl::get<1>(pair), 2.0
    );
    ASSERT_EQ(
        isl::get<2>(pair), "Hello"
    );
}

int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
