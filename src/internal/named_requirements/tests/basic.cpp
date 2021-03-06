#include "../basic.hpp"
#include <gtest/gtest.h>

namespace DefaultConstructibleTest {
struct C {
  C() = delete;
};
} // namespace DefaultConstructibleTest

TEST(basic, TestDefaultConstructible) {
  using namespace isl::internal;
  using namespace DefaultConstructibleTest;

  ASSERT_EQ(DefaultConstructible<int>, true);
  ASSERT_EQ(DefaultConstructible<C>, false);
}

int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
