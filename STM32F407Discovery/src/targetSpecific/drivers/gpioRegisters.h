#ifndef GPIOREGISTERS
#define GPIOREGISTERS

#include "targetSpecific/registerType.h"
#include "targetSpecific/registersBaseAddresses.h"

#include "utils/helpers.h"
#include "utils/registerAccess.h"

enum class PortMode
{
  input,
  generalpurposeOutput,
  alternateFunction,
  analog
};

template<typename RegisterAddressType>
class GPIORegisters
{
  struct Offsets
  {
    static constexpr RegisterType moder = UINT32_C(0x00);
    static constexpr RegisterType otyper = UINT32_C(0x04);
    static constexpr RegisterType ospeedr = UINT32_C(0x08);
    static constexpr RegisterType pupdr = UINT32_C(0x0C);
    static constexpr RegisterType idr = UINT32_C(0x10);
    static constexpr RegisterType odr = UINT32_C(0x14);
    static constexpr RegisterType bsrr = UINT32_C(0x18);
    static constexpr RegisterType lckr = UINT32_C(0x1C);
    static constexpr RegisterType afrl = UINT32_C(0x20);
    static constexpr RegisterType afrh = UINT32_C(0x24);
  };

public:
  template<PortMode mode, PinType pinNumber>
  static void setPortMode(const RegisterAddressType baseRegisterAddress)
  {
    static constexpr auto numberOfPins = 16;
    static_assert(pinNumber < numberOfPins, "Pin number is not supported!");

    const auto portModeValue = portModeToValue.at(mode);
    const auto numberOfShifts = pinNumber * 2;
    RegisterAccess<RegisterAddressType, RegisterAddressType>::regSet(baseRegisterAddress + Offsets::moder,
                                                                     portModeValue << numberOfShifts);
  }

private:
  static constexpr StaticMap<PortMode, RegisterType, 4> portModeToValue{ { { { PortMode::input, 0b00 },
                                                                             { PortMode::generalpurposeOutput, 0b01 },
                                                                             { PortMode::alternateFunction, 0b10 },
                                                                             { PortMode::analog, 0b11 } } } };
};

class GPIORegs
{
public:
  template<PortMode mode, PinType pinNumber>
  static void setPortMode(const RegisterType baseRegisterAddress)
  {
    GPIORegisters<RegisterType>::setPortMode<mode, pinNumber>(baseRegisterAddress);
  }
};

#endif /* GPIOREGISTERS */
