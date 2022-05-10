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
  template<ControlRegister1Property property, bool set>
  static void setControlRegister1Bit(const RegisterAddressType spiBaseAddress)
  {
    constexpr auto bitNumber = controlRegister1PropertyToShiftValue.at(property);
    doSet<set>(spiBaseAddress + Offsets::cr1, bitNumber);
  }

  template<BaudRateControl property, bool set>
  static void setBaudRate(const RegisterAddressType spiBaseAddress)
  {
    constexpr auto value = baudRateControlToShiftValue.at(property);
    constexpr auto numberOfShifts = 3;
    RegisterAccess<RegisterAddressType, RegisterAddressType>::regSet(spiBaseAddress + Offsets::cr1,
                                                                     value << numberOfShifts);
  }

  template<ControlRegister2Property property, bool set>
  static void setControlRegister2Bit(const RegisterAddressType spiBaseAddress)
  {
    constexpr auto bitNumber = controlRegister2PropertyToShiftValue.at(property);
    doSet<set>(spiBaseAddress + Offsets::cr2, bitNumber);
  }


private:
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
