#ifndef STM32F407DISCOVERY_SRC_TARGETSPECIFIC_REGISTERS_GPIOREGISTERS
#define STM32F407DISCOVERY_SRC_TARGETSPECIFIC_REGISTERS_GPIOREGISTERS

#include "registerType.h"
#include "registersBaseAddresses.h"

#include "utils/helpers.h"
#include "utils/registerAccess.h"

enum class PortMode : std::uint8_t
{
  input,
  generalpurposeOutput,
  alternateFunction,
  analog
};

enum class OutputType : bool
{
  pushPull,
  openDrain
};

enum class OutputSpeed : std::uint8_t
{
  low,
  medium,
  high,
  veryHigh
};

enum class PullupPullDownControl : std::uint8_t
{
  noPullupPullDown,
  pullup,
  pullDown
};

enum class AlternateFunction : std::uint8_t
{
  af0,
  af1,
  af2,
  af3,
  af4,
  af5,
  af6,
  af7,
  af8,
  af9,
  af10,
  af11,
  af12,
  af13,
  af14,
  af15
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
    static_assert(pinNumber < numberOfPins, "Pin number is not supported!");

    constexpr auto portModeValue = portModeToValue.at(mode);
    static constexpr auto shiftPerPin = 2;
    constexpr auto numberOfShifts = pinNumber * shiftPerPin;
    RegisterAccess<RegisterAddressType, RegisterAddressType>::regOverride(baseRegisterAddress + Offsets::moder,
                                                                          portModeValue << numberOfShifts);
  }

  template<OutputType type, PinType pinNumber>
  static void setOutputType(const RegisterAddressType baseRegisterAddress)
  {
    static_assert(pinNumber < numberOfPins, "Pin number is not supported!");

    constexpr auto outputTypeValue = outputTypeToValue.at(type);
    RegisterAccess<RegisterAddressType, RegisterAddressType>::regOverride(baseRegisterAddress + Offsets::otyper,
                                                                          outputTypeValue << pinNumber);
  }

  template<OutputSpeed speed, PinType pinNumber>
  static void setOutputSpeed(const RegisterAddressType baseRegisterAddress)
  {
    static_assert(pinNumber < numberOfPins, "Pin number is not supported!");

    constexpr auto outputSpeedValue = outputSpeedToValue.at(speed);
    static constexpr auto shiftPerPin = 2;
    constexpr auto numberOfShifts = pinNumber * shiftPerPin;
    RegisterAccess<RegisterAddressType, RegisterAddressType>::regOverride(baseRegisterAddress + Offsets::ospeedr,
                                                                          outputSpeedValue << numberOfShifts);
  }

  template<PullupPullDownControl type, PinType pinNumber>
  static void setPullupPullDown(const RegisterAddressType baseRegisterAddress)
  {
    static_assert(pinNumber < numberOfPins, "Pin number is not supported!");

    constexpr auto pullupPullDownValue = pullupPullDownControlToValue.at(type);
    static constexpr auto shiftPerPin = 2;
    constexpr auto numberOfShifts = pinNumber * shiftPerPin;
    RegisterAccess<RegisterAddressType, RegisterAddressType>::regOverride(baseRegisterAddress + Offsets::pupdr,
                                                                          pullupPullDownValue << numberOfShifts);
  }

  template<AlternateFunction function, PinType pinNumber>
  static void setAlternateFunction(const RegisterAddressType baseRegisterAddress)
  {
    static_assert(pinNumber < numberOfPins, "Pin number is not supported!");

    const auto alternateFunctionValue = alternateFunctionToValue.at(function);

    static constexpr auto numberOfPinsInEachRegister = 8;
    constexpr auto doesPinBelongToLowRegister = pinNumber < numberOfPinsInEachRegister;

    static constexpr auto shiftPerPin = 4;
    constexpr auto numberOfShifts =
      doesPinBelongToLowRegister ? (pinNumber * shiftPerPin) : ((pinNumber - numberOfPinsInEachRegister) * shiftPerPin);

    if constexpr (doesPinBelongToLowRegister)
      RegisterAccess<RegisterAddressType, RegisterAddressType>::regOverride(baseRegisterAddress + Offsets::afrl,
                                                                            alternateFunctionValue << numberOfShifts);
    else
      RegisterAccess<RegisterAddressType, RegisterAddressType>::regOverride(baseRegisterAddress + Offsets::afrh,
                                                                            alternateFunctionValue << numberOfShifts);
  }

  template<PinType pinNumber>
  static bool readInputPin(const RegisterAddressType baseRegisterAddress)
  {
    return RegisterAccess<RegisterAddressType, RegisterAddressType>::regBitGet(baseRegisterAddress + Offsets::idr,
                                                                               pinNumber);
  }

  static RegisterAddressType readInputPort(const RegisterAddressType baseRegisterAddress)
  {
    return RegisterAccess<RegisterAddressType, RegisterAddressType>::regGet(baseRegisterAddress + Offsets::idr);
  }

  template<PinType pinNumber, bool set>
  static void writeOutputPin(const RegisterAddressType baseRegisterAddress)
  {
    if constexpr (set)
      RegisterAccess<RegisterAddressType, RegisterAddressType>::regBitSet(baseRegisterAddress + Offsets::odr,
                                                                          pinNumber);
    else
      RegisterAccess<RegisterAddressType, RegisterAddressType>::regBitClear(baseRegisterAddress + Offsets::odr,
                                                                            pinNumber);
  }

  static void writeOutputPort(const RegisterAddressType baseRegisterAddress, const RegisterAddressType value)
  {
    RegisterAccess<RegisterAddressType, RegisterAddressType>::regOverride(baseRegisterAddress + Offsets::odr, value);
  }

  template<PinType pinNumber>
  static void toggleOutputPin(const RegisterAddressType baseRegisterAddress)
  {
    RegisterAccess<RegisterAddressType, RegisterAddressType>::regBitToggle(baseRegisterAddress + Offsets::odr,
                                                                           pinNumber);
  }

private:
  static constexpr StaticMap<PortMode, RegisterAddressType, 4> portModeToValue{
    { { { PortMode::input, 0b00 },
        { PortMode::generalpurposeOutput, 0b01 },
        { PortMode::alternateFunction, 0b10 },
        { PortMode::analog, 0b11 } } }
  };

  static constexpr StaticMap<OutputType, RegisterAddressType, 2> outputTypeToValue{
    { { { OutputType::pushPull, 0b0 }, { OutputType::openDrain, 0b1 } } }
  };

  static constexpr StaticMap<OutputSpeed, RegisterAddressType, 4> outputSpeedToValue{
    { { { OutputSpeed::low, 0b00 },
        { OutputSpeed::medium, 0b01 },
        { OutputSpeed::high, 0b10 },
        { OutputSpeed::veryHigh, 0b11 } } }
  };

  static constexpr StaticMap<PullupPullDownControl, RegisterAddressType, 3> pullupPullDownControlToValue{
    { { { PullupPullDownControl::noPullupPullDown, 0b00 },
        { PullupPullDownControl::pullup, 0b01 },
        { PullupPullDownControl::pullDown, 0b10 } } }
  };

  static constexpr StaticMap<AlternateFunction, RegisterAddressType, 16> alternateFunctionToValue{
    { { { AlternateFunction::af0, 0b0000 },
        { AlternateFunction::af1, 0b0001 },
        { AlternateFunction::af2, 0b0010 },
        { AlternateFunction::af3, 0b0011 },
        { AlternateFunction::af4, 0b0100 },
        { AlternateFunction::af5, 0b0101 },
        { AlternateFunction::af6, 0b0110 },
        { AlternateFunction::af7, 0b0111 },
        { AlternateFunction::af8, 0b1000 },
        { AlternateFunction::af9, 0b1001 },
        { AlternateFunction::af10, 0b1010 },
        { AlternateFunction::af11, 0b1011 },
        { AlternateFunction::af12, 0b1100 },
        { AlternateFunction::af13, 0b1101 },
        { AlternateFunction::af14, 0b1110 },
        { AlternateFunction::af15, 0b1111 } } }
  };

  static constexpr auto numberOfPins = 16;
};

#endif /* STM32F407DISCOVERY_SRC_TARGETSPECIFIC_REGISTERS_GPIOREGISTERS */
