
#include <gtest/gtest.h>

#include "targetSpecific/drivers/rccRegisters.h"

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

  RegisterTypeHost registerSetBaseAddressValue{ 0 };
  static constexpr auto numberOfRCCRegisters{ 36 };
  std::array<RegisterType, numberOfRCCRegisters> rccRegisterSet{};
};

TEST_F(RCCRegisterTest, enableGPIOAClock) // NOLINT: Static storage warning.
{
  RCCRegisters<RegisterTypeHost>::enablePeripheralClock<Peripheral::GPIOA>(registerSetBaseAddressValue);

  const auto numberOfShifts = UINT32_C(0);
  const auto expectedValue = UINT32_C(0b1) << numberOfShifts;
  EXPECT_EQ(getValueOfAHB1EnrRegister(), expectedValue);
}

TEST_F(RCCRegisterTest, enableGPIOHClock) // NOLINT: Static storage warning.
{
  RCCRegisters<RegisterTypeHost>::enablePeripheralClock<Peripheral::GPIOH>(registerSetBaseAddressValue);

  const auto numberOfShifts = UINT32_C(7);
  const auto expectedValue = UINT32_C(0b1) << numberOfShifts;
  EXPECT_EQ(getValueOfAHB1EnrRegister(), expectedValue);
}
