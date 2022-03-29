
#include <gtest/gtest.h>

#include "targetSpecific/rccRegisters.h"

class RCCRegisterTest : public ::testing::Test
{
protected:
  using RegisterTypeHost = std::uint64_t;

  void SetUp() override
  {
    std::for_each(rccRegisterSet.begin(), rccRegisterSet.end(), [](RegisterType &el) { el = 0; });
    registerSetBaseAddressValue =
      reinterpret_cast<RegisterTypeHost>(rccRegisterSet.data()); // NOLINT: Ignored reinterpret_cast by clang-tidy.
  }

  [[nodiscard]] RegisterType getValueOfAHB1EnrRegister() const { return rccRegisterSet.at(12); }
  [[nodiscard]] RegisterType getValueOfAPB1EnrRegister() const { return rccRegisterSet.at(16); }

  RegisterTypeHost registerSetBaseAddressValue{ 0 };
  static constexpr auto numberOfRCCRegisters{ 36 };
  std::array<RegisterType, numberOfRCCRegisters> rccRegisterSet{};
};

TEST_F(RCCRegisterTest, enableDisableGPIOAClock) // NOLINT: Static storage warning.
{
  RCCRegisters<RegisterTypeHost>::peripheralClockSet<Peripheral::GPIOA, true>(registerSetBaseAddressValue);

  const auto numberOfShifts = UINT32_C(0);
  auto expectedValue = UINT32_C(0b1) << numberOfShifts;
  EXPECT_EQ(getValueOfAHB1EnrRegister(), expectedValue);

  RCCRegisters<RegisterTypeHost>::peripheralClockSet<Peripheral::GPIOA, false>(registerSetBaseAddressValue);
  expectedValue = 0;
  EXPECT_EQ(getValueOfAHB1EnrRegister(), expectedValue);
}

TEST_F(RCCRegisterTest, enableDisableGPIOHClock) // NOLINT: Static storage warning.
{
  RCCRegisters<RegisterTypeHost>::peripheralClockSet<Peripheral::GPIOH, true>(registerSetBaseAddressValue);

  const auto numberOfShifts = UINT32_C(7);
  auto expectedValue = UINT32_C(0b1) << numberOfShifts;
  EXPECT_EQ(getValueOfAHB1EnrRegister(), expectedValue);

  RCCRegisters<RegisterTypeHost>::peripheralClockSet<Peripheral::GPIOH, false>(registerSetBaseAddressValue);
  expectedValue = 0;
  EXPECT_EQ(getValueOfAHB1EnrRegister(), expectedValue);
}

TEST_F(RCCRegisterTest, enableDisableI2C3Clock) // NOLINT: Static storage warning.
{
  RCCRegisters<RegisterTypeHost>::peripheralClockSet<Peripheral::I2C3, true>(registerSetBaseAddressValue);

  const auto numberOfShifts = UINT32_C(23);
  auto expectedValue = UINT32_C(0b1) << numberOfShifts;
  EXPECT_EQ(getValueOfAPB1EnrRegister(), expectedValue);

  RCCRegisters<RegisterTypeHost>::peripheralClockSet<Peripheral::I2C3, false>(registerSetBaseAddressValue);
  expectedValue = 0;
  EXPECT_EQ(getValueOfAHB1EnrRegister(), expectedValue);
}
