#include <gtest/gtest.h>

#include "sum.h"

TEST(SumTest, PositiveNos)
{
  ASSERT_EQ(3, sum(1, 2));
}

int main(int argc, char **argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
