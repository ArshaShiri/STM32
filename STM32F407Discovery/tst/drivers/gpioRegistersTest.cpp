#include <algorithm>
#include <array>

#include <gtest/gtest.h>

#include "targetSpecific/drivers/gpioRegisters.h"
#include "targetSpecific/registerType.h"

class GPIORegisterTest : public ::testing::Test
{
protected:
  using RegisterTypeHost = std::uint64_t;

  void SetUp() override
  {
    std::for_each(gpioRegisterSet.begin(), gpioRegisterSet.end(), [](RegisterType &el) { el = 0; });
    registerSetBaseAddressValue =
      reinterpret_cast<RegisterTypeHost>(gpioRegisterSet.data()); // NOLINT: Ignored reinterpret_cast by clang-tidy.
  }

  RegisterTypeHost registerSetBaseAddressValue{ 0 };
  static constexpr auto numberOfGPIORegisters{ 10 };
  std::array<RegisterType, numberOfGPIORegisters> gpioRegisterSet{};
};

TEST_F(GPIORegisterTest, setPinOneToInput) // NOLINT: Static storage warning.
{
  const auto pinNumber = 0;
  GPIORegisters<RegisterTypeHost>::setPortMode<PortMode::input, pinNumber>(registerSetBaseAddressValue);

  static constexpr auto expectedValue = UINT32_C(0b00);
  EXPECT_EQ(gpioRegisterSet.at(0), expectedValue);
}

TEST_F(GPIORegisterTest, setPinFiveToGeneralpurposeOutput) // NOLINT: Static storage warning.
{
  const auto pinNumber = 5;
  GPIORegisters<RegisterTypeHost>::setPortMode<PortMode::generalpurposeOutput, pinNumber>(registerSetBaseAddressValue);

  const auto numberOfShifts = UINT32_C(pinNumber * 2);
  const auto expectedValue = UINT32_C(0b01) << numberOfShifts;
  EXPECT_EQ(gpioRegisterSet.at(0), expectedValue);
}

TEST_F(GPIORegisterTest, setPinTenToAlternateFunction) // NOLINT: Static storage warning.
{
  const auto pinNumber = 10;
  GPIORegisters<RegisterTypeHost>::setPortMode<PortMode::alternateFunction, pinNumber>(registerSetBaseAddressValue);

  const auto numberOfShifts = UINT32_C(pinNumber * 2);
  const auto expectedValue = UINT32_C(0b10) << numberOfShifts;
  EXPECT_EQ(gpioRegisterSet.at(0), expectedValue);
}

TEST_F(GPIORegisterTest, setPinFifteenToAnalog) // NOLINT: Static storage warning.
{
  const auto pinNumber = 15;
  GPIORegisters<RegisterTypeHost>::setPortMode<PortMode::analog, pinNumber>(registerSetBaseAddressValue);

  const auto numberOfShifts = UINT32_C(pinNumber * 2);
  const auto expectedValue = UINT32_C(0b11) << numberOfShifts;
  EXPECT_EQ(gpioRegisterSet.at(0), expectedValue);
}

int main(int argc, char **argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
