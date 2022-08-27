

#include "externalPeripherals/i2cLCD.h"

#include "targetSpecific/drivers/gpio.h"
#include "targetSpecific/drivers/i2c.h"
#include "targetSpecific/registers/registersBaseAddresses.h"

/*
 *  PB6 --> I2C1_SCL
 *  PB7 --> I2C1_SDA
 */

namespace
{
void initI2CGPIOPeripherals()
{
  constexpr auto pinNumberSCL = 6;
  constexpr auto pinNumberSDA = 7;
  static constexpr GPIOInitData initData{ PeripheralAHB1::GPIOB,  PortMode::alternateFunction,
                                          AlternateFunction::af4, OutputType::openDrain,
                                          OutputSpeed::high,      PullupPullDownControl::pullup };

  using gpioB = GPIO<BaseAddresses::gpioB>;
  gpioB::init<initData, pinNumberSDA>();
  gpioB::init<initData, pinNumberSCL>();
}
} // namespace

int main()
{
  initI2CGPIOPeripherals();

  constexpr uint8_t ownAddress = 0x61;
  constexpr uint32_t serialClockSpeedHz = 100000;
  constexpr I2CInitData initData{ Acknowledge::enable, ownAddress, serialClockSpeedHz, FastModeDutyCycle::two };

  I2C<I2CNumber::i2c1>::init<initData>();

  I2CLCD::init();
  I2CLCD::setCursorLocation<1, 2>();
  I2CLCD::sendString("Hello World!");


  static constexpr auto numberOfDisplayShifts = 4;
  while (true)
  {
    for (auto i = 0; i < numberOfDisplayShifts; ++i)
    {
      softwareDelay<1000000>();
      I2CLCD::shiftRight();
    }

    for (auto i = 0; i < numberOfDisplayShifts; ++i)
    {
      softwareDelay<1000000>();
      I2CLCD::shiftLeft();
    }
  }

  return 0;
}
