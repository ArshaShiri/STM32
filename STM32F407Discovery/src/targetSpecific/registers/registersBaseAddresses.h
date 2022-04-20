#ifndef REGISTERS
#define REGISTERS

#include "registerType.h"
class BaseAddresses
{
private:
  static constexpr RegisterType sizeOfSRam1KB = 112;

  struct AHB1Offset
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
    static constexpr RegisterType rcc = UINT32_C(0x3800);
  };

  struct APB1Offset
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
  };

  struct APB2Offset
  {
    static constexpr RegisterType usart1 = UINT32_C(0x1000);
    static constexpr RegisterType usart6 = UINT32_C(0x1400);
    static constexpr RegisterType spi1 = UINT32_C(0x3000);
    static constexpr RegisterType syscfg = UINT32_C(0x3800);
    static constexpr RegisterType exti = UINT32_C(0x3C00);
  };

public:
  static constexpr RegisterType flash = UINT32_C(0x08000000);
  static constexpr RegisterType sRam1 = UINT32_C(0x20000000);
  static constexpr RegisterType sRam2 = UINT32_C(sRam1 + sizeOfSRam1KB * 1024);
  static constexpr RegisterType rom = UINT32_C(0x1FFF0000);

  static constexpr RegisterType peripheral = UINT32_C(0x40000000);

  static constexpr RegisterType apb1 = BaseAddresses::peripheral;
  static constexpr RegisterType apb2 = UINT32_C(0x40010000);
  static constexpr RegisterType ahb1 = UINT32_C(0x40020000);
  static constexpr RegisterType ahb2 = UINT32_C(0x50000000);

  static constexpr RegisterType gpioA = ahb1 + AHB1Offset::gpioA;
  static constexpr RegisterType gpioB = ahb1 + AHB1Offset::gpioB;
  static constexpr RegisterType gpioC = ahb1 + AHB1Offset::gpioC;
  static constexpr RegisterType gpioD = ahb1 + AHB1Offset::gpioD;
  static constexpr RegisterType gpioE = ahb1 + AHB1Offset::gpioE;
  static constexpr RegisterType gpioF = ahb1 + AHB1Offset::gpioF;
  static constexpr RegisterType gpioG = ahb1 + AHB1Offset::gpioG;
  static constexpr RegisterType gpioH = ahb1 + AHB1Offset::gpioH;
  static constexpr RegisterType gpioI = ahb1 + AHB1Offset::gpioI;
  static constexpr RegisterType rcc = ahb1 + AHB1Offset::rcc;

  static constexpr RegisterType spi2 = apb1 + APB1Offset::spi2;
  static constexpr RegisterType spi3 = apb1 + APB1Offset::spi3;
  static constexpr RegisterType usart2 = apb1 + APB1Offset::usart2;
  static constexpr RegisterType usart3 = apb1 + APB1Offset::usart3;
  static constexpr RegisterType uart4 = apb1 + APB1Offset::uart4;
  static constexpr RegisterType uart5 = apb1 + APB1Offset::uart5;

  static constexpr RegisterType i2c1 = apb1 + APB1Offset::i2c1;
  static constexpr RegisterType i2c2 = apb1 + APB1Offset::i2c2;
  static constexpr RegisterType i2c3 = apb1 + APB1Offset::i2c3;

  static constexpr RegisterType usart1 = apb2 + APB2Offset::usart1;
  static constexpr RegisterType usart6 = apb2 + APB2Offset::usart6;
  static constexpr RegisterType spi1 = apb2 + APB2Offset::spi1;
  static constexpr RegisterType syscfg = apb2 + APB2Offset::syscfg;
  static constexpr RegisterType exti = apb2 + APB2Offset::exti;
};

#endif /* REGISTERS */
