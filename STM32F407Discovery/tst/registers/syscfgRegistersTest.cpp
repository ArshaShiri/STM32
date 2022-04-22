#include <algorithm>
#include <array>

#include <gtest/gtest.h>

#include "targetSpecific/registers/registerType.h"
#include "targetSpecific/registers/syscfgRegisters.h"

class EXTIRegisterTest : public ::testing::Test
{
protected:
  using RegisterTypeHost = std::uint64_t;

  void SetUp() override
  {
    std::fill(syscfgRegisterSet.begin(), syscfgRegisterSet.end(), 0);
    registerSetBaseAddressValue =
      reinterpret_cast<RegisterTypeHost>(syscfgRegisterSet.data()); // NOLINT: Ignored reinterpret_cast by clang-tidy.
  }

  [[nodiscard]] RegisterType getValueOfEXTICR1Register() const { return syscfgRegisterSet.at(2); }
  [[nodiscard]] RegisterType getValueOfEXTICR2Register() const { return syscfgRegisterSet.at(3); }
  [[nodiscard]] RegisterType getValueOfEXTICR3Register() const { return syscfgRegisterSet.at(4); }
  [[nodiscard]] RegisterType getValueOfEXTICR4Register() const { return syscfgRegisterSet.at(5); }

  RegisterTypeHost registerSetBaseAddressValue{ 0 };
  static constexpr auto numberOfSYSCFGegisters{ 7 };
  std::array<RegisterType, numberOfSYSCFGegisters> syscfgRegisterSet{};
};

TEST_F(EXTIRegisterTest, setExternalInterruptConfigurationRegister1) // NOLINT: Static storage warning.
{
  constexpr auto pinNumber = 3;
  SYSCFGRegisters<RegisterTypeHost>::setExternalInterruptConfigurationRegister<InputPort::PD, pinNumber>(
    registerSetBaseAddressValue);
  const auto numerOfShifts = 12;
  const auto expectedValue = UINT32_C(0b0011) << numerOfShifts;
  EXPECT_EQ(expectedValue, getValueOfEXTICR1Register());
}

TEST_F(EXTIRegisterTest, setExternalInterruptConfigurationRegister2) // NOLINT: Static storage warning.
{
  constexpr auto pinNumber = 5;
  SYSCFGRegisters<RegisterTypeHost>::setExternalInterruptConfigurationRegister<InputPort::PH, pinNumber>(
    registerSetBaseAddressValue);
  const auto numerOfShifts = 4;
  const auto expectedValue = UINT32_C(0b0111) << numerOfShifts;
  EXPECT_EQ(expectedValue, getValueOfEXTICR2Register());
}

TEST_F(EXTIRegisterTest, setExternalInterruptConfigurationRegister3) // NOLINT: Static storage warning.
{
  constexpr auto pinNumber = 8;
  SYSCFGRegisters<RegisterTypeHost>::setExternalInterruptConfigurationRegister<InputPort::PE, pinNumber>(
    registerSetBaseAddressValue);
  const auto numerOfShifts = 0;
  const auto expectedValue = UINT32_C(0b0100) << numerOfShifts;
  EXPECT_EQ(expectedValue, getValueOfEXTICR3Register());
}

TEST_F(EXTIRegisterTest, setExternalInterruptConfigurationRegister4) // NOLINT: Static storage warning.
{
  constexpr auto pinNumber = 13;
  SYSCFGRegisters<RegisterTypeHost>::setExternalInterruptConfigurationRegister<InputPort::PB, pinNumber>(
    registerSetBaseAddressValue);
  const auto numerOfShifts = 4;
  const auto expectedValue = UINT32_C(0b0001) << numerOfShifts;
  EXPECT_EQ(expectedValue, getValueOfEXTICR4Register());
}
