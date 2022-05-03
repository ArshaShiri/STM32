#ifndef SRC_TARGETSPECIFIC_REGISTERS_SYSCFGREGISTERS
#define SRC_TARGETSPECIFIC_REGISTERS_SYSCFGREGISTERS

#include "registerType.h"
#include "registersBaseAddresses.h"

#include "utils/helpers.h"
#include "utils/registerAccess.h"

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

  static constexpr auto numberOfPins = 16;

public:
  template<InputPort inputPort, PinType pin>
  requires(pin < numberOfPins) static void setExternalInterruptConfigurationRegister(
    const RegisterAddressType syscfgBaseAddress)
  {
    static constexpr auto numberOfEXTIRegisters = 4;
    static constexpr auto regNumer = pin / numberOfEXTIRegisters;

    if constexpr (regNumer == 0)
      setExternalInterruptConfigurationRegister1<inputPort, pin>(syscfgBaseAddress);
    if constexpr (regNumer == 1)
      setExternalInterruptConfigurationRegister2<inputPort, pin>(syscfgBaseAddress);
    if constexpr (regNumer == 2)
      setExternalInterruptConfigurationRegister3<inputPort, pin>(syscfgBaseAddress);
    else
      setExternalInterruptConfigurationRegister4<inputPort, pin>(syscfgBaseAddress);
  }

private:
  template<InputPort inputPort, PinType pin>
  static void setExternalInterruptConfigurationRegister1(const RegisterAddressType syscfgBaseAddress)
  {
    doSet<inputPortToBits.at(inputPort), pin, Offsets::exticr1>(syscfgBaseAddress);
  }

  template<InputPort inputPort, PinType pin>
  static void setExternalInterruptConfigurationRegister2(const RegisterAddressType syscfgBaseAddress)
  {
    doSet<inputPortToBits.at(inputPort), pin, Offsets::exticr2>(syscfgBaseAddress);
  }

  template<InputPort inputPort, PinType pin>
  static void setExternalInterruptConfigurationRegister3(const RegisterAddressType syscfgBaseAddress)
  {
    doSet<inputPortToBits.at(inputPort), pin, Offsets::exticr3>(syscfgBaseAddress);
  }

  template<InputPort inputPort, PinType pin>
  static void setExternalInterruptConfigurationRegister4(const RegisterAddressType syscfgBaseAddress)
  {
    doSet<inputPortToBits.at(inputPort), pin, Offsets::exticr4>(syscfgBaseAddress);
  }

  template<RegisterType value, PinType pin, std::uint32_t offset>
  static void doSet(const RegisterAddressType syscfgBaseAddress)
  {
    constexpr auto numberOfEXTIsInEachConfigRegister = 4;
    constexpr auto extiNumber = pin % numberOfEXTIsInEachConfigRegister;
    constexpr auto numberOfShiftsPerEXTI = 4;
    RegisterAccess<RegisterAddressType, RegisterAddressType>::regSet(syscfgBaseAddress + offset,
                                                                     value << extiNumber * numberOfShiftsPerEXTI);
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

#endif /* SRC_TARGETSPECIFIC_REGISTERS_SYSCFGREGISTERS */
