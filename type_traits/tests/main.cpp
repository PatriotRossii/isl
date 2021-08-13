#include <gtest/gtest.h>
#include <type_traits> // std::is_same

#include "../type_traits.hpp" // isl::integral_constant

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

TEST(type_traits, TestRemoveCV) {
    using type1 = isl::remove_cv<const int>::type;
    using type2 = isl::remove_cv<volatile int>::type;
    using type3 = isl::remove_cv<const volatile int>::type;
    using type4 = isl::remove_cv<const volatile int*>::type;
    using type5 = isl::remove_cv<int * const volatile>::type;

    constexpr bool same1 = std::is_same_v<int, type1>;
    constexpr bool same2 = std::is_same_v<int, type2>;
    constexpr bool same3 = std::is_same_v<int, type3>;
    constexpr bool same4 = std::is_same_v<const volatile int*, type4>;
    constexpr bool same5 = std::is_same_v<int*, type5>;

    ASSERT_TRUE(same1);
    ASSERT_TRUE(same2);
    ASSERT_TRUE(same3);
    ASSERT_TRUE(same4);
    ASSERT_TRUE(same5);
}

TEST(type_traits, TestAddCV) {
    using type1 = isl::add_cv<int>::type;
    using type2 = isl::add_const<int>::type;
    using type3 = isl::add_volatile<int>::type;

    constexpr bool same1 = std::is_same_v<const volatile int, type1>;
    constexpr bool same2 = std::is_same_v<const int, type2>;
    constexpr bool same3 = std::is_same_v<volatile int, type3>;

    ASSERT_TRUE(same1);
    ASSERT_TRUE(same2);
    ASSERT_TRUE(same3); 
}

int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
