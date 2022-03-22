#ifndef REGISTERS
#define REGISTERS

#include "registerType.h"

namespace
{
static constexpr RegisterType sizeOfSRam1KB = 112;

namespace ahb1Offset
{
  static constexpr RegisterType gpioA = UINT32_C(0x0000);
  static constexpr RegisterType gpioB = UINT32_C(0x0400);
  static constexpr RegisterType gpioC = UINT32_C(0x0800);
  static constexpr RegisterType gpioD = UINT32_C(0x0c00);
  static constexpr RegisterType gpioE = UINT32_C(0x1000);
  static constexpr RegisterType gpioF = UINT32_C(0x1400);
  static constexpr RegisterType gpioG = UINT32_C(0x1800);
  static constexpr RegisterType gpioH = UINT32_C(0x1c00);
  static constexpr RegisterType gpioI = UINT32_C(0x2000);
} // namespace ahb1Offset

namespace apb1Offset
{
  static constexpr RegisterType spi2 = UINT32_C(0x3800);
  static constexpr RegisterType spi3 = UINT32_C(0x3C00);
  static constexpr RegisterType usart2 = UINT32_C(0x4400);
  static constexpr RegisterType usart3 = UINT32_C(0x4800);
  static constexpr RegisterType uart4 = UINT32_C(0x4C00);
  static constexpr RegisterType uart5 = UINT32_C(0x5000);

  static constexpr RegisterType i2c1 = UINT32_C(0x5400);
  static constexpr RegisterType i2c2 = UINT32_C(0x5800);
  static constexpr RegisterType i2c3 = UINT32_C(0x5C00);
} // namespace apb1Offset

namespace apb2Offset
{
  static constexpr RegisterType usart1 = UINT32_C(0x1000);
  static constexpr RegisterType usart6 = UINT32_C(0x1400);
  static constexpr RegisterType spi1 = UINT32_C(0x3000);
  static constexpr RegisterType syscfg = UINT32_C(0x3800);
  static constexpr RegisterType exti = UINT32_C(0x3C00);
} // namespace apb2Offset

} // namespace

struct BaseAddresses
{
  static constexpr RegisterType flash = UINT32_C(0x08000000);
  static constexpr RegisterType sRam1 = UINT32_C(0x20000000);
  static constexpr RegisterType sRam2 = UINT32_C(sRam1 + sizeOfSRam1KB * 1024);
  static constexpr RegisterType rom = UINT32_C(0x1FFF0000);

  static constexpr RegisterType peripheral = UINT32_C(0x40000000);

  static constexpr RegisterType apb1 = BaseAddresses::peripheral;
  static constexpr RegisterType apb2 = UINT32_C(0x40010000);
  static constexpr RegisterType ahb1 = UINT32_C(0x40020000);
  static constexpr RegisterType ahb2 = UINT32_C(0x50000000);

  static constexpr RegisterType gpioA = ahb1 + ahb1Offset::gpioA;
  static constexpr RegisterType gpioB = ahb1 + ahb1Offset::gpioB;
  static constexpr RegisterType gpioC = ahb1 + ahb1Offset::gpioC;
  static constexpr RegisterType gpioD = ahb1 + ahb1Offset::gpioD;
  static constexpr RegisterType gpioE = ahb1 + ahb1Offset::gpioE;
  static constexpr RegisterType gpioF = ahb1 + ahb1Offset::gpioF;
  static constexpr RegisterType gpioG = ahb1 + ahb1Offset::gpioG;
  static constexpr RegisterType gpioH = ahb1 + ahb1Offset::gpioH;
  static constexpr RegisterType gpioI = ahb1 + ahb1Offset::gpioI;

  static constexpr RegisterType spi2 = apb1 + apb1Offset::spi2;
  static constexpr RegisterType spi3 = apb1 + apb1Offset::spi3;
  static constexpr RegisterType usart2 = apb1 + apb1Offset::usart2;
  static constexpr RegisterType usart3 = apb1 + apb1Offset::usart3;
  static constexpr RegisterType uart4 = apb1 + apb1Offset::uart4;
  static constexpr RegisterType uart5 = apb1 + apb1Offset::uart5;

  static constexpr RegisterType i2c1 = apb1 + apb1Offset::i2c1;
  static constexpr RegisterType i2c2 = apb1 + apb1Offset::i2c2;
  static constexpr RegisterType i2c3 = apb1 + apb1Offset::i2c3;

  static constexpr RegisterType usart1 = apb2 + apb2Offset::usart1;
  static constexpr RegisterType usart6 = apb2 + apb2Offset::usart6;
  static constexpr RegisterType spi1 = apb2 + apb2Offset::spi1;
  static constexpr RegisterType syscfg = apb2 + apb2Offset::syscfg;
  static constexpr RegisterType exti = apb2 + apb2Offset::exti;
};

#endif /* REGISTERS */