
#include "targetSpecific/drivers/i2c.h"
#include "targetSpecific/drivers/gpio.h"
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
  gpioB::init<initData, pinNumberSCL>();
  gpioB::init<initData, pinNumberSDA>();
}
} // namespace

int main()
{
  initI2CGPIOPeripherals();

  // constexpr SPIInitData initData{ MasterSelection::master,
  //                                 BidirectionalDataMode::fullDuplex,
  //                                 BaudRateControl::fPCLKDiv2,
  //                                 DataFrameFormat::eightBit,
  //                                 ClockPhase::firstClockTransitionFirstDataCapture,
  //                                 ClockPolarity::clockZeroWhenIdle,
  //                                 SoftwareSlaveSelect::enabled };

  // SPI<SPINumber::spi2>::init<initData>();

  // const std::array<std::uint8_t, 10> data{ { 0, 15, 54, 241, 78, 5, 6, 7, 8, 9 } };
  // SPI<SPINumber::spi2>::sendData(data);

  // while (true)
  //   ;

  return 0;
}
