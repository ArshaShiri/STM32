#ifndef RCCREGISTERS
#define RCCREGISTERS

#include "registerType.h"
#include "registersBaseAddresses.h"

#include "utils/helpers.h"
#include "utils/registerAccess.h"

enum class PeripheralAHB1
{
  GPIOA,
  GPIOB,
  GPIOC,
  GPIOD,
  GPIOE,
  GPIOF,
  GPIOG,
  GPIOH,
  GPIOI
};

enum class PeripheralAPB1
{
  I2C1,
  I2C2,
  I2C3
};

template<typename RegisterAddressType>
class RCCRegisters
{
  struct Offsets
  {
    static constexpr RegisterType CR = UINT32_C(0x00);
    static constexpr RegisterType pllcfgr = UINT32_C(0x04);
    static constexpr RegisterType cfgr = UINT32_C(0x08);
    static constexpr RegisterType cir = UINT32_C(0x0C);
    static constexpr RegisterType ahb1rstr = UINT32_C(0x10);
    static constexpr RegisterType ahb2rstr = UINT32_C(0x14);
    static constexpr RegisterType ahb3rstr = UINT32_C(0x18);
    // 0x1C is reserved
    static constexpr RegisterType apb1rstr = UINT32_C(0x20);
    static constexpr RegisterType apb2rstr = UINT32_C(0x24);
    // 0x28 is reserved
    // 0x2C is reserved
    static constexpr RegisterType ahb1enr = UINT32_C(0x30);
    static constexpr RegisterType ahb2enr = UINT32_C(0x34);
    static constexpr RegisterType ahb3enr = UINT32_C(0x38);
    // 0x3C is reserved
    static constexpr RegisterType apb1enr = UINT32_C(0x40);
    static constexpr RegisterType apb2enr = UINT32_C(0x44);
    // 0x48 is reserved
    // 0x4C is reserved
    static constexpr RegisterType ahb1lpenr = UINT32_C(0x50);
    static constexpr RegisterType ahb2lpenr = UINT32_C(0x54);
    static constexpr RegisterType ahb3lpenr = UINT32_C(0x58);
    // 0x5C is reserved
    static constexpr RegisterType apb1lpenr = UINT32_C(0x60);
    static constexpr RegisterType apb2lpenr = UINT32_C(0x64);
    // 0x68 is reserved
    // 0x6C is reserved
    static constexpr RegisterType bdcr = UINT32_C(0x70);
    static constexpr RegisterType csr = UINT32_C(0x74);
    // 0x78 is reserved
    // 0x7C is reserved
    static constexpr RegisterType sscgr = UINT32_C(0x80);
    static constexpr RegisterType plli2scfgr = UINT32_C(0x84);
    static constexpr RegisterType pllsaicfgr = UINT32_C(0x88);
    static constexpr RegisterType dckcfgr = UINT32_C(0x8C);
  };

public:
  template<PeripheralAHB1 peripheral, bool set>
  static void setPeripheralOnAHB1(const RegisterAddressType rccBaseAddress)
  {
    constexpr RegisterAddressType bitNumber = ahb1ToBitNumber.at(peripheral);

    if constexpr (set)
      RegisterAccess<RegisterAddressType, RegisterAddressType>::regBitSet(rccBaseAddress + Offsets::ahb1enr, bitNumber);
    else
      RegisterAccess<RegisterAddressType, RegisterAddressType>::regBitClear(rccBaseAddress + Offsets::ahb1enr,
                                                                            bitNumber);
  }

  template<PeripheralAPB1 peripheral, bool set>
  static void setPeripheralOnAPB1(const RegisterAddressType rccBaseAddress)
  {
    constexpr RegisterAddressType bitNumber = apb1ToBitNumber.at(peripheral);

    if constexpr (set)
      RegisterAccess<RegisterAddressType, RegisterAddressType>::regBitSet(rccBaseAddress + Offsets::apb1enr, bitNumber);
    else
      RegisterAccess<RegisterAddressType, RegisterAddressType>::regBitClear(rccBaseAddress + Offsets::apb1enr,
                                                                            bitNumber);
  }

private:
  static constexpr StaticMap<PeripheralAHB1, RegisterType, 9> ahb1ToBitNumber{ { { { PeripheralAHB1::GPIOA, 0 },
                                                                                   { PeripheralAHB1::GPIOB, 1 },
                                                                                   { PeripheralAHB1::GPIOC, 2 },
                                                                                   { PeripheralAHB1::GPIOD, 3 },
                                                                                   { PeripheralAHB1::GPIOE, 4 },
                                                                                   { PeripheralAHB1::GPIOF, 5 },
                                                                                   { PeripheralAHB1::GPIOG, 6 },
                                                                                   { PeripheralAHB1::GPIOH, 7 },
                                                                                   { PeripheralAHB1::GPIOI, 8 } } } };

  static constexpr StaticMap<PeripheralAPB1, RegisterType, 3> apb1ToBitNumber{
    { { { PeripheralAPB1::I2C1, 21 }, { PeripheralAPB1::I2C2, 22 }, { PeripheralAPB1::I2C3, 23 } } }
  };
};

class RCCRegistersTarget
{
public:
  template<PeripheralAHB1 peripheral, bool set>
  static void setPeripheralOnAHB1()
  {
    constexpr auto rccBaseAddress = BaseAddresses::rcc;
    RCCRegisters<RegisterType>::setPeripheralOnAHB1<peripheral, set>(rccBaseAddress);
  }

  template<PeripheralAPB1 peripheral, bool set>
  static void setPeripheralOnAPB1()
  {
    constexpr auto rccBaseAddress = BaseAddresses::rcc;
    RCCRegisters<RegisterType>::setPeripheralOnAPB1<peripheral, set>(rccBaseAddress);
  }
};

#endif /* RCCREGISTERS */
