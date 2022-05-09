#ifndef STM32F407DISCOVERY_SRC_TARGETSPECIFIC_REGISTERS_SPIREGISTERS
#define STM32F407DISCOVERY_SRC_TARGETSPECIFIC_REGISTERS_SPIREGISTERS

#include "registerType.h"
#include "registersBaseAddresses.h"

#include "utils/helpers.h"
#include "utils/registerAccess.h"

enum class ControlRegister1Property
{
  CPHA,
  CPOL,
  MSTR,
  SPE,
  LSBFIRST,
  SSI,
  SSM,
  RXONLY,
  DFF,
  CRCNEXT,
  CRCEN,
  BIDIOE,
  BIDIMODE
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
  RXDMAEN,
  TXDMAEN,
  SSOE,
  FRF,
  ERRIE,
  RXNEIE,
  TXEIE
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
    constexpr auto bitNumber = controlRegister1PropertyToValue.at(property);
    doSet<set>(spiBaseAddress + Offsets::cr1, bitNumber);
  }

  template<BaudRateControl property, bool set>
  static void setBaudRate(const RegisterAddressType spiBaseAddress)
  {
    constexpr auto value = baudRateControlToValue.at(property);
    constexpr auto numberOfShifts = 3;
    RegisterAccess<RegisterAddressType, RegisterAddressType>::regSet(spiBaseAddress + Offsets::cr1,
                                                                     value << numberOfShifts);
  }

  template<ControlRegister2Property property, bool set>
  static void setControlRegister2Bit(const RegisterAddressType spiBaseAddress)
  {
    constexpr auto bitNumber = controlRegister2PropertyToValue.at(property);
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

  static constexpr StaticMap<ControlRegister1Property, std::uint8_t, 13> controlRegister1PropertyToValue{
    { { { ControlRegister1Property::CPHA, 0 },
        { ControlRegister1Property::CPOL, 1 },
        { ControlRegister1Property::MSTR, 2 },
        { ControlRegister1Property::SPE, 6 },
        { ControlRegister1Property::LSBFIRST, 7 },
        { ControlRegister1Property::SSI, 8 },
        { ControlRegister1Property::SSM, 9 },
        { ControlRegister1Property::RXONLY, 10 },
        { ControlRegister1Property::DFF, 11 },
        { ControlRegister1Property::CRCNEXT, 12 },
        { ControlRegister1Property::CRCEN, 13 },
        { ControlRegister1Property::BIDIOE, 14 },
        { ControlRegister1Property::BIDIMODE, 15 } } }
  };

  static constexpr StaticMap<BaudRateControl, std::uint8_t, 8> baudRateControlToValue{
    { { { BaudRateControl::fPCLKDiv2, 0b000 },
        { BaudRateControl::fPCLKDiv4, 0b001 },
        { BaudRateControl::fPCLKDiv8, 0b010 },
        { BaudRateControl::fPCLKDiv16, 0b011 },
        { BaudRateControl::fPCLKDiv32, 0b100 },
        { BaudRateControl::fPCLKDiv64, 0b101 },
        { BaudRateControl::fPCLKDiv128, 0b110 },
        { BaudRateControl::fPCLKDiv256, 0b111 } } }
  };

  static constexpr StaticMap<ControlRegister2Property, std::uint8_t, 7> controlRegister2PropertyToValue{
    { { { ControlRegister2Property::RXDMAEN, 0 },
        { ControlRegister2Property::TXDMAEN, 1 },
        { ControlRegister2Property::SSOE, 2 },
        { ControlRegister2Property::FRF, 4 },
        { ControlRegister2Property::ERRIE, 5 },
        { ControlRegister2Property::RXNEIE, 6 },
        { ControlRegister2Property::TXEIE, 7 } } }
  };
};

#endif /* STM32F407DISCOVERY_SRC_TARGETSPECIFIC_REGISTERS_SPIREGISTERS */
