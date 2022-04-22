#ifndef SRC_TARGETSPECIFIC_REGISTERS_EXTIREGISTERS
#define SRC_TARGETSPECIFIC_REGISTERS_EXTIREGISTERS

#include "registerType.h"
#include "registersBaseAddresses.h"

#include "utils/helpers.h"
#include "utils/registerAccess.h"

template<typename RegisterAddressType>
class EXTIRegisters
{
  struct Offsets
  {
    static constexpr RegisterType imr = UINT32_C(0x00);
    static constexpr RegisterType emr = UINT32_C(0x04);
    static constexpr RegisterType rtsr = UINT32_C(0x08);
    static constexpr RegisterType ftsr = UINT32_C(0x0C);
    static constexpr RegisterType swier = UINT32_C(0x10);
    static constexpr RegisterType pr = UINT32_C(0x14);
  };

  static constexpr auto numerOfLines = 23;

public:
  template<std::uint8_t line, bool set>
  requires(line < numerOfLines) static void setInterruptMaskRegister(const RegisterAddressType extiBaseAddress)
  {
    doSet<line, set, Offsets::imr>(extiBaseAddress);
  }

  template<std::uint8_t line, bool set>
  requires(line < numerOfLines) static void setEventMaskRegister(const RegisterAddressType extiBaseAddress)
  {
    doSet<line, set, Offsets::emr>(extiBaseAddress);
  }

  template<std::uint8_t line, bool set>
  requires(line < numerOfLines) static void setRisingTriggerRegister(const RegisterAddressType extiBaseAddress)
  {
    doSet<line, set, Offsets::rtsr>(extiBaseAddress);
  }

  template<std::uint8_t line, bool set>
  requires(line < numerOfLines) static void setFallingTriggerRegister(const RegisterAddressType extiBaseAddress)
  {
    doSet<line, set, Offsets::ftsr>(extiBaseAddress);
  }

  template<std::uint8_t line, bool set>
  requires(line < numerOfLines) static void setSoftwareInterruptEventRegister(const RegisterAddressType extiBaseAddress)
  {
    doSet<line, set, Offsets::swier>(extiBaseAddress);
  }

  template<std::uint8_t line, bool set>
  requires(line < numerOfLines) static void setPendingRegister(const RegisterAddressType extiBaseAddress)
  {
    doSet<line, set, Offsets::pr>(extiBaseAddress);
  }

private:
  template<std::uint8_t line, bool set, std::uint32_t offset>
  static void doSet(const RegisterAddressType extiBaseAddress)
  {
    if constexpr (set)
      RegisterAccess<RegisterAddressType, RegisterAddressType>::regBitSet(extiBaseAddress + offset, line);
    else
      RegisterAccess<RegisterAddressType, RegisterAddressType>::regBitClear(extiBaseAddress + offset, line);
  }
};

class EXTIRegistersTarget
{
public:
  template<std::uint8_t line, bool set>
  static void setInterruptMaskRegister()
  {
    EXTIRegisters<RegisterType>::setInterruptMaskRegister<line, set>(extiBaseAddress);
  }

  template<std::uint8_t line, bool set>
  static void setEventMaskRegister()
  {
    EXTIRegisters<RegisterType>::setEventMaskRegister<line, set>(extiBaseAddress);
  }

  template<std::uint8_t line, bool set>
  static void setRisingTriggerRegister()
  {
    EXTIRegisters<RegisterType>::setRisingTriggerRegister<line, set>(extiBaseAddress);
  }

  template<std::uint8_t line, bool set>
  static void setFallingTriggerRegister()
  {
    EXTIRegisters<RegisterType>::setFallingTriggerRegister<line, set>(extiBaseAddress);
  }

  template<std::uint8_t line, bool set>
  static void setSoftwareInterruptEventRegister()
  {
    EXTIRegisters<RegisterType>::setSoftwareInterruptEventRegister<line, set>(extiBaseAddress);
  }

  template<std::uint8_t line, bool set>
  static void setPendingRegister()
  {
    EXTIRegisters<RegisterType>::setPendingRegister<line, set>(extiBaseAddress);
  }

private:
  static constexpr auto extiBaseAddress = BaseAddresses::exti;
};

#endif /* SRC_TARGETSPECIFIC_REGISTERS_EXTIREGISTERS */
