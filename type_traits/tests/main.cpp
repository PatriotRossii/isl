#include <gtest/gtest.h>
#include <type_traits> // std::is_same

#include "../type_traits.h" // isl::integral_constant

TEST(type_traits, TestIntegralConstant) {
    using two_t = isl::integral_constant<int, 2>;
    using four_t = isl::integral_constant<int, 4>;

    ASSERT_EQ(
        two_t::value * 2,
        4
    ) << "2 * 2 != 4";

    enum class my_e { e1, e2 };

    using my_e_e1 = isl::integral_constant<my_e, my_e::e1>;
    using my_e_e2 = isl::integral_constant<my_e, my_e::e2>;

    ASSERT_EQ(my_e_e1(), my_e::e1);
    ASSERT_EQ(my_e_e2(), my_e::e2);

    using same = std::is_same<my_e_e2, my_e_e2>;
    ASSERT_TRUE(same::value)
        << "my_e_e2 != my_e_e2";
}

int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
