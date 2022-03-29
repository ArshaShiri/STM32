#include <algorithm>
#include <array>

#include <gtest/gtest.h>

#include "targetSpecific/gpioRegisters.h"
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

  [[nodiscard]] RegisterType getValueOfModeRegister() const { return gpioRegisterSet.at(0); }
  [[nodiscard]] RegisterType getValueOfOutputTypeRegister() const { return gpioRegisterSet.at(1); }
  [[nodiscard]] RegisterType getValueOfOutputSpeedRegister() const { return gpioRegisterSet.at(2); }
  [[nodiscard]] RegisterType getValueOfPullupPullDownRegister() const { return gpioRegisterSet.at(3); }

  RegisterTypeHost registerSetBaseAddressValue{ 0 };
  static constexpr auto numberOfGPIORegisters{ 10 };
  std::array<RegisterType, numberOfGPIORegisters> gpioRegisterSet{};
};

TEST_F(GPIORegisterTest, setPinOneModeToInput) // NOLINT: Static storage warning.
{
  const auto pinNumber = 0;
  GPIORegisters<RegisterTypeHost>::setPortMode<PortMode::input, pinNumber>(registerSetBaseAddressValue);

  const auto expectedValue = UINT32_C(0b00);
  EXPECT_EQ(getValueOfModeRegister(), expectedValue);
}

TEST_F(GPIORegisterTest, setPinFiveModeToGeneralpurposeOutput) // NOLINT: Static storage warning.
{
  const auto pinNumber = 5;
  GPIORegisters<RegisterTypeHost>::setPortMode<PortMode::generalpurposeOutput, pinNumber>(registerSetBaseAddressValue);

  const auto numberOfShifts = UINT32_C(pinNumber * 2);
  const auto expectedValue = UINT32_C(0b01) << numberOfShifts;
  EXPECT_EQ(getValueOfModeRegister(), expectedValue);
}

TEST_F(GPIORegisterTest, setPinTenModeToAlternateFunction) // NOLINT: Static storage warning.
{
  const auto pinNumber = 10;
  GPIORegisters<RegisterTypeHost>::setPortMode<PortMode::alternateFunction, pinNumber>(registerSetBaseAddressValue);

  const auto numberOfShifts = UINT32_C(pinNumber * 2);
  const auto expectedValue = UINT32_C(0b10) << numberOfShifts;
  EXPECT_EQ(getValueOfModeRegister(), expectedValue);
}

TEST_F(GPIORegisterTest, setPinFifteenModeToAnalog) // NOLINT: Static storage warning.
{
  const auto pinNumber = 15;
  GPIORegisters<RegisterTypeHost>::setPortMode<PortMode::analog, pinNumber>(registerSetBaseAddressValue);

  const auto numberOfShifts = UINT32_C(pinNumber * 2);
  const auto expectedValue = UINT32_C(0b11) << numberOfShifts;
  EXPECT_EQ(getValueOfModeRegister(), expectedValue);
}

TEST_F(GPIORegisterTest, setOutputTypeToPushPull) // NOLINT: Static storage warning.
{
  const auto pinNumber = 13;
  GPIORegisters<RegisterTypeHost>::setOutputType<OutputType::pushPull, pinNumber>(registerSetBaseAddressValue);

  const auto expectedValue = UINT32_C(0b0) << pinNumber;
  EXPECT_EQ(getValueOfOutputTypeRegister(), expectedValue);
}

TEST_F(GPIORegisterTest, setOutputTypeToOpenDrain) // NOLINT: Static storage warning.
{
  const auto pinNumber = 15;
  GPIORegisters<RegisterTypeHost>::setOutputType<OutputType::openDrain, pinNumber>(registerSetBaseAddressValue);

  const auto expectedValue = UINT32_C(0b1) << pinNumber;
  EXPECT_EQ(getValueOfOutputTypeRegister(), expectedValue);
}

TEST_F(GPIORegisterTest, setOutputSpeedToMedium) // NOLINT: Static storage warning.
{
  const auto pinNumber = 11;
  GPIORegisters<RegisterTypeHost>::setOutputSpeed<OutputSpeed::medium, pinNumber>(registerSetBaseAddressValue);

  const auto numberOfShifts = UINT32_C(pinNumber * 2);
  const auto expectedValue = UINT32_C(0b01) << numberOfShifts;
  EXPECT_EQ(getValueOfOutputSpeedRegister(), expectedValue);
}

TEST_F(GPIORegisterTest, setOutputSpeedToVeryHight) // NOLINT: Static storage warning.
{
  const auto pinNumber = 15;
  GPIORegisters<RegisterTypeHost>::setOutputSpeed<OutputSpeed::veryHigh, pinNumber>(registerSetBaseAddressValue);

  const auto numberOfShifts = UINT32_C(pinNumber * 2);
  const auto expectedValue = UINT32_C(0b11) << numberOfShifts;
  EXPECT_EQ(getValueOfOutputSpeedRegister(), expectedValue);
}

TEST_F(GPIORegisterTest, setPullupPullDownToPullDown) // NOLINT: Static storage warning.
{
  const auto pinNumber = 7;
  GPIORegisters<RegisterTypeHost>::setPullupPullDown<PullupPullDownControl::pullDown, pinNumber>(
    registerSetBaseAddressValue);

  const auto numberOfShifts = UINT32_C(pinNumber * 2);
  const auto expectedValue = UINT32_C(0b10) << numberOfShifts;
  EXPECT_EQ(getValueOfPullupPullDownRegister(), expectedValue);
}

TEST_F(GPIORegisterTest, setPullupPullDownToPullup) // NOLINT: Static storage warning.
{
  const auto pinNumber = 3;
  GPIORegisters<RegisterTypeHost>::setPullupPullDown<PullupPullDownControl::pullup, pinNumber>(
    registerSetBaseAddressValue);

  const auto numberOfShifts = UINT32_C(pinNumber * 2);
  const auto expectedValue = UINT32_C(0b01) << numberOfShifts;
  EXPECT_EQ(getValueOfPullupPullDownRegister(), expectedValue);
}
