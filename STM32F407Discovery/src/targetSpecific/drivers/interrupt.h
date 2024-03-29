#ifndef STM32F407DISCOVERY_SRC_TARGETSPECIFIC_DRIVERS_INTERRUPT
#define STM32F407DISCOVERY_SRC_TARGETSPECIFIC_DRIVERS_INTERRUPT

#include "processorSpecific/interruptRegisters.h"

#include "targetSpecific/registers/extiRegisters.h"
#include "targetSpecific/registers/rccRegisters.h"
#include "targetSpecific/registers/syscfgRegisters.h"

#include "utils/helpers.h"

enum class IRQ
{
  EXTI0,
  EXTI1,
  EXTI2,
  EXTI3,
  EXTI4,
  EXTI9_5,
  EXTI15_10,
  SPI1,
  SPI2,
  SPI3
};

class Interrupt
{
public:
  template<PinType pin, bool set>
  static void setEXTIInterruptMaskRegister()
  {
    EXTIRegisters<RegisterType>::setInterruptMaskRegister<pin, set>(BaseAddresses::exti);
  }

  template<PinType pin, bool set>
  static void setEXTIEventMaskRegister()
  {
    EXTIRegisters<RegisterType>::setEventMaskRegister<pin, set>(BaseAddresses::exti);
  }

  template<PinType pin, bool set>
  static void setEXTIRisingTriggerRegister()
  {
    EXTIRegisters<RegisterType>::setRisingTriggerRegister<pin, set>(BaseAddresses::exti);
    EXTIRegisters<RegisterType>::setFallingTriggerRegister<pin, false>(BaseAddresses::exti);
  }

  template<PinType pin, bool set>
  static void setEXTIFallingTriggerRegister()
  {
    EXTIRegisters<RegisterType>::setFallingTriggerRegister<pin, set>(BaseAddresses::exti);
    EXTIRegisters<RegisterType>::setRisingTriggerRegister<pin, false>(BaseAddresses::exti);
  }

  template<PinType pin, bool set>
  static void setEXTISoftwareInterruptEventRegister()
  {
    EXTIRegisters<RegisterType>::setSoftwareInterruptEventRegister<pin, set>(BaseAddresses::exti);
  }

  template<PinType pin, bool set>
  static void setEXTIPendingRegister()
  {
    EXTIRegisters<RegisterType>::setPendingRegister<pin, set>(BaseAddresses::exti);
  }

  template<bool set>
  static void setExternalInterruptClock()
  {
    RCCRegistersTarget::setPeripheralOnAPB2<PeripheralAPB2::SYSCFG, set>();
  }

  template<InputPort inputPort, PinType pin>
  static void setExternalInterruptConfigurationRegister()
  {
    SYSCFGRegisters<RegisterType>::setExternalInterruptConfigurationRegister<inputPort, pin>(BaseAddresses::syscfg);
  }

  template<IRQ irqNumber>
  static void enableIRQ()
  {
    using namespace processor;
    InterruptsRegisters<RegisterType>::enable<irqToPositionInVectorTable.at(irqNumber)>(
      processor::BaseAddresses::nvicISER0);
  }

  template<IRQ irqNumber>
  static void disableIRQ()
  {
    using namespace processor;
    InterruptsRegisters<RegisterType>::disable<irqToPositionInVectorTable.at(irqNumber)>(
      processor::BaseAddresses::nvicICER0);
  }

  template<IRQ irqNumber, std::uint8_t irqPriority>
  static void setIRQPriority()
  {
    using namespace processor;
    InterruptsRegisters<RegisterType>::setPriority<irqToPositionInVectorTable.at(irqNumber), irqPriority>(
      processor::BaseAddresses::nvicIPR0);
  }

private:
  static constexpr StaticMap<IRQ, std::uint8_t, 10> irqToPositionInVectorTable{ { { { IRQ::EXTI0, 6 },
                                                                                    { IRQ::EXTI1, 7 },
                                                                                    { IRQ::EXTI2, 8 },
                                                                                    { IRQ::EXTI3, 9 },
                                                                                    { IRQ::EXTI4, 10 },
                                                                                    { IRQ::EXTI9_5, 23 },
                                                                                    { IRQ::SPI1, 35 },
                                                                                    { IRQ::SPI2, 36 },
                                                                                    { IRQ::EXTI15_10, 40 },
                                                                                    { IRQ::SPI3, 54 } } } };
};

#endif /* STM32F407DISCOVERY_SRC_TARGETSPECIFIC_DRIVERS_INTERRUPT */
