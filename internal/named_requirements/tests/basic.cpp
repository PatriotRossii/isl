#include <gtest/gtest.h>
#include "../basic.hpp"

namespace DefaultConstructible {
    template<typename T>
    bool accept_default_constructible() requires(
        isl::internal::DefaultConstructible<T>
    ) {
        return true;
    }
    template<typename T>
    bool accept_default_constructible() {
        return false;
    }

    struct C {
        C() = delete;
    };
}

TEST(basic, TestDefaultConstructible) {
    using namespace DefaultConstructible;

    ASSERT_EQ(
        accept_default_constructible<int>(), true
    );
    ASSERT_EQ(
        accept_default_constructible<C>(), false
    );
}


int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
