#include <gtest/gtest.h>

#include <vector>

#include "utils/registerAccess.h"

class RegisterAccessTest : public ::testing::Test
{
protected:
  using RegisterTypeHost = std::uint64_t;

  void SetUp() override
  {
    // 1167592324
    // 1000101100110000000101110000100
    const auto valueOfDummyregister = 0x45980B84;
    dummyRegister = valueOfDummyregister;
    addressOfDummyRegister =
      reinterpret_cast<RegisterTypeHost>(&dummyRegister); // NOLINT: Ignored reinterpret_cast by clang-tidy.
  }

  RegisterTypeHost dummyRegister{ 0 };
  RegisterTypeHost addressOfDummyRegister{ 0 };
};

TEST_F(RegisterAccessTest, regSet) // NOLINT: Static storage warning.
{
  const auto setValue = 0x52;
  RegisterAccess<RegisterTypeHost, RegisterTypeHost>::regSet(addressOfDummyRegister, setValue);
  EXPECT_EQ(dummyRegister, setValue);
}

TEST_F(RegisterAccessTest, regAnd) // NOLINT: Static storage warning.
{
  const auto otherValue = 56482564;
  const auto expectedValue = 18352900; // 1167592324 & 56482564
  RegisterAccess<RegisterTypeHost, RegisterTypeHost>::regAnd(addressOfDummyRegister, otherValue);

  EXPECT_EQ(dummyRegister, expectedValue);
}

TEST_F(RegisterAccessTest, regOr) // NOLINT: Static storage warning.
{
  const auto otherValue = 56482564;
  const auto expectedValue = 1205721988; // 1167592324 | 56482564
  RegisterAccess<RegisterTypeHost, RegisterTypeHost>::regOr(addressOfDummyRegister, otherValue);

  EXPECT_EQ(dummyRegister, expectedValue);
}

TEST_F(RegisterAccessTest, regGet) // NOLINT: Static storage warning.
{
  const auto actualValue = RegisterAccess<RegisterTypeHost, RegisterTypeHost>::regGet(addressOfDummyRegister);
  EXPECT_EQ(actualValue, dummyRegister);
}

TEST_F(RegisterAccessTest, regBitSet) // NOLINT: Static storage warning.
{
  const auto bitsToSet = std::vector<RegisterTypeHost>{ 0, 1, 5, 7, 27 };
  RegisterAccess<RegisterTypeHost, RegisterTypeHost>::regBitSet(addressOfDummyRegister, bitsToSet.at(0));
  RegisterAccess<RegisterTypeHost, RegisterTypeHost>::regBitSet(addressOfDummyRegister, bitsToSet.at(1));
  RegisterAccess<RegisterTypeHost, RegisterTypeHost>::regBitSet(addressOfDummyRegister, bitsToSet.at(2));
  RegisterAccess<RegisterTypeHost, RegisterTypeHost>::regBitSet(addressOfDummyRegister, bitsToSet.at(3));
  RegisterAccess<RegisterTypeHost, RegisterTypeHost>::regBitSet(addressOfDummyRegister, bitsToSet.at(4));
  const auto expectedValue = 0b1001101100110000000101110100111;

  EXPECT_EQ(dummyRegister, expectedValue);
}

TEST_F(RegisterAccessTest, regBitClear) // NOLINT: Static storage warning.
{
  const auto bitsToClear = std::vector<RegisterTypeHost>{ 0, 2, 7, 9, 26 };
  RegisterAccess<RegisterTypeHost, RegisterTypeHost>::regBitClear(addressOfDummyRegister, bitsToClear.at(0));
  RegisterAccess<RegisterTypeHost, RegisterTypeHost>::regBitClear(addressOfDummyRegister, bitsToClear.at(1));
  RegisterAccess<RegisterTypeHost, RegisterTypeHost>::regBitClear(addressOfDummyRegister, bitsToClear.at(2));
  RegisterAccess<RegisterTypeHost, RegisterTypeHost>::regBitClear(addressOfDummyRegister, bitsToClear.at(3));
  RegisterAccess<RegisterTypeHost, RegisterTypeHost>::regBitClear(addressOfDummyRegister, bitsToClear.at(4));
  const auto expectedValue = 0b1000001100110000000100100000000;

  EXPECT_EQ(dummyRegister, expectedValue);
}


TEST_F(RegisterAccessTest, regBitToggle) // NOLINT: Static storage warning.
{
  const auto bitsToToggle = std::vector<RegisterTypeHost>{ 0, 2, 7, 9, 26 };
  RegisterAccess<RegisterTypeHost, RegisterTypeHost>::regBitToggle(addressOfDummyRegister, bitsToToggle.at(0));
  RegisterAccess<RegisterTypeHost, RegisterTypeHost>::regBitToggle(addressOfDummyRegister, bitsToToggle.at(1));
  RegisterAccess<RegisterTypeHost, RegisterTypeHost>::regBitToggle(addressOfDummyRegister, bitsToToggle.at(2));
  RegisterAccess<RegisterTypeHost, RegisterTypeHost>::regBitToggle(addressOfDummyRegister, bitsToToggle.at(3));
  RegisterAccess<RegisterTypeHost, RegisterTypeHost>::regBitToggle(addressOfDummyRegister, bitsToToggle.at(4));
  const auto expectedValue = 0b1000001100110000000100100000001;

  EXPECT_EQ(dummyRegister, expectedValue);
}

TEST_F(RegisterAccessTest, regBitGet) // NOLINT: Static storage warning.
{
  const auto bitsToGet = std::vector<RegisterTypeHost>{ 0, 2, 24 };

  const auto zerothBit =
    RegisterAccess<RegisterTypeHost, RegisterTypeHost>::regBitGet(addressOfDummyRegister, bitsToGet.at(0));
  EXPECT_FALSE(zerothBit);

  const auto secondBit =
    RegisterAccess<RegisterTypeHost, RegisterTypeHost>::regBitGet(addressOfDummyRegister, bitsToGet.at(1));
  EXPECT_TRUE(secondBit);

  const auto twentyForthBit =
    RegisterAccess<RegisterTypeHost, RegisterTypeHost>::regBitGet(addressOfDummyRegister, bitsToGet.at(2));
  EXPECT_TRUE(twentyForthBit);
}

int main(int argc, char **argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
