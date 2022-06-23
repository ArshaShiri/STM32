#include <gtest/gtest.h>

#include "targetSpecific/registers/i2cRegisters.h"

class I2CRegisterTest : public ::testing::Test
{
protected:
  using RegisterTypeHost = std::uint64_t;
  using I2CRegs = I2CRegisters<RegisterTypeHost>;

  void SetUp() override
  {
    std::fill(i2cRegisterSet.begin(), i2cRegisterSet.end(), 0);
    registerSetBaseAddressValue =
      reinterpret_cast<RegisterTypeHost>(i2cRegisterSet.data()); // NOLINT: Ignored reinterpret_cast by clang-tidy.
  }

  [[nodiscard]] RegisterType getValueOfControlRegister1() const { return i2cRegisterSet.at(0); }
  [[nodiscard]] RegisterType getValueOfControlRegister2() const { return i2cRegisterSet.at(1); }
  [[nodiscard]] RegisterType getValueOfOwnAddressRegister() const { return i2cRegisterSet.at(2); }

  RegisterTypeHost registerSetBaseAddressValue{ 0 };
  static constexpr auto numberOfI2CRegisters{ 10 };
  std::array<RegisterType, numberOfI2CRegisters> i2cRegisterSet{};
};

TEST_F(I2CRegisterTest, setPeripheral) // NOLINT: Static storage warning.
{
  I2CRegs::setControlRegister1Bit<ControlRegister1Property::pe, Peripheral, Peripheral::enable>(
    registerSetBaseAddressValue);

  const auto numberOfShifts = UINT32_C(0);
  auto expectedValue = UINT32_C(0b1) << numberOfShifts;
  EXPECT_EQ(getValueOfControlRegister1(), expectedValue);

  I2CRegs::setControlRegister1Bit<ControlRegister1Property::pe, Peripheral, Peripheral::disable>(
    registerSetBaseAddressValue);

  expectedValue = 0;
  EXPECT_EQ(getValueOfControlRegister1(), expectedValue);
}

TEST_F(I2CRegisterTest, setAcknowledge) // NOLINT: Static storage warning.
{
  I2CRegs::setControlRegister1Bit<ControlRegister1Property::ack, Acknowledge, Acknowledge::enable>(
    registerSetBaseAddressValue);

  const auto numberOfShifts = UINT32_C(10);
  auto expectedValue = UINT32_C(0b1) << numberOfShifts;
  EXPECT_EQ(getValueOfControlRegister1(), expectedValue);

  I2CRegs::setControlRegister1Bit<ControlRegister1Property::ack, Acknowledge, Acknowledge::disable>(
    registerSetBaseAddressValue);

  expectedValue = 0;
  EXPECT_EQ(getValueOfControlRegister1(), expectedValue);
}

TEST_F(I2CRegisterTest, setPeripheralClockFrequency) // NOLINT: Static storage warning.
{
  uint8_t clockFrequencyValueMhz = 16;
  I2CRegs::setPeripheralClockFrequency(registerSetBaseAddressValue, clockFrequencyValueMhz);
  EXPECT_EQ(getValueOfControlRegister2(), clockFrequencyValueMhz);

  clockFrequencyValueMhz = 48;
  I2CRegs::setPeripheralClockFrequency(registerSetBaseAddressValue, clockFrequencyValueMhz);
  EXPECT_EQ(getValueOfControlRegister2(), clockFrequencyValueMhz);
}

TEST_F(I2CRegisterTest, setOwnAddress) // NOLINT: Static storage warning.
{
  uint8_t ownAddress = 0b1101011;
  constexpr auto shiftValueForSevenBitAddress = 1;
  I2CRegs::setOwnAddress(registerSetBaseAddressValue, ownAddress);
  EXPECT_EQ(getValueOfOwnAddressRegister(), ownAddress << shiftValueForSevenBitAddress);
}
