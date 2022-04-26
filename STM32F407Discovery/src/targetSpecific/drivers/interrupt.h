#ifndef SRC_TARGETSPECIFIC_DRIVERS_INTERRUPT
#define SRC_TARGETSPECIFIC_DRIVERS_INTERRUPT

#include "targetSpecific/registers/extiRegisters.h"

class Interrupt
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
    EXTIRegisters<RegisterType>::setFallingTriggerRegister<line, false>(extiBaseAddress);
  }

  template<std::uint8_t line, bool set>
  static void setFallingTriggerRegister()
  {
    EXTIRegisters<RegisterType>::setFallingTriggerRegister<line, set>(extiBaseAddress);
    EXTIRegisters<RegisterType>::setRisingTriggerRegister<line, false>(extiBaseAddress);
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

#endif /* SRC_TARGETSPECIFIC_DRIVERS_INTERRUPT */
