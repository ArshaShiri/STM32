#ifndef RCCREGISTERS
#define RCCREGISTERS

#include "targetSpecific/registerType.h"
#include "targetSpecific/registersBaseAddresses.h"

#include "utils/helpers.h"
#include "utils/registerAccess.h"

enum class Peripheral
{
  GPIOA,
  GPIOB,
  GPIOC,
  GPIOD,
  GPIOE,
  GPIOF,
  GPIOG,
  GPIOH,
  GPIOI,
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
  template<Peripheral peripheral, bool set>
  static void peripheralClockSet(const RegisterAddressType rccBaseAddress)
  {
    if constexpr (isPeripheralOnAHB1<peripheral>())
      peripheralOnAHB1Set<peripheral, set>(rccBaseAddress);

    if constexpr (isPeripheralOnAPB1<peripheral>())
      peripheralOnAPB1<peripheral, set>(rccBaseAddress);
  }

private:
  template<Peripheral peripheral>
  static constexpr bool isPeripheralOnAHB1()
  {
    return (peripheral == Peripheral::GPIOA) || (peripheral == Peripheral::GPIOB) ||
           (peripheral == Peripheral::GPIOC) || (peripheral == Peripheral::GPIOD) ||
           (peripheral == Peripheral::GPIOE) || (peripheral == Peripheral::GPIOF) ||
           (peripheral == Peripheral::GPIOG) || (peripheral == Peripheral::GPIOH) || (peripheral == Peripheral::GPIOI);
  }

  template<Peripheral peripheral>
  static constexpr bool isPeripheralOnAPB1()
  {
    return (peripheral == Peripheral::I2C1) || (peripheral == Peripheral::I2C2) || (peripheral == Peripheral::I2C3);
  }


  template<Peripheral peripheral, bool set>
  static void peripheralOnAHB1Set(const RegisterAddressType rccBaseAddress)
  {
    constexpr RegisterAddressType bitNumber = ahb1ToBitNumber.at(peripheral);

    if constexpr (set)
      RegisterAccess<RegisterAddressType, RegisterAddressType>::regBitSet(rccBaseAddress + Offsets::ahb1enr, bitNumber);
    else
      RegisterAccess<RegisterAddressType, RegisterAddressType>::regBitClear(rccBaseAddress + Offsets::ahb1enr,
                                                                            bitNumber);
  }

  template<Peripheral peripheral, bool set>
  static void peripheralOnAPB1(const RegisterAddressType rccBaseAddress)
  {
    constexpr RegisterAddressType bitNumber = apb1ToBitNumber.at(peripheral);

    if constexpr (set)
      RegisterAccess<RegisterAddressType, RegisterAddressType>::regBitSet(rccBaseAddress + Offsets::apb1enr, bitNumber);
    else
      RegisterAccess<RegisterAddressType, RegisterAddressType>::regBitClear(rccBaseAddress + Offsets::apb1enr,
                                                                            bitNumber);
  }

  static constexpr StaticMap<Peripheral, RegisterType, 9> ahb1ToBitNumber{ { { { Peripheral::GPIOA, 0 },
                                                                               { Peripheral::GPIOB, 1 },
                                                                               { Peripheral::GPIOC, 2 },
                                                                               { Peripheral::GPIOD, 3 },
                                                                               { Peripheral::GPIOE, 4 },
                                                                               { Peripheral::GPIOF, 5 },
                                                                               { Peripheral::GPIOG, 6 },
                                                                               { Peripheral::GPIOH, 7 },
                                                                               { Peripheral::GPIOI, 8 } } } };

  static constexpr StaticMap<Peripheral, RegisterType, 3> apb1ToBitNumber{
    { { { Peripheral::I2C1, 21 }, { Peripheral::I2C2, 22 }, { Peripheral::I2C3, 23 } } }
  };
};

class RCCRegistersTarget
{
public:
  template<Peripheral peripheral, bool set>
  static void peripheralClockSet()
  {
    constexpr auto rccBaseAddress = BaseAddresses::rcc;
    RCCRegisters<RegisterType>::peripheralClockSet<peripheral, set>();
  }
};

#endif /* RCCREGISTERS */
