#ifndef SRC_TARGETSPECIFIC_REGISTERS_SYSCFGREGISTERS
#define SRC_TARGETSPECIFIC_REGISTERS_SYSCFGREGISTERS

#include "registerType.h"
#include "registersBaseAddresses.h"

#include "utils/helpers.h"
#include "utils/registerAccess.h"

#include <iostream>

enum class InputPort
{
  PA,
  PB,
  PC,
  PD,
  PE,
  PF,
  PG,
  PH,
  PI
};

template<typename RegisterAddressType>
class SYSCFGRegisters
{
  struct Offsets
  {
    // TODO Make the type to be RegisterAddressType
    static constexpr RegisterType memrmp = UINT32_C(0x00);
    static constexpr RegisterType pmc = UINT32_C(0x04);
    static constexpr RegisterType exticr1 = UINT32_C(0x08);
    static constexpr RegisterType exticr2 = UINT32_C(0x0C);
    static constexpr RegisterType exticr3 = UINT32_C(0x10);
    static constexpr RegisterType exticr4 = UINT32_C(0x14);
    static constexpr RegisterType cmpcr = UINT32_C(0x20);
  };

  static constexpr auto exti1PinLowerBound = 0;
  static constexpr auto exti1PinUpperBound = 3;

  static constexpr auto exti2PinLowerBound = 4;
  static constexpr auto exti2PinUpperBound = 7;

  static constexpr auto exti3PinLowerBound = 8;
  static constexpr auto exti3PinUpperBound = 11;

  static constexpr auto exti4PinLowerBound = 12;
  static constexpr auto exti4PinUpperBound = 15;

public:
  template<InputPort inputPort, PinType pin>
  requires((exti1PinLowerBound <= pin) &&
           (pin <= exti1PinUpperBound)) static void setExternalInterruptConfigurationRegister1(const RegisterAddressType
                                                                                                 syscfgBaseAddress)
  {
    doSet<inputPortToBits.at(inputPort), pin, Offsets::exticr1>(syscfgBaseAddress);
  }

  template<InputPort inputPort, PinType pin>
  requires((exti2PinLowerBound <= pin) &&
           (pin <= exti2PinUpperBound)) static void setExternalInterruptConfigurationRegister2(const RegisterAddressType
                                                                                                 syscfgBaseAddress)
  {
    doSet<inputPortToBits.at(inputPort), pin, Offsets::exticr2>(syscfgBaseAddress);
  }

  template<InputPort inputPort, PinType pin>
  requires((exti3PinLowerBound <= pin) &&
           (pin <= exti3PinUpperBound)) static void setExternalInterruptConfigurationRegister3(const RegisterAddressType
                                                                                                 syscfgBaseAddress)
  {
    doSet<inputPortToBits.at(inputPort), pin, Offsets::exticr3>(syscfgBaseAddress);
  }

  template<InputPort inputPort, PinType pin>
  requires((exti4PinLowerBound <= pin) &&
           (pin <= exti4PinUpperBound)) static void setExternalInterruptConfigurationRegister4(const RegisterAddressType
                                                                                                 syscfgBaseAddress)
  {
    doSet<inputPortToBits.at(inputPort), pin, Offsets::exticr4>(syscfgBaseAddress);
  }


private:
  template<RegisterType value, PinType pin, std::uint32_t offset>
  static void doSet(const RegisterAddressType syscfgBaseAddress)
  {
    constexpr auto numberOfEXTIsInEachConfigRegister = 4;
    constexpr auto extiNumbner = pin % numberOfEXTIsInEachConfigRegister;
    constexpr auto numberOfShiftsPerEXTI = 4;
    RegisterAccess<RegisterAddressType, RegisterAddressType>::regSet(syscfgBaseAddress + offset,
                                                                     value << extiNumbner * numberOfShiftsPerEXTI);
  }

  static constexpr StaticMap<InputPort, RegisterType, 9> inputPortToBits{ { { { InputPort::PA, 0b0000 },
                                                                              { InputPort::PB, 0b0001 },
                                                                              { InputPort::PC, 0b0010 },
                                                                              { InputPort::PD, 0b0011 },
                                                                              { InputPort::PE, 0b0100 },
                                                                              { InputPort::PF, 0b0101 },
                                                                              { InputPort::PG, 0b0110 },
                                                                              { InputPort::PH, 0b0111 },
                                                                              { InputPort::PI, 0b1000 } } } };
};

class SYSCFGRegistersTarget
{
public:
  template<InputPort inputPort, PinType pin>
  static void setExternalInterruptConfigurationRegister1()
  {
    SYSCFGRegisters<RegisterType>::setExternalInterruptConfigurationRegister1<inputPort, pin>(syscfgBaseAddress);
  }

  template<InputPort inputPort, PinType pin>
  static void setExternalInterruptConfigurationRegister2()
  {
    SYSCFGRegisters<RegisterType>::setExternalInterruptConfigurationRegister2<inputPort, pin>(syscfgBaseAddress);
  }

  template<InputPort inputPort, PinType pin>
  static void setExternalInterruptConfigurationRegister3()
  {
    SYSCFGRegisters<RegisterType>::setExternalInterruptConfigurationRegister3<inputPort, pin>(syscfgBaseAddress);
  }

  template<InputPort inputPort, PinType pin>
  static void setExternalInterruptConfigurationRegister4()
  {
    SYSCFGRegisters<RegisterType>::setExternalInterruptConfigurationRegister4<inputPort, pin>(syscfgBaseAddress);
  }

private:
  static constexpr auto syscfgBaseAddress = BaseAddresses::syscfg;
};


#endif /* SRC_TARGETSPECIFIC_REGISTERS_SYSCFGREGISTERS */
