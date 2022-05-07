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

TEST_F(SPIRegisterTest, setUnsetCPHA) // NOLINT: Static storage warning.
{
  SPIRegisters<RegisterTypeHost>::setControlRegister1Bit<ControlRegister1Property::CPHA, true>(
    registerSetBaseAddressValue);

  const auto numberOfShifts = UINT32_C(0);
  auto expectedValue = UINT32_C(0b1) << numberOfShifts;
  EXPECT_EQ(getValueOfControlRegister1(), expectedValue);

  SPIRegisters<RegisterTypeHost>::setControlRegister1Bit<ControlRegister1Property::CPHA, false>(
    registerSetBaseAddressValue);
  expectedValue = 0;
  EXPECT_EQ(getValueOfControlRegister1(), expectedValue);
}

TEST_F(SPIRegisterTest, setUnsetCPOL) // NOLINT: Static storage warning.
{
  SPIRegisters<RegisterTypeHost>::setControlRegister1Bit<ControlRegister1Property::CPOL, true>(
    registerSetBaseAddressValue);

  const auto numberOfShifts = UINT32_C(1);
  auto expectedValue = UINT32_C(0b1) << numberOfShifts;
  EXPECT_EQ(getValueOfControlRegister1(), expectedValue);

  SPIRegisters<RegisterTypeHost>::setControlRegister1Bit<ControlRegister1Property::CPOL, false>(
    registerSetBaseAddressValue);
  expectedValue = 0;
  EXPECT_EQ(getValueOfControlRegister1(), expectedValue);
}

TEST_F(SPIRegisterTest, setUnsetMSTR) // NOLINT: Static storage warning.
{
  SPIRegisters<RegisterTypeHost>::setControlRegister1Bit<ControlRegister1Property::MSTR, true>(
    registerSetBaseAddressValue);

  const auto numberOfShifts = UINT32_C(2);
  auto expectedValue = UINT32_C(0b1) << numberOfShifts;
  EXPECT_EQ(getValueOfControlRegister1(), expectedValue);

  SPIRegisters<RegisterTypeHost>::setControlRegister1Bit<ControlRegister1Property::MSTR, false>(
    registerSetBaseAddressValue);
  expectedValue = 0;
  EXPECT_EQ(getValueOfControlRegister1(), expectedValue);
}

TEST_F(SPIRegisterTest, setUnsetSPE) // NOLINT: Static storage warning.
{
  SPIRegisters<RegisterTypeHost>::setControlRegister1Bit<ControlRegister1Property::SPE, true>(
    registerSetBaseAddressValue);

  const auto numberOfShifts = UINT32_C(6);
  auto expectedValue = UINT32_C(0b1) << numberOfShifts;
  EXPECT_EQ(getValueOfControlRegister1(), expectedValue);

  SPIRegisters<RegisterTypeHost>::setControlRegister1Bit<ControlRegister1Property::SPE, false>(
    registerSetBaseAddressValue);
  expectedValue = 0;
  EXPECT_EQ(getValueOfControlRegister1(), expectedValue);
}

TEST_F(SPIRegisterTest, setUnsetLSBFIRST) // NOLINT: Static storage warning.
{
  SPIRegisters<RegisterTypeHost>::setControlRegister1Bit<ControlRegister1Property::LSBFIRST, true>(
    registerSetBaseAddressValue);

  const auto numberOfShifts = UINT32_C(7);
  auto expectedValue = UINT32_C(0b1) << numberOfShifts;
  EXPECT_EQ(getValueOfControlRegister1(), expectedValue);

  SPIRegisters<RegisterTypeHost>::setControlRegister1Bit<ControlRegister1Property::LSBFIRST, false>(
    registerSetBaseAddressValue);
  expectedValue = 0;
  EXPECT_EQ(getValueOfControlRegister1(), expectedValue);
}

TEST_F(SPIRegisterTest, setUnsetSSI) // NOLINT: Static storage warning.
{
  SPIRegisters<RegisterTypeHost>::setControlRegister1Bit<ControlRegister1Property::SSI, true>(
    registerSetBaseAddressValue);

  const auto numberOfShifts = UINT32_C(8);
  auto expectedValue = UINT32_C(0b1) << numberOfShifts;
  EXPECT_EQ(getValueOfControlRegister1(), expectedValue);

  SPIRegisters<RegisterTypeHost>::setControlRegister1Bit<ControlRegister1Property::SSI, false>(
    registerSetBaseAddressValue);
  expectedValue = 0;
  EXPECT_EQ(getValueOfControlRegister1(), expectedValue);
}

TEST_F(SPIRegisterTest, setUnsetSSM) // NOLINT: Static storage warning.
{
  SPIRegisters<RegisterTypeHost>::setControlRegister1Bit<ControlRegister1Property::SSM, true>(
    registerSetBaseAddressValue);

  const auto numberOfShifts = UINT32_C(9);
  auto expectedValue = UINT32_C(0b1) << numberOfShifts;
  EXPECT_EQ(getValueOfControlRegister1(), expectedValue);

  SPIRegisters<RegisterTypeHost>::setControlRegister1Bit<ControlRegister1Property::SSM, false>(
    registerSetBaseAddressValue);
  expectedValue = 0;
  EXPECT_EQ(getValueOfControlRegister1(), expectedValue);
}

TEST_F(SPIRegisterTest, setUnsetRXONLY) // NOLINT: Static storage warning.
{
  SPIRegisters<RegisterTypeHost>::setControlRegister1Bit<ControlRegister1Property::RXONLY, true>(
    registerSetBaseAddressValue);

  const auto numberOfShifts = UINT32_C(10);
  auto expectedValue = UINT32_C(0b1) << numberOfShifts;
  EXPECT_EQ(getValueOfControlRegister1(), expectedValue);

  SPIRegisters<RegisterTypeHost>::setControlRegister1Bit<ControlRegister1Property::RXONLY, false>(
    registerSetBaseAddressValue);
  expectedValue = 0;
  EXPECT_EQ(getValueOfControlRegister1(), expectedValue);
}

TEST_F(SPIRegisterTest, setUnsetDFF) // NOLINT: Static storage warning.
{
  SPIRegisters<RegisterTypeHost>::setControlRegister1Bit<ControlRegister1Property::DFF, true>(
    registerSetBaseAddressValue);

  const auto numberOfShifts = UINT32_C(11);
  auto expectedValue = UINT32_C(0b1) << numberOfShifts;
  EXPECT_EQ(getValueOfControlRegister1(), expectedValue);

  SPIRegisters<RegisterTypeHost>::setControlRegister1Bit<ControlRegister1Property::DFF, false>(
    registerSetBaseAddressValue);
  expectedValue = 0;
  EXPECT_EQ(getValueOfControlRegister1(), expectedValue);
}

TEST_F(SPIRegisterTest, setUnsetCRCNEXT) // NOLINT: Static storage warning.
{
  SPIRegisters<RegisterTypeHost>::setControlRegister1Bit<ControlRegister1Property::CRCNEXT, true>(
    registerSetBaseAddressValue);

  const auto numberOfShifts = UINT32_C(12);
  auto expectedValue = UINT32_C(0b1) << numberOfShifts;
  EXPECT_EQ(getValueOfControlRegister1(), expectedValue);

  SPIRegisters<RegisterTypeHost>::setControlRegister1Bit<ControlRegister1Property::CRCNEXT, false>(
    registerSetBaseAddressValue);
  expectedValue = 0;
  EXPECT_EQ(getValueOfControlRegister1(), expectedValue);
}

TEST_F(SPIRegisterTest, setUnsetCRCEN) // NOLINT: Static storage warning.
{
  SPIRegisters<RegisterTypeHost>::setControlRegister1Bit<ControlRegister1Property::CRCEN, true>(
    registerSetBaseAddressValue);

  const auto numberOfShifts = UINT32_C(13);
  auto expectedValue = UINT32_C(0b1) << numberOfShifts;
  EXPECT_EQ(getValueOfControlRegister1(), expectedValue);

  SPIRegisters<RegisterTypeHost>::setControlRegister1Bit<ControlRegister1Property::CRCEN, false>(
    registerSetBaseAddressValue);
  expectedValue = 0;
  EXPECT_EQ(getValueOfControlRegister1(), expectedValue);
}

TEST_F(SPIRegisterTest, setUnsetBIDIOE) // NOLINT: Static storage warning.
{
  SPIRegisters<RegisterTypeHost>::setControlRegister1Bit<ControlRegister1Property::BIDIOE, true>(
    registerSetBaseAddressValue);

  const auto numberOfShifts = UINT32_C(14);
  auto expectedValue = UINT32_C(0b1) << numberOfShifts;
  EXPECT_EQ(getValueOfControlRegister1(), expectedValue);

  SPIRegisters<RegisterTypeHost>::setControlRegister1Bit<ControlRegister1Property::BIDIOE, false>(
    registerSetBaseAddressValue);
  expectedValue = 0;
  EXPECT_EQ(getValueOfControlRegister1(), expectedValue);
}

TEST_F(SPIRegisterTest, setUnsetBIDIMODE) // NOLINT: Static storage warning.
{
  SPIRegisters<RegisterTypeHost>::setControlRegister1Bit<ControlRegister1Property::BIDIMODE, true>(
    registerSetBaseAddressValue);

  const auto numberOfShifts = UINT32_C(15);
  auto expectedValue = UINT32_C(0b1) << numberOfShifts;
  EXPECT_EQ(getValueOfControlRegister1(), expectedValue);

  SPIRegisters<RegisterTypeHost>::setControlRegister1Bit<ControlRegister1Property::BIDIMODE, false>(
    registerSetBaseAddressValue);
  expectedValue = 0;
  EXPECT_EQ(getValueOfControlRegister1(), expectedValue);
}

TEST_F(SPIRegisterTest, setUnsetRXDMAEN) // NOLINT: Static storage warning.
{
  SPIRegisters<RegisterTypeHost>::setControlRegister2Bit<ControlRegister2Property::RXDMAEN, true>(
    registerSetBaseAddressValue);

  const auto numberOfShifts = UINT32_C(0);
  auto expectedValue = UINT32_C(0b1) << numberOfShifts;
  EXPECT_EQ(getValueOfControlRegister2(), expectedValue);

  SPIRegisters<RegisterTypeHost>::setControlRegister2Bit<ControlRegister2Property::RXDMAEN, false>(
    registerSetBaseAddressValue);
  expectedValue = 0;
  EXPECT_EQ(getValueOfControlRegister2(), expectedValue);
}

TEST_F(SPIRegisterTest, setUnsetTXDMAEN) // NOLINT: Static storage warning.
{
  SPIRegisters<RegisterTypeHost>::setControlRegister2Bit<ControlRegister2Property::TXDMAEN, true>(
    registerSetBaseAddressValue);

  const auto numberOfShifts = UINT32_C(1);
  auto expectedValue = UINT32_C(0b1) << numberOfShifts;
  EXPECT_EQ(getValueOfControlRegister2(), expectedValue);

  SPIRegisters<RegisterTypeHost>::setControlRegister2Bit<ControlRegister2Property::TXDMAEN, false>(
    registerSetBaseAddressValue);
  expectedValue = 0;
  EXPECT_EQ(getValueOfControlRegister2(), expectedValue);
}

TEST_F(SPIRegisterTest, setUnsetSSOE) // NOLINT: Static storage warning.
{
  SPIRegisters<RegisterTypeHost>::setControlRegister2Bit<ControlRegister2Property::SSOE, true>(
    registerSetBaseAddressValue);

  const auto numberOfShifts = UINT32_C(2);
  auto expectedValue = UINT32_C(0b1) << numberOfShifts;
  EXPECT_EQ(getValueOfControlRegister2(), expectedValue);

  SPIRegisters<RegisterTypeHost>::setControlRegister2Bit<ControlRegister2Property::SSOE, false>(
    registerSetBaseAddressValue);
  expectedValue = 0;
  EXPECT_EQ(getValueOfControlRegister2(), expectedValue);
}

TEST_F(SPIRegisterTest, setUnsetFRF) // NOLINT: Static storage warning.
{
  SPIRegisters<RegisterTypeHost>::setControlRegister2Bit<ControlRegister2Property::FRF, true>(
    registerSetBaseAddressValue);

  const auto numberOfShifts = UINT32_C(4);
  auto expectedValue = UINT32_C(0b1) << numberOfShifts;
  EXPECT_EQ(getValueOfControlRegister2(), expectedValue);

  SPIRegisters<RegisterTypeHost>::setControlRegister2Bit<ControlRegister2Property::FRF, false>(
    registerSetBaseAddressValue);
  expectedValue = 0;
  EXPECT_EQ(getValueOfControlRegister2(), expectedValue);
}

TEST_F(SPIRegisterTest, setUnsetERRIE) // NOLINT: Static storage warning.
{
  SPIRegisters<RegisterTypeHost>::setControlRegister2Bit<ControlRegister2Property::ERRIE, true>(
    registerSetBaseAddressValue);

  const auto numberOfShifts = UINT32_C(5);
  auto expectedValue = UINT32_C(0b1) << numberOfShifts;
  EXPECT_EQ(getValueOfControlRegister2(), expectedValue);

  SPIRegisters<RegisterTypeHost>::setControlRegister2Bit<ControlRegister2Property::ERRIE, false>(
    registerSetBaseAddressValue);
  expectedValue = 0;
  EXPECT_EQ(getValueOfControlRegister2(), expectedValue);
}

TEST_F(SPIRegisterTest, setUnsetRXNEIE) // NOLINT: Static storage warning.
{
  SPIRegisters<RegisterTypeHost>::setControlRegister2Bit<ControlRegister2Property::RXNEIE, true>(
    registerSetBaseAddressValue);

  const auto numberOfShifts = UINT32_C(6);
  auto expectedValue = UINT32_C(0b1) << numberOfShifts;
  EXPECT_EQ(getValueOfControlRegister2(), expectedValue);

  SPIRegisters<RegisterTypeHost>::setControlRegister2Bit<ControlRegister2Property::RXNEIE, false>(
    registerSetBaseAddressValue);
  expectedValue = 0;
  EXPECT_EQ(getValueOfControlRegister2(), expectedValue);
}

TEST_F(SPIRegisterTest, setUnsetTXEIE) // NOLINT: Static storage warning.
{
  SPIRegisters<RegisterTypeHost>::setControlRegister2Bit<ControlRegister2Property::TXEIE, true>(
    registerSetBaseAddressValue);

  const auto numberOfShifts = UINT32_C(7);
  auto expectedValue = UINT32_C(0b1) << numberOfShifts;
  EXPECT_EQ(getValueOfControlRegister2(), expectedValue);

  SPIRegisters<RegisterTypeHost>::setControlRegister2Bit<ControlRegister2Property::TXEIE, false>(
    registerSetBaseAddressValue);
  expectedValue = 0;
  EXPECT_EQ(getValueOfControlRegister2(), expectedValue);
}
