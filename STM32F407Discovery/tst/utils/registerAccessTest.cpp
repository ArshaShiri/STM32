#include <gtest/gtest.h>

int sum(const int a, const int b) { return a + b; }

TEST(SumTest, PositiveNos) { ASSERT_EQ(3, sum(1, 2)); }

int main(int argc, char **argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
