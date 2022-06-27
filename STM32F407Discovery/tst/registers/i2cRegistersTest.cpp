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
  [[nodiscard]] RegisterType getValueOfDataRegister() const { return i2cRegisterSet.at(4); }
  void setStatusRegister1(RegisterType value) { i2cRegisterSet.at(5) = value; }
  void setStatusRegister2(RegisterType value) { i2cRegisterSet.at(6) = value; }

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

TEST_F(I2CRegisterTest, isStartConditionGenerated) // NOLINT: Static storage warning.
{
  const auto value = 0b1;
  setStatusRegister1(value);
  EXPECT_TRUE(I2CRegs::isStartConditionGenerated(registerSetBaseAddressValue));
}

TEST_F(I2CRegisterTest, isAddressTransmissionFinished) // NOLINT: Static storage warning.
{
  const auto value = 0b10;
  setStatusRegister1(value);
  EXPECT_TRUE(I2CRegs::isAddressTransmissionFinished(registerSetBaseAddressValue));
}

TEST_F(I2CRegisterTest, writeToDataRegister) // NOLINT: Static storage warning.
{
  const uint8_t value = 176;
  I2CRegs::writeToDataRegister(registerSetBaseAddressValue, value);
  EXPECT_EQ(getValueOfDataRegister(), value);
}

TEST_F(I2CRegisterTest, readStatusRegister1) // NOLINT: Static storage warning.
{
  const auto value1 = 431465;
  setStatusRegister1(value1);
  EXPECT_EQ(I2CRegs::readStatusRegister1(registerSetBaseAddressValue), value1);
}

TEST_F(I2CRegisterTest, readStatusRegister2) // NOLINT: Static storage warning.
{
  const auto value2 = 45561465;
  setStatusRegister2(value2);
  EXPECT_EQ(I2CRegs::readStatusRegister2(registerSetBaseAddressValue), value2);
}
