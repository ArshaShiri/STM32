#include <gtest/gtest.h>

#include "targetSpecific/registers/spiRegisters.h"

class SPIRegisterTest : public ::testing::Test
{
protected:
  using RegisterTypeHost = std::uint64_t;

  void SetUp() override
  {
    std::fill(spiRegisterSet.begin(), spiRegisterSet.end(), 0);
    registerSetBaseAddressValue =
      reinterpret_cast<RegisterTypeHost>(spiRegisterSet.data()); // NOLINT: Ignored reinterpret_cast by clang-tidy.
  }

  [[nodiscard]] RegisterType getValueOfControlRegister1() const { return spiRegisterSet.at(0); }
  [[nodiscard]] RegisterType getValueOfControlRegister2() const { return spiRegisterSet.at(1); }

  RegisterTypeHost registerSetBaseAddressValue{ 0 };
  static constexpr auto numberOfSPIRegisters{ 9 };
  std::array<RegisterType, numberOfSPIRegisters> spiRegisterSet{};
};

TEST_F(SPIRegisterTest, setUnsetcpha) // NOLINT: Static storage warning.
{
  SPIRegisters<RegisterTypeHost>::setControlRegister1Bit<ControlRegister1Property::cpha, true>(
    registerSetBaseAddressValue);

  const auto numberOfShifts = UINT32_C(0);
  auto expectedValue = UINT32_C(0b1) << numberOfShifts;
  EXPECT_EQ(getValueOfControlRegister1(), expectedValue);

  SPIRegisters<RegisterTypeHost>::setControlRegister1Bit<ControlRegister1Property::cpha, false>(
    registerSetBaseAddressValue);
  expectedValue = 0;
  EXPECT_EQ(getValueOfControlRegister1(), expectedValue);
}

TEST_F(SPIRegisterTest, setUnsetcpol) // NOLINT: Static storage warning.
{
  SPIRegisters<RegisterTypeHost>::setControlRegister1Bit<ControlRegister1Property::cpol, true>(
    registerSetBaseAddressValue);

  const auto numberOfShifts = UINT32_C(1);
  auto expectedValue = UINT32_C(0b1) << numberOfShifts;
  EXPECT_EQ(getValueOfControlRegister1(), expectedValue);

  SPIRegisters<RegisterTypeHost>::setControlRegister1Bit<ControlRegister1Property::cpol, false>(
    registerSetBaseAddressValue);
  expectedValue = 0;
  EXPECT_EQ(getValueOfControlRegister1(), expectedValue);
}

TEST_F(SPIRegisterTest, setUnsetmstr) // NOLINT: Static storage warning.
{
  SPIRegisters<RegisterTypeHost>::setControlRegister1Bit<ControlRegister1Property::mstr, true>(
    registerSetBaseAddressValue);

  const auto numberOfShifts = UINT32_C(2);
  auto expectedValue = UINT32_C(0b1) << numberOfShifts;
  EXPECT_EQ(getValueOfControlRegister1(), expectedValue);

  SPIRegisters<RegisterTypeHost>::setControlRegister1Bit<ControlRegister1Property::mstr, false>(
    registerSetBaseAddressValue);
  expectedValue = 0;
  EXPECT_EQ(getValueOfControlRegister1(), expectedValue);
}

TEST_F(SPIRegisterTest, setUnsetSPE) // NOLINT: Static storage warning.
{
  SPIRegisters<RegisterTypeHost>::setControlRegister1Bit<ControlRegister1Property::spe, true>(
    registerSetBaseAddressValue);

  const auto numberOfShifts = UINT32_C(6);
  auto expectedValue = UINT32_C(0b1) << numberOfShifts;
  EXPECT_EQ(getValueOfControlRegister1(), expectedValue);

  SPIRegisters<RegisterTypeHost>::setControlRegister1Bit<ControlRegister1Property::spe, false>(
    registerSetBaseAddressValue);
  expectedValue = 0;
  EXPECT_EQ(getValueOfControlRegister1(), expectedValue);
}

TEST_F(SPIRegisterTest, setUnsetLSBFIRST) // NOLINT: Static storage warning.
{
  SPIRegisters<RegisterTypeHost>::setControlRegister1Bit<ControlRegister1Property::lsbfirst, true>(
    registerSetBaseAddressValue);

  const auto numberOfShifts = UINT32_C(7);
  auto expectedValue = UINT32_C(0b1) << numberOfShifts;
  EXPECT_EQ(getValueOfControlRegister1(), expectedValue);

  SPIRegisters<RegisterTypeHost>::setControlRegister1Bit<ControlRegister1Property::lsbfirst, false>(
    registerSetBaseAddressValue);
  expectedValue = 0;
  EXPECT_EQ(getValueOfControlRegister1(), expectedValue);
}

TEST_F(SPIRegisterTest, setUnsetSSI) // NOLINT: Static storage warning.
{
  SPIRegisters<RegisterTypeHost>::setControlRegister1Bit<ControlRegister1Property::ssi, true>(
    registerSetBaseAddressValue);

  const auto numberOfShifts = UINT32_C(8);
  auto expectedValue = UINT32_C(0b1) << numberOfShifts;
  EXPECT_EQ(getValueOfControlRegister1(), expectedValue);

  SPIRegisters<RegisterTypeHost>::setControlRegister1Bit<ControlRegister1Property::ssi, false>(
    registerSetBaseAddressValue);
  expectedValue = 0;
  EXPECT_EQ(getValueOfControlRegister1(), expectedValue);
}

TEST_F(SPIRegisterTest, setUnsetSSM) // NOLINT: Static storage warning.
{
  SPIRegisters<RegisterTypeHost>::setControlRegister1Bit<ControlRegister1Property::ssm, true>(
    registerSetBaseAddressValue);

  const auto numberOfShifts = UINT32_C(9);
  auto expectedValue = UINT32_C(0b1) << numberOfShifts;
  EXPECT_EQ(getValueOfControlRegister1(), expectedValue);

  SPIRegisters<RegisterTypeHost>::setControlRegister1Bit<ControlRegister1Property::ssm, false>(
    registerSetBaseAddressValue);
  expectedValue = 0;
  EXPECT_EQ(getValueOfControlRegister1(), expectedValue);
}

TEST_F(SPIRegisterTest, setUnsetRXONLY) // NOLINT: Static storage warning.
{
  SPIRegisters<RegisterTypeHost>::setControlRegister1Bit<ControlRegister1Property::rxonly, true>(
    registerSetBaseAddressValue);

  const auto numberOfShifts = UINT32_C(10);
  auto expectedValue = UINT32_C(0b1) << numberOfShifts;
  EXPECT_EQ(getValueOfControlRegister1(), expectedValue);

  SPIRegisters<RegisterTypeHost>::setControlRegister1Bit<ControlRegister1Property::rxonly, false>(
    registerSetBaseAddressValue);
  expectedValue = 0;
  EXPECT_EQ(getValueOfControlRegister1(), expectedValue);
}

TEST_F(SPIRegisterTest, setUnsetDFF) // NOLINT: Static storage warning.
{
  SPIRegisters<RegisterTypeHost>::setControlRegister1Bit<ControlRegister1Property::dff, true>(
    registerSetBaseAddressValue);

  const auto numberOfShifts = UINT32_C(11);
  auto expectedValue = UINT32_C(0b1) << numberOfShifts;
  EXPECT_EQ(getValueOfControlRegister1(), expectedValue);

  SPIRegisters<RegisterTypeHost>::setControlRegister1Bit<ControlRegister1Property::dff, false>(
    registerSetBaseAddressValue);
  expectedValue = 0;
  EXPECT_EQ(getValueOfControlRegister1(), expectedValue);
}

TEST_F(SPIRegisterTest, setUnsetCRCNEXT) // NOLINT: Static storage warning.
{
  SPIRegisters<RegisterTypeHost>::setControlRegister1Bit<ControlRegister1Property::crcnext, true>(
    registerSetBaseAddressValue);

  const auto numberOfShifts = UINT32_C(12);
  auto expectedValue = UINT32_C(0b1) << numberOfShifts;
  EXPECT_EQ(getValueOfControlRegister1(), expectedValue);

  SPIRegisters<RegisterTypeHost>::setControlRegister1Bit<ControlRegister1Property::crcnext, false>(
    registerSetBaseAddressValue);
  expectedValue = 0;
  EXPECT_EQ(getValueOfControlRegister1(), expectedValue);
}

TEST_F(SPIRegisterTest, setUnsetCRCEN) // NOLINT: Static storage warning.
{
  SPIRegisters<RegisterTypeHost>::setControlRegister1Bit<ControlRegister1Property::crcen, true>(
    registerSetBaseAddressValue);

  const auto numberOfShifts = UINT32_C(13);
  auto expectedValue = UINT32_C(0b1) << numberOfShifts;
  EXPECT_EQ(getValueOfControlRegister1(), expectedValue);

  SPIRegisters<RegisterTypeHost>::setControlRegister1Bit<ControlRegister1Property::crcen, false>(
    registerSetBaseAddressValue);
  expectedValue = 0;
  EXPECT_EQ(getValueOfControlRegister1(), expectedValue);
}

TEST_F(SPIRegisterTest, setUnsetBIDIOE) // NOLINT: Static storage warning.
{
  SPIRegisters<RegisterTypeHost>::setControlRegister1Bit<ControlRegister1Property::bidioe, true>(
    registerSetBaseAddressValue);

  const auto numberOfShifts = UINT32_C(14);
  auto expectedValue = UINT32_C(0b1) << numberOfShifts;
  EXPECT_EQ(getValueOfControlRegister1(), expectedValue);

  SPIRegisters<RegisterTypeHost>::setControlRegister1Bit<ControlRegister1Property::bidioe, false>(
    registerSetBaseAddressValue);
  expectedValue = 0;
  EXPECT_EQ(getValueOfControlRegister1(), expectedValue);
}

TEST_F(SPIRegisterTest, setUnsetBIDIMODE) // NOLINT: Static storage warning.
{
  SPIRegisters<RegisterTypeHost>::setControlRegister1Bit<ControlRegister1Property::bidimode, true>(
    registerSetBaseAddressValue);

  const auto numberOfShifts = UINT32_C(15);
  auto expectedValue = UINT32_C(0b1) << numberOfShifts;
  EXPECT_EQ(getValueOfControlRegister1(), expectedValue);

  SPIRegisters<RegisterTypeHost>::setControlRegister1Bit<ControlRegister1Property::bidimode, false>(
    registerSetBaseAddressValue);
  expectedValue = 0;
  EXPECT_EQ(getValueOfControlRegister1(), expectedValue);
}

TEST_F(SPIRegisterTest, setBaudRate) // NOLINT: Static storage warning.
{
  SPIRegisters<RegisterTypeHost>::setBaudRate<BaudRateControl::fPCLKDiv16, true>(registerSetBaseAddressValue);

  const auto numberOfShifts = UINT32_C(3);
  auto expectedValue = UINT32_C(0b011) << numberOfShifts;
  EXPECT_EQ(getValueOfControlRegister1(), expectedValue);
}

TEST_F(SPIRegisterTest, setUnsetRXDMAEN) // NOLINT: Static storage warning.
{
  SPIRegisters<RegisterTypeHost>::setControlRegister2Bit<ControlRegister2Property::rxdmaen, true>(
    registerSetBaseAddressValue);

  const auto numberOfShifts = UINT32_C(0);
  auto expectedValue = UINT32_C(0b1) << numberOfShifts;
  EXPECT_EQ(getValueOfControlRegister2(), expectedValue);

  SPIRegisters<RegisterTypeHost>::setControlRegister2Bit<ControlRegister2Property::rxdmaen, false>(
    registerSetBaseAddressValue);
  expectedValue = 0;
  EXPECT_EQ(getValueOfControlRegister2(), expectedValue);
}

TEST_F(SPIRegisterTest, setUnsetTXDMAEN) // NOLINT: Static storage warning.
{
  SPIRegisters<RegisterTypeHost>::setControlRegister2Bit<ControlRegister2Property::txdmaen, true>(
    registerSetBaseAddressValue);

  const auto numberOfShifts = UINT32_C(1);
  auto expectedValue = UINT32_C(0b1) << numberOfShifts;
  EXPECT_EQ(getValueOfControlRegister2(), expectedValue);

  SPIRegisters<RegisterTypeHost>::setControlRegister2Bit<ControlRegister2Property::txdmaen, false>(
    registerSetBaseAddressValue);
  expectedValue = 0;
  EXPECT_EQ(getValueOfControlRegister2(), expectedValue);
}

TEST_F(SPIRegisterTest, setUnsetSSOE) // NOLINT: Static storage warning.
{
  SPIRegisters<RegisterTypeHost>::setControlRegister2Bit<ControlRegister2Property::ssoe, true>(
    registerSetBaseAddressValue);

  const auto numberOfShifts = UINT32_C(2);
  auto expectedValue = UINT32_C(0b1) << numberOfShifts;
  EXPECT_EQ(getValueOfControlRegister2(), expectedValue);

  SPIRegisters<RegisterTypeHost>::setControlRegister2Bit<ControlRegister2Property::ssoe, false>(
    registerSetBaseAddressValue);
  expectedValue = 0;
  EXPECT_EQ(getValueOfControlRegister2(), expectedValue);
}

TEST_F(SPIRegisterTest, setUnsetFRF) // NOLINT: Static storage warning.
{
  SPIRegisters<RegisterTypeHost>::setControlRegister2Bit<ControlRegister2Property::frf, true>(
    registerSetBaseAddressValue);

  const auto numberOfShifts = UINT32_C(4);
  auto expectedValue = UINT32_C(0b1) << numberOfShifts;
  EXPECT_EQ(getValueOfControlRegister2(), expectedValue);

  SPIRegisters<RegisterTypeHost>::setControlRegister2Bit<ControlRegister2Property::frf, false>(
    registerSetBaseAddressValue);
  expectedValue = 0;
  EXPECT_EQ(getValueOfControlRegister2(), expectedValue);
}

TEST_F(SPIRegisterTest, setUnsetERRIE) // NOLINT: Static storage warning.
{
  SPIRegisters<RegisterTypeHost>::setControlRegister2Bit<ControlRegister2Property::errie, true>(
    registerSetBaseAddressValue);

  const auto numberOfShifts = UINT32_C(5);
  auto expectedValue = UINT32_C(0b1) << numberOfShifts;
  EXPECT_EQ(getValueOfControlRegister2(), expectedValue);

  SPIRegisters<RegisterTypeHost>::setControlRegister2Bit<ControlRegister2Property::errie, false>(
    registerSetBaseAddressValue);
  expectedValue = 0;
  EXPECT_EQ(getValueOfControlRegister2(), expectedValue);
}

TEST_F(SPIRegisterTest, setUnsetRXNEIE) // NOLINT: Static storage warning.
{
  SPIRegisters<RegisterTypeHost>::setControlRegister2Bit<ControlRegister2Property::rxneie, true>(
    registerSetBaseAddressValue);

  const auto numberOfShifts = UINT32_C(6);
  auto expectedValue = UINT32_C(0b1) << numberOfShifts;
  EXPECT_EQ(getValueOfControlRegister2(), expectedValue);

  SPIRegisters<RegisterTypeHost>::setControlRegister2Bit<ControlRegister2Property::rxneie, false>(
    registerSetBaseAddressValue);
  expectedValue = 0;
  EXPECT_EQ(getValueOfControlRegister2(), expectedValue);
}

TEST_F(SPIRegisterTest, setUnsetTXEIE) // NOLINT: Static storage warning.
{
  SPIRegisters<RegisterTypeHost>::setControlRegister2Bit<ControlRegister2Property::txeie, true>(
    registerSetBaseAddressValue);

  const auto numberOfShifts = UINT32_C(7);
  auto expectedValue = UINT32_C(0b1) << numberOfShifts;
  EXPECT_EQ(getValueOfControlRegister2(), expectedValue);

  SPIRegisters<RegisterTypeHost>::setControlRegister2Bit<ControlRegister2Property::txeie, false>(
    registerSetBaseAddressValue);
  expectedValue = 0;
  EXPECT_EQ(getValueOfControlRegister2(), expectedValue);
}
