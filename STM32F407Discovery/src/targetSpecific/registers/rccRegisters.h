#ifndef SRC_TARGETSPECIFIC_REGISTERS_RCCREGISTERS
#define SRC_TARGETSPECIFIC_REGISTERS_RCCREGISTERS

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
  I2C3,
  SPI2,
  SPI3
};

enum class PeripheralAPB2
{
  SYSCFG,
  SPI1,
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
    doSet<set>(rccBaseAddress + Offsets::ahb1enr, bitNumber);
  }

  template<PeripheralAPB1 peripheral, bool set>
  static void setPeripheralOnAPB1(const RegisterAddressType rccBaseAddress)
  {
    constexpr RegisterAddressType bitNumber = apb1ToBitNumber.at(peripheral);
    doSet<set>(rccBaseAddress + Offsets::apb1enr, bitNumber);
  }

  template<PeripheralAPB2 peripheral, bool set>
  static void setPeripheralOnAPB2(const RegisterAddressType rccBaseAddress)
  {
    constexpr RegisterAddressType bitNumber = apb2ToBitNumber.at(peripheral);
    doSet<set>(rccBaseAddress + Offsets::apb2enr, bitNumber);
  }

  template<PeripheralAHB1 peripheral>
  static void resetPeripheralOnAHB1(const RegisterAddressType rccBaseAddress)
  {
    constexpr RegisterAddressType bitNumber = ahb1ToBitNumber.at(peripheral);
    RegisterAccess<RegisterAddressType, RegisterAddressType>::regBitSet(rccBaseAddress + Offsets::ahb1rstr, bitNumber);
    RegisterAccess<RegisterAddressType, RegisterAddressType>::regBitClear(rccBaseAddress + Offsets::ahb1rstr,
                                                                          bitNumber);
  }

  template<PeripheralAPB1 peripheral>
  static void resetPeripheralOnAPB1(const RegisterAddressType rccBaseAddress)
  {
    constexpr RegisterAddressType bitNumber = apb1ToBitNumber.at(peripheral);
    RegisterAccess<RegisterAddressType, RegisterAddressType>::regBitSet(rccBaseAddress + Offsets::apb1rstr, bitNumber);
    RegisterAccess<RegisterAddressType, RegisterAddressType>::regBitClear(rccBaseAddress + Offsets::apb1rstr,
                                                                          bitNumber);
  }

  template<PeripheralAPB2 peripheral>
  static void resetPeripheralOnAPB2(const RegisterAddressType rccBaseAddress)
  {
    constexpr RegisterAddressType bitNumber = apb2ToBitNumber.at(peripheral);
    RegisterAccess<RegisterAddressType, RegisterAddressType>::regBitSet(rccBaseAddress + Offsets::apb2rstr, bitNumber);
    RegisterAccess<RegisterAddressType, RegisterAddressType>::regBitClear(rccBaseAddress + Offsets::apb2rstr,
                                                                          bitNumber);
  }

  static uint32_t getAPB1Clock(const RegisterAddressType rccBaseAddress)
  {
    uint32_t clockSourceValue = 0;
    const auto systemClockSwitchStatus = getSystemClockSwitchStatus(rccBaseAddress);

    // HSI
    if (systemClockSwitchStatus == 0)
      clockSourceValue = 16000000;
    else // HSE
      clockSourceValue = 8000000;

    // PLL is not implemented.

    const auto ahpPrescaler = getAHBPrescaler(rccBaseAddress);
    const auto apb1Prescaler = getAPB1Prescaler(rccBaseAddress);

    return (clockSourceValue / ahpPrescaler) / apb1Prescaler;
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

  static uint8_t getSystemClockSwitchStatus(const RegisterAddressType rccBaseAddress)
  {
    const auto cfgrValue =
      RegisterAccess<RegisterAddressType, RegisterAddressType>::regGet(rccBaseAddress + Offsets::cfgr);
    constexpr auto numberOfShifts = 2;
    constexpr auto maskValue = 0b11;

    return (cfgrValue >> numberOfShifts) & maskValue;
  }

  static uint16_t getAHBPrescaler(const RegisterAddressType rccBaseAddress)
  {
    const auto cfgrValue =
      RegisterAccess<RegisterAddressType, RegisterAddressType>::regGet(rccBaseAddress + Offsets::cfgr);
    constexpr auto numberOfShifts = 4;
    constexpr auto maskValue = 0b1111;
    const auto prescalerValue = (cfgrValue >> numberOfShifts) & maskValue;

    if (prescalerValue < 0b1000)
      return 1;

    if (prescalerValue == 0b1000)
      return 2;
    if (prescalerValue == 0b1001)
      return 4;
    if (prescalerValue == 0b1010)
      return 8;
    if (prescalerValue == 0b1011)
      return 16;
    if (prescalerValue == 0b1100)
      return 64;
    if (prescalerValue == 0b1101)
      return 128;
    if (prescalerValue == 0b1110)
      return 256;
    if (prescalerValue == 0b1111)
      return 512;

    return 0;
  }

  static uint8_t getAPB1Prescaler(const RegisterAddressType rccBaseAddress)
  {
    const auto cfgrValue =
      RegisterAccess<RegisterAddressType, RegisterAddressType>::regGet(rccBaseAddress + Offsets::cfgr);
    constexpr auto numberOfShifts = 10;
    constexpr auto maskValue = 0b111;
    const auto prescalerValue = (cfgrValue >> numberOfShifts) & maskValue;

    if (prescalerValue < 0b100)
      return 1;

    if (prescalerValue == 0b100)
      return 2;
    if (prescalerValue == 0b101)
      return 4;
    if (prescalerValue == 0b110)
      return 8;
    if (prescalerValue == 0b111)
      return 16;

    return 1;
  }

  static constexpr StaticMap<PeripheralAHB1, RegisterType, 9> ahb1ToBitNumber{ { { { PeripheralAHB1::GPIOA, 0 },
                                                                                   { PeripheralAHB1::GPIOB, 1 },
                                                                                   { PeripheralAHB1::GPIOC, 2 },
                                                                                   { PeripheralAHB1::GPIOD, 3 },
                                                                                   { PeripheralAHB1::GPIOE, 4 },
                                                                                   { PeripheralAHB1::GPIOF, 5 },
                                                                                   { PeripheralAHB1::GPIOG, 6 },
                                                                                   { PeripheralAHB1::GPIOH, 7 },
                                                                                   { PeripheralAHB1::GPIOI, 8 } } } };

  static constexpr StaticMap<PeripheralAPB1, RegisterType, 5> apb1ToBitNumber{ { { { PeripheralAPB1::SPI2, 14 },
                                                                                   { PeripheralAPB1::SPI3, 15 },
                                                                                   { PeripheralAPB1::I2C1, 21 },
                                                                                   { PeripheralAPB1::I2C2, 22 },
                                                                                   { PeripheralAPB1::I2C3, 23 } } } };

  static constexpr StaticMap<PeripheralAPB2, RegisterType, 2> apb2ToBitNumber{ { { { PeripheralAPB2::SPI1, 12 },
                                                                                   { PeripheralAPB2::SYSCFG, 14 } } } };
};

class RCCRegistersTarget
{
public:
  template<PeripheralAHB1 peripheral, bool set>
  static void setPeripheralOnAHB1()
  {
    RCCRegisters<RegisterType>::setPeripheralOnAHB1<peripheral, set>(rccBaseAddress);
  }

  template<PeripheralAPB1 peripheral, bool set>
  static void setPeripheralOnAPB1()
  {
    RCCRegisters<RegisterType>::setPeripheralOnAPB1<peripheral, set>(rccBaseAddress);
  }

  template<PeripheralAPB2 peripheral, bool set>
  static void setPeripheralOnAPB2()
  {
    RCCRegisters<RegisterType>::setPeripheralOnAPB2<peripheral, set>(rccBaseAddress);
  }

  template<PeripheralAHB1 peripheral>
  static void resetPeripheralOnAHB1()
  {
    RCCRegisters<RegisterType>::resetPeripheralOnAHB1<peripheral>(rccBaseAddress);
  }

  template<PeripheralAPB1 peripheral>
  static void resetPeripheralOnAPB1()
  {
    RCCRegisters<RegisterType>::resetPeripheralOnAPB1<peripheral>(rccBaseAddress);
  }

  template<PeripheralAPB2 peripheral>
  static void resetPeripheralOnAPB2()
  {
    RCCRegisters<RegisterType>::resetPeripheralOnAPB2<peripheral>(rccBaseAddress);
  }

private:
  static constexpr auto rccBaseAddress = BaseAddresses::rcc;
};

#endif /* SRC_TARGETSPECIFIC_REGISTERS_RCCREGISTERS */
