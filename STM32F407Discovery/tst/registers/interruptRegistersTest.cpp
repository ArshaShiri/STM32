#include <algorithm>
#include <array>

#include <gtest/gtest.h>

#include "processorSpecific/interruptRegisters.h"
#include "targetSpecific/registers/registerType.h"

class InterruptsRegistersTest : public ::testing::Test
{
protected:
  using RegisterTypeHost = std::uint64_t;

  void SetUp() override
  {
    std::fill(interruptRegisterSet.begin(), interruptRegisterSet.end(), 0);
    registerSetBaseAddressValue = reinterpret_cast<RegisterTypeHost>(
      interruptRegisterSet.data()); // NOLINT: Ignored reinterpret_cast by clang-tidy.

    std::fill(irqPriorityRegisterSet.begin(), irqPriorityRegisterSet.end(), 0);
    irqPriorityRegisterSetBaseAddressValue = reinterpret_cast<RegisterTypeHost>(
      irqPriorityRegisterSet.data()); // NOLINT: Ignored reinterpret_cast by clang-tidy.
  }

  [[nodiscard]] RegisterType getValueOfInterruptRegister(size_t registerNumber) const
  {
    return interruptRegisterSet.at(registerNumber);
  }
  [[nodiscard]] RegisterType getValueOfIRQRegister(size_t registerNumber) const
  {
    return irqPriorityRegisterSet.at(registerNumber);
  }

  RegisterTypeHost registerSetBaseAddressValue{ 0 };
  static constexpr auto numberOfInterruptRegisters{ 3 };
  std::array<RegisterType, numberOfInterruptRegisters> interruptRegisterSet{};

  RegisterTypeHost irqPriorityRegisterSetBaseAddressValue{ 0 };
  static constexpr auto numberOfIRQPriorityRegisters{ 60 };
  std::array<RegisterType, numberOfIRQPriorityRegisters> irqPriorityRegisterSet{};
};

TEST_F(InterruptsRegistersTest, setIRQInRegsiter0) // NOLINT: Static storage warning.
{
  const auto irqNumber = 5;
  InterruptsRegisters<RegisterTypeHost>::enable<irqNumber>(registerSetBaseAddressValue);

  const auto numberOfShifts = 5;
  auto expectedValue = 1 << numberOfShifts;
  EXPECT_EQ(expectedValue, getValueOfInterruptRegister(0));

  expectedValue = 0;
  InterruptsRegisters<RegisterTypeHost>::disable<irqNumber>(registerSetBaseAddressValue);
  EXPECT_EQ(expectedValue, getValueOfInterruptRegister(0));
}

TEST_F(InterruptsRegistersTest, setIRQInRegsiter1) // NOLINT: Static storage warning.
{
  const auto irqNumber = 54;
  InterruptsRegisters<RegisterTypeHost>::enable<irqNumber>(registerSetBaseAddressValue);

  const auto numberOfShifts = 22;
  auto expectedValue = 1 << numberOfShifts;
  EXPECT_EQ(expectedValue, getValueOfInterruptRegister(1));

  expectedValue = 0;
  InterruptsRegisters<RegisterTypeHost>::disable<irqNumber>(registerSetBaseAddressValue);
  EXPECT_EQ(expectedValue, getValueOfInterruptRegister(1));
}

TEST_F(InterruptsRegistersTest, setIRQInRegsiter2) // NOLINT: Static storage warning.
{
  const auto irqNumber = 81;
  InterruptsRegisters<RegisterTypeHost>::enable<irqNumber>(registerSetBaseAddressValue);

  const auto numberOfShifts = 17;
  auto expectedValue = 1 << numberOfShifts;
  EXPECT_EQ(expectedValue, getValueOfInterruptRegister(2));

  expectedValue = 0;
  InterruptsRegisters<RegisterTypeHost>::disable<irqNumber>(registerSetBaseAddressValue);
  EXPECT_EQ(expectedValue, getValueOfInterruptRegister(2));
}

TEST_F(InterruptsRegistersTest, setIRQ1InterruptPriority) // NOLINT: Static storage warning.
{
  const auto irqNumber = 1;
  const auto irqPriority = 15;
  InterruptsRegisters<RegisterTypeHost>::setPriority<irqNumber, irqPriority>(irqPriorityRegisterSetBaseAddressValue);

  const auto numberOfShifts = 12;
  auto expectedValue = irqPriority << numberOfShifts;
  EXPECT_EQ(expectedValue, getValueOfIRQRegister(0));
}

TEST_F(InterruptsRegistersTest, setIRQ27InterruptPriority) // NOLINT: Static storage warning.
{
  const std::uint8_t irqNumber = 27;
  const std::uint8_t irqPriority = 14;
  InterruptsRegisters<RegisterTypeHost>::setPriority<irqNumber, irqPriority>(irqPriorityRegisterSetBaseAddressValue);

  const auto numberOfShifts = 28;
  auto expectedValue = irqPriority << numberOfShifts;
  EXPECT_EQ(expectedValue, getValueOfIRQRegister(6));
}
