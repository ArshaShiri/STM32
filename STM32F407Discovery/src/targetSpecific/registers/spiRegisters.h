#ifndef STM32F407DISCOVERY_SRC_TARGETSPECIFIC_REGISTERS_SPIREGISTERS
#define STM32F407DISCOVERY_SRC_TARGETSPECIFIC_REGISTERS_SPIREGISTERS

#include <type_traits>

#include "registerType.h"
#include "registersBaseAddresses.h"

#include "utils/helpers.h"
#include "utils/registerAccess.h"

enum class ControlRegister1Property
{
  cpha,
  cpol,
  mstr,
  spe,
  lsbfirst,
  ssi,
  ssm,
  rxonly,
  dff,
  crcnext,
  crcen,
  bidioe,
  bidimode
};

enum class ClockPhase
{
  firstClockTransitionFirstDataCapture,
  secondClockTransitionFirstDataCapture
};

enum class ClockPolarity
{
  clockZeroWhenIdle,
  clockOneWhenIdle
};

enum class MasterSelection
{
  master,
  slave
};

enum class SoftwareSlaveSelect
{
  disabled,
  enabled
};

enum class DataFrameFormat
{
  eightBit,
  sixteenBit
};

enum class ReceiveOnly
{
  fullDuplex,
  outputDisabled
};

enum class OutputEnableInBidirectionalMode
{
  disabled,
  enabled
};

enum class BidirectionalDataMode
{
  fullDuplex,
  halfDuplex
};

enum class BaudRateControl
{
  fPCLKDiv2,
  fPCLKDiv4,
  fPCLKDiv8,
  fPCLKDiv16,
  fPCLKDiv32,
  fPCLKDiv64,
  fPCLKDiv128,
  fPCLKDiv256
};

enum class ControlRegister2Property
{
  rxdmaen,
  txdmaen,
  ssoe,
  frf,
  errie,
  rxneie,
  txeie
};

template<typename RegisterAddressType>
class SPIRegisters
{
  struct Offsets
  {
    // TODO Make the type to be RegisterAddressType
    static constexpr RegisterType cr1 = UINT32_C(0x00);
    static constexpr RegisterType cr2 = UINT32_C(0x04);
    static constexpr RegisterType sr = UINT32_C(0x08);
    static constexpr RegisterType dr = UINT32_C(0x0C);
    static constexpr RegisterType crcpr = UINT32_C(0x10);
    static constexpr RegisterType rxcrcpr = UINT32_C(0x14);
    static constexpr RegisterType txcrcpr = UINT32_C(0x18);
    static constexpr RegisterType i2scfgr = UINT32_C(0x1C);
    static constexpr RegisterType i2spr = UINT32_C(0x20);
  };

public:
  template<ControlRegister1Property property, typename T, T value>
  static void setControlRegister1Bit(const RegisterAddressType spiBaseAddress)
  {
    constexpr auto bitNumber = controlRegister1PropertyToShiftValue.at(property);
    constexpr auto setValue = SetValueHelper<property, T>::getSetValue(value);
    doSet<setValue>(spiBaseAddress + Offsets::cr1, bitNumber);
  }

  template<ControlRegister1Property property, typename T, T value>
  static bool readControlRegister1Bit(const RegisterAddressType spiBaseAddress)
  {
    constexpr auto bitNumber = controlRegister1PropertyToShiftValue.at(property);
    const auto actualValueInRegister =
      RegisterAccess<RegisterAddressType, RegisterAddressType>::regBitGet(spiBaseAddress + Offsets::cr1, bitNumber);
    return actualValueInRegister == SetValueHelper<property, T>::getSetValue(value);
  }

  template<BaudRateControl rate>
  static void setBaudRate(const RegisterAddressType spiBaseAddress)
  {
    constexpr auto value = baudRateControlToShiftValue.at(rate);
    constexpr auto numberOfShifts = 3;
    RegisterAccess<RegisterAddressType, RegisterAddressType>::regOr(spiBaseAddress + Offsets::cr1,
                                                                    value << numberOfShifts);
  }

  template<ControlRegister2Property property, bool set>
  static void setControlRegister2Bit(const RegisterAddressType spiBaseAddress)
  {
    constexpr auto bitNumber = controlRegister2PropertyToShiftValue.at(property);
    doSet<set>(spiBaseAddress + Offsets::cr2, bitNumber);
  }

  static void writeToDataRegister(const RegisterAddressType spiBaseAddress, const std::uint8_t data)
  {
    RegisterAccess<RegisterAddressType, std::uint8_t>::regSet(spiBaseAddress + Offsets::dr, data);
  }

  static void writeToDataRegister(const RegisterAddressType spiBaseAddress, const std::uint16_t data)
  {
    RegisterAccess<RegisterAddressType, std::uint16_t>::regSet(spiBaseAddress + Offsets::dr, data);
  }

  static bool isReceiveBufferOccupied(const RegisterAddressType spiBaseAddress)
  {
    constexpr auto bitNumber = 0;
    return RegisterAccess<RegisterAddressType, RegisterAddressType>::regBitGet(spiBaseAddress + Offsets::sr, bitNumber);
  }

  static bool isTransmitBufferEmpty(const RegisterAddressType spiBaseAddress)
  {
    constexpr auto bitNumber = 1;
    return RegisterAccess<RegisterAddressType, RegisterAddressType>::regBitGet(spiBaseAddress + Offsets::sr, bitNumber);
  }

  static bool isSPIBusy(const RegisterAddressType spiBaseAddress)
  {
    constexpr auto bitNumber = 7;
    return RegisterAccess<RegisterAddressType, RegisterAddressType>::regBitGet(spiBaseAddress + Offsets::sr, bitNumber);
  }

private:
  template<ControlRegister1Property property, typename T>
  struct SetValueHelper
  {
    static constexpr bool getSetValue(T value) { return value; }
  };

  // Only specialize based on property to avoid calling a specialized method with the wrong value type.
  template<typename T>
  struct SetValueHelper<ControlRegister1Property::cpha, T>
  {
    static constexpr bool getSetValue(T value)
    {
      return value == ClockPhase::secondClockTransitionFirstDataCapture ? 1 : 0;
    }
  };

  template<typename T>
  struct SetValueHelper<ControlRegister1Property::cpol, T>
  {
    static constexpr bool getSetValue(T value) { return value == ClockPolarity::clockOneWhenIdle ? 1 : 0; }
  };

  template<typename T>
  struct SetValueHelper<ControlRegister1Property::mstr, T>
  {
    static constexpr bool getSetValue(T value) { return value == MasterSelection::master ? 1 : 0; }
  };

  template<typename T>
  struct SetValueHelper<ControlRegister1Property::dff, T>
  {
    static constexpr bool getSetValue(T value) { return value == DataFrameFormat::sixteenBit ? 1 : 0; }
  };

  template<typename T>
  struct SetValueHelper<ControlRegister1Property::ssm, T>
  {
    static constexpr bool getSetValue(T value) { return value == SoftwareSlaveSelect::enabled ? 1 : 0; }
  };

  template<typename T>
  struct SetValueHelper<ControlRegister1Property::rxonly, T>
  {
    static constexpr bool getSetValue(T value) { return value == ReceiveOnly::outputDisabled ? 1 : 0; }
  };

  template<typename T>
  struct SetValueHelper<ControlRegister1Property::bidioe, T>
  {
    static constexpr bool getSetValue(T value) { return value == OutputEnableInBidirectionalMode::enabled ? 1 : 0; }
  };

  template<typename T>
  struct SetValueHelper<ControlRegister1Property::bidimode, T>
  {
    static constexpr bool getSetValue(T value) { return value == BidirectionalDataMode::halfDuplex ? 1 : 0; }
  };

  template<bool set>
  static void doSet(const RegisterAddressType regAddress, const RegisterAddressType bitNumber)
  {
    if constexpr (set)
      RegisterAccess<RegisterAddressType, RegisterAddressType>::regBitSet(regAddress, bitNumber);
    else
      RegisterAccess<RegisterAddressType, RegisterAddressType>::regBitClear(regAddress, bitNumber);
  }

  static constexpr StaticMap<ControlRegister1Property, std::uint8_t, 13> controlRegister1PropertyToShiftValue{
    { { { ControlRegister1Property::cpha, 0 },
        { ControlRegister1Property::cpol, 1 },
        { ControlRegister1Property::mstr, 2 },
        { ControlRegister1Property::spe, 6 },
        { ControlRegister1Property::lsbfirst, 7 },
        { ControlRegister1Property::ssi, 8 },
        { ControlRegister1Property::ssm, 9 },
        { ControlRegister1Property::rxonly, 10 },
        { ControlRegister1Property::dff, 11 },
        { ControlRegister1Property::crcnext, 12 },
        { ControlRegister1Property::crcen, 13 },
        { ControlRegister1Property::bidioe, 14 },
        { ControlRegister1Property::bidimode, 15 } } }
  };

  static constexpr StaticMap<BaudRateControl, std::uint8_t, 8> baudRateControlToShiftValue{
    { { { BaudRateControl::fPCLKDiv2, 0b000 },
        { BaudRateControl::fPCLKDiv4, 0b001 },
        { BaudRateControl::fPCLKDiv8, 0b010 },
        { BaudRateControl::fPCLKDiv16, 0b011 },
        { BaudRateControl::fPCLKDiv32, 0b100 },
        { BaudRateControl::fPCLKDiv64, 0b101 },
        { BaudRateControl::fPCLKDiv128, 0b110 },
        { BaudRateControl::fPCLKDiv256, 0b111 } } }
  };

  static constexpr StaticMap<ControlRegister2Property, std::uint8_t, 7> controlRegister2PropertyToShiftValue{
    { { { ControlRegister2Property::rxdmaen, 0 },
        { ControlRegister2Property::txdmaen, 1 },
        { ControlRegister2Property::ssoe, 2 },
        { ControlRegister2Property::frf, 4 },
        { ControlRegister2Property::errie, 5 },
        { ControlRegister2Property::rxneie, 6 },
        { ControlRegister2Property::txeie, 7 } } }
  };
};

#endif /* STM32F407DISCOVERY_SRC_TARGETSPECIFIC_REGISTERS_SPIREGISTERS */
