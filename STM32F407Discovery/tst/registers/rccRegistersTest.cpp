
#include <gtest/gtest.h>

#include "targetSpecific/registers/rccRegisters.h"

class RCCRegisterTest : public ::testing::Test
{
protected:
  using RegisterTypeHost = std::uint64_t;

  void SetUp() override
  {
    std::fill(rccRegisterSet.begin(), rccRegisterSet.end(), 0);
    registerSetBaseAddressValue =
      reinterpret_cast<RegisterTypeHost>(rccRegisterSet.data()); // NOLINT: Ignored reinterpret_cast by clang-tidy.
  }

  void setCFGRValue(const RegisterType value) { rccRegisterSet.at(2) = value; }
  [[nodiscard]] RegisterType getValueOfAHB1RstrRegister() const { return rccRegisterSet.at(4); }
  [[nodiscard]] RegisterType getValueOfAPB1RstrRegister() const { return rccRegisterSet.at(8); }
  [[nodiscard]] RegisterType getValueOfAPB2RstrRegister() const { return rccRegisterSet.at(9); }


  [[nodiscard]] RegisterType getValueOfAHB1EnrRegister() const { return rccRegisterSet.at(12); }
  [[nodiscard]] RegisterType getValueOfAPB1EnrRegister() const { return rccRegisterSet.at(16); }
  [[nodiscard]] RegisterType getValueOfAPB2EnrRegister() const { return rccRegisterSet.at(17); }

  RegisterTypeHost registerSetBaseAddressValue{ 0 };
  static constexpr auto numberOfRCCRegisters{ 36 };
  std::array<RegisterType, numberOfRCCRegisters> rccRegisterSet{};
};

TEST_F(RCCRegisterTest, enableDisableGPIOAClock) // NOLINT: Static storage warning.
{
  RCCRegisters<RegisterTypeHost>::setPeripheralOnAHB1<PeripheralAHB1::GPIOA, true>(registerSetBaseAddressValue);

  const auto numberOfShifts = UINT32_C(0);
  auto expectedValue = UINT32_C(0b1) << numberOfShifts;
  EXPECT_EQ(getValueOfAHB1EnrRegister(), expectedValue);

  RCCRegisters<RegisterTypeHost>::setPeripheralOnAHB1<PeripheralAHB1::GPIOA, false>(registerSetBaseAddressValue);
  expectedValue = 0;
  EXPECT_EQ(getValueOfAHB1EnrRegister(), expectedValue);
}

TEST_F(RCCRegisterTest, enableDisableGPIOHClock) // NOLINT: Static storage warning.
{
  RCCRegisters<RegisterTypeHost>::setPeripheralOnAHB1<PeripheralAHB1::GPIOH, true>(registerSetBaseAddressValue);

  const auto numberOfShifts = UINT32_C(7);
  auto expectedValue = UINT32_C(0b1) << numberOfShifts;
  EXPECT_EQ(getValueOfAHB1EnrRegister(), expectedValue);

  RCCRegisters<RegisterTypeHost>::setPeripheralOnAHB1<PeripheralAHB1::GPIOH, false>(registerSetBaseAddressValue);
  expectedValue = 0;
  EXPECT_EQ(getValueOfAHB1EnrRegister(), expectedValue);
}

TEST_F(RCCRegisterTest, enableDisableI2C3Clock) // NOLINT: Static storage warning.
{
  RCCRegisters<RegisterTypeHost>::setPeripheralOnAPB1<PeripheralAPB1::I2C3, true>(registerSetBaseAddressValue);

  const auto numberOfShifts = UINT32_C(23);
  auto expectedValue = UINT32_C(0b1) << numberOfShifts;
  EXPECT_EQ(getValueOfAPB1EnrRegister(), expectedValue);

  RCCRegisters<RegisterTypeHost>::setPeripheralOnAPB1<PeripheralAPB1::I2C3, false>(registerSetBaseAddressValue);
  expectedValue = 0;
  EXPECT_EQ(getValueOfAHB1EnrRegister(), expectedValue);
}

TEST_F(RCCRegisterTest, enableDisableSYSCFGlock) // NOLINT: Static storage warning.
{
  RCCRegisters<RegisterTypeHost>::setPeripheralOnAPB2<PeripheralAPB2::SYSCFG, true>(registerSetBaseAddressValue);

  const auto numberOfShifts = UINT32_C(14);
  auto expectedValue = UINT32_C(0b1) << numberOfShifts;
  EXPECT_EQ(getValueOfAPB2EnrRegister(), expectedValue);

  RCCRegisters<RegisterTypeHost>::setPeripheralOnAPB2<PeripheralAPB2::SYSCFG, false>(registerSetBaseAddressValue);
  expectedValue = 0;
  EXPECT_EQ(getValueOfAPB2EnrRegister(), expectedValue);
}

TEST_F(RCCRegisterTest, resetGPIOC) // NOLINT: Static storage warning.
{
  RCCRegisters<RegisterTypeHost>::resetPeripheralOnAHB1<PeripheralAHB1::GPIOC>(registerSetBaseAddressValue);

  const auto numberOfShifts = UINT32_C(2);
  auto expectedValue = UINT32_C(0b0) << numberOfShifts;
  EXPECT_EQ(getValueOfAHB1RstrRegister(), expectedValue);
}

TEST_F(RCCRegisterTest, resetI2C2) // NOLINT: Static storage warning.
{
  RCCRegisters<RegisterTypeHost>::resetPeripheralOnAPB1<PeripheralAPB1::I2C2>(registerSetBaseAddressValue);

  const auto numberOfShifts = UINT32_C(22);
  auto expectedValue = UINT32_C(0b0) << numberOfShifts;
  EXPECT_EQ(getValueOfAPB1RstrRegister(), expectedValue);
}

TEST_F(RCCRegisterTest, resetSYSCFG) // NOLINT: Static storage warning.
{
  RCCRegisters<RegisterTypeHost>::resetPeripheralOnAPB2<PeripheralAPB2::SYSCFG>(registerSetBaseAddressValue);

  const auto numberOfShifts = UINT32_C(14);
  auto expectedValue = UINT32_C(0b0) << numberOfShifts;
  EXPECT_EQ(getValueOfAPB2RstrRegister(), expectedValue);
}

TEST_F(RCCRegisterTest, getAPB1ClockHZ) // NOLINT: Static storage warning.
{
  RegisterType cfgrValue = 0b0;

  // Set system clock to hsi
  const auto systemClockShiftValue = 2;
  const auto hsiValue = 0b00;
  cfgrValue = cfgrValue | (hsiValue << systemClockShiftValue);

  RegisterType ahbPrescaler = 0b1011;
  const auto ahbPrescalerShiftValue = 4;
  cfgrValue = cfgrValue | (ahbPrescaler << ahbPrescalerShiftValue);

  RegisterType apb1Prescaler = 0b101;
  const auto apb1PrescalerShiftValue = 10;
  cfgrValue = cfgrValue | (apb1Prescaler << apb1PrescalerShiftValue);

  setCFGRValue(cfgrValue);

  auto apb1Clock = RCCRegisters<RegisterTypeHost>::getAPB1ClockHZ(registerSetBaseAddressValue);

  const auto expectedHSIValue = 16000000;
  auto expectedAhbPrescalerahbPrescaler = 16;
  auto expectedApb1PrescalerahbPrescaler = 4;
  auto expectedApb1Clock = (expectedHSIValue / expectedAhbPrescalerahbPrescaler) / expectedApb1PrescalerahbPrescaler;
  EXPECT_EQ(apb1Clock, expectedApb1Clock);
}
