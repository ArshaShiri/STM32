#include <algorithm>
#include <array>

#include <gtest/gtest.h>

#include "targetSpecific/registers/extiRegisters.h"
#include "targetSpecific/registers/registerType.h"

class EXTIRegisterTest : public ::testing::Test
{
protected:
  using RegisterTypeHost = std::uint64_t;

  void SetUp() override
  {
    std::fill(extiRegisterSet.begin(), extiRegisterSet.end(), 0);
    registerSetBaseAddressValue =
      reinterpret_cast<RegisterTypeHost>(extiRegisterSet.data()); // NOLINT: Ignored reinterpret_cast by clang-tidy.
  }

  [[nodiscard]] RegisterType getValueOfInterruptMaskRegister() const { return extiRegisterSet.at(0); }
  [[nodiscard]] RegisterType getValueOfEventtMaskRegister() const { return extiRegisterSet.at(1); }
  [[nodiscard]] RegisterType getValueOfRisingTriggerRegister() const { return extiRegisterSet.at(2); }
  [[nodiscard]] RegisterType getValueOfFallingTriggerRegister() const { return extiRegisterSet.at(3); }
  [[nodiscard]] RegisterType getSoftwareInterruptEventRegister() const { return extiRegisterSet.at(4); }
  [[nodiscard]] RegisterType getValueOfPendingRegister() const { return extiRegisterSet.at(5); }

  RegisterTypeHost registerSetBaseAddressValue{ 0 };
  static constexpr auto numberOfEXTIRegisters{ 6 };
  std::array<RegisterType, numberOfEXTIRegisters> extiRegisterSet{};
};

TEST_F(EXTIRegisterTest, setInterruptMask) // NOLINT: Static storage warning.
{
  constexpr auto lineNumber = 5;

  EXTIRegisters<RegisterTypeHost>::setInterruptMaskRegister<lineNumber, true>(registerSetBaseAddressValue);
  auto expectedValue = UINT32_C(0b01) << lineNumber;
  EXPECT_EQ(expectedValue, getValueOfInterruptMaskRegister());

  EXTIRegisters<RegisterTypeHost>::setInterruptMaskRegister<lineNumber, false>(registerSetBaseAddressValue);
  expectedValue = 0;
  EXPECT_EQ(0, getValueOfInterruptMaskRegister());
}

TEST_F(EXTIRegisterTest, setEventMask) // NOLINT: Static storage warning.
{
  constexpr auto lineNumber = 7;

  EXTIRegisters<RegisterTypeHost>::setEventMaskRegister<lineNumber, true>(registerSetBaseAddressValue);
  auto expectedValue = UINT32_C(0b01) << lineNumber;
  EXPECT_EQ(expectedValue, getValueOfEventtMaskRegister());

  EXTIRegisters<RegisterTypeHost>::setEventMaskRegister<lineNumber, false>(registerSetBaseAddressValue);
  expectedValue = 0;
  EXPECT_EQ(0, getValueOfEventtMaskRegister());
}

TEST_F(EXTIRegisterTest, setRisingTrigger) // NOLINT: Static storage warning.
{
  constexpr auto lineNumber = 3;

  EXTIRegisters<RegisterTypeHost>::setRisingTriggerRegister<lineNumber, true>(registerSetBaseAddressValue);
  auto expectedValue = UINT32_C(0b01) << lineNumber;
  EXPECT_EQ(expectedValue, getValueOfRisingTriggerRegister());

  EXTIRegisters<RegisterTypeHost>::setRisingTriggerRegister<lineNumber, false>(registerSetBaseAddressValue);
  expectedValue = 0;
  EXPECT_EQ(0, getValueOfRisingTriggerRegister());
}

TEST_F(EXTIRegisterTest, setFallingTrigger) // NOLINT: Static storage warning.
{
  constexpr auto lineNumber = 18;

  EXTIRegisters<RegisterTypeHost>::setFallingTriggerRegister<lineNumber, true>(registerSetBaseAddressValue);
  auto expectedValue = UINT32_C(0b01) << lineNumber;
  EXPECT_EQ(expectedValue, getValueOfFallingTriggerRegister());

  EXTIRegisters<RegisterTypeHost>::setFallingTriggerRegister<lineNumber, false>(registerSetBaseAddressValue);
  expectedValue = 0;
  EXPECT_EQ(0, getValueOfFallingTriggerRegister());
}

TEST_F(EXTIRegisterTest, setSoftwareInterruptEvent) // NOLINT: Static storage warning.
{
  constexpr auto lineNumber = 22;

  EXTIRegisters<RegisterTypeHost>::setSoftwareInterruptEventRegister<lineNumber, true>(registerSetBaseAddressValue);
  auto expectedValue = UINT32_C(0b01) << lineNumber;
  EXPECT_EQ(expectedValue, getSoftwareInterruptEventRegister());

  EXTIRegisters<RegisterTypeHost>::setSoftwareInterruptEventRegister<lineNumber, false>(registerSetBaseAddressValue);
  expectedValue = 0;
  EXPECT_EQ(0, getSoftwareInterruptEventRegister());
}

TEST_F(EXTIRegisterTest, setPending) // NOLINT: Static storage warning.
{
  constexpr auto lineNumber = 0;

  EXTIRegisters<RegisterTypeHost>::setPendingRegister<lineNumber, true>(registerSetBaseAddressValue);
  auto expectedValue = UINT32_C(0b01) << lineNumber;
  EXPECT_EQ(expectedValue, getValueOfPendingRegister());

  EXTIRegisters<RegisterTypeHost>::setPendingRegister<lineNumber, false>(registerSetBaseAddressValue);
  expectedValue = 0;
  EXPECT_EQ(0, getValueOfPendingRegister());
}
