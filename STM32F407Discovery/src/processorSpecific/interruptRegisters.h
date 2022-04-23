#ifndef SRC_PROCESSORSPECIFIC_INTERRUPTREGISTERS
#define SRC_PROCESSORSPECIFIC_INTERRUPTREGISTERS

#include "baseAddresses.h"
#include "targetSpecific/registers/registerType.h"

#include "utils/registerAccess.h"

#include <iostream>

template<typename RegisterAddressType>
class InterruptsRegisters
{
  struct Offsets
  {
    static constexpr RegisterType register0 = UINT32_C(0x00);
    static constexpr RegisterType register1 = UINT32_C(0x04);
    static constexpr RegisterType register2 = UINT32_C(0x08);
  };

  static constexpr auto numberOfInterrupts = 82;
  static constexpr auto numberOfPriorities = 16;

public:
  template<std::uint8_t irqNumber>
  requires(irqNumber <
           numberOfInterrupts) static void enable(const RegisterAddressType interruptSetEnableRegisterBaseAddress)
  {
    static constexpr auto numberOfBitsPerRegister = 32;
    static constexpr auto registerNumber = irqNumber / numberOfBitsPerRegister;
    static constexpr auto bitNumber = irqNumber % numberOfBitsPerRegister;

    if constexpr (registerNumber == 0)
      RegisterAccess<RegisterAddressType, RegisterAddressType>::regBitSet(
        interruptSetEnableRegisterBaseAddress + Offsets::register0, bitNumber);
    if constexpr (registerNumber == 1)
      RegisterAccess<RegisterAddressType, RegisterAddressType>::regBitSet(
        interruptSetEnableRegisterBaseAddress + Offsets::register1, bitNumber);
    else
      RegisterAccess<RegisterAddressType, RegisterAddressType>::regBitSet(
        interruptSetEnableRegisterBaseAddress + Offsets::register2, bitNumber);
  }

  template<std::uint8_t irqNumber>
  requires(irqNumber <
           numberOfInterrupts) static void disable(const RegisterAddressType interruptClearEnableRegisterBaseAddress)
  {
    static constexpr auto numberOfBitsPerRegister = 32;
    static constexpr auto registerNumber = irqNumber / numberOfBitsPerRegister;
    static constexpr auto bitNumber = irqNumber % numberOfBitsPerRegister;

    if constexpr (registerNumber == 0)
      RegisterAccess<RegisterAddressType, RegisterAddressType>::regBitClear(
        interruptClearEnableRegisterBaseAddress + Offsets::register0, bitNumber);
    if constexpr (registerNumber == 1)
      RegisterAccess<RegisterAddressType, RegisterAddressType>::regBitClear(
        interruptClearEnableRegisterBaseAddress + Offsets::register1, bitNumber);
    else
      RegisterAccess<RegisterAddressType, RegisterAddressType>::regBitClear(
        interruptClearEnableRegisterBaseAddress + Offsets::register2, bitNumber);
  }

  template<std::uint8_t irqNumber, std::uint8_t irqPriority>
  requires((irqNumber < numberOfInterrupts) &&
           (irqPriority <
            numberOfPriorities)) static void setPriority(const RegisterAddressType interruptPriorityBaseRegister)
  {
    static constexpr auto numberOfSectionsPerRegister = 4;
    static constexpr auto registerNumber = irqNumber / numberOfSectionsPerRegister;
    static constexpr auto registerSection = irqNumber % numberOfSectionsPerRegister;
    static const auto registerAddress = interruptPriorityBaseRegister + (registerNumber * numberOfSectionsPerRegister);
    static constexpr auto numberOfBitsPerSection = 8;
    static constexpr auto numberOfImplementedBits = 4;
    static constexpr std::uint8_t shifts =
      (numberOfBitsPerSection * registerSection) + (numberOfBitsPerSection - numberOfImplementedBits);

    static constexpr RegisterAddressType value = static_cast<RegisterAddressType>(irqPriority << shifts);
    RegisterAccess<RegisterAddressType, RegisterAddressType>::regSet(registerAddress, value);
  }
};

class InterruptsRegistersTarget
{
public:
public:
  template<std::uint8_t irqNumber>
  static void enable()
  {
    InterruptsRegisters<RegisterType>::enable<irqNumber>(BaseAddresses::nvicISER0);
  }

  template<std::uint8_t irqNumber>
  static void disable()
  {
    InterruptsRegisters<RegisterType>::disable<irqNumber>(BaseAddresses::nvicICER0);
  }

  template<std::uint8_t irqNumber, std::uint8_t irqPriority>
  static void setPriority()
  {
    InterruptsRegisters<RegisterType>::setPriority<irqNumber, irqPriority>(BaseAddresses::nvicIPR0);
  }
};

#endif /* SRC_PROCESSORSPECIFIC_INTERRUPTREGISTERS */
