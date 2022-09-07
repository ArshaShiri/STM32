
#include "targetSpecific/drivers/spi.h"
#include "targetSpecific/drivers/gpio.h"
#include "targetSpecific/registers/registersBaseAddresses.h"

/*
 *  PB15 --> SPI2_MOSI
 *  PB14 --> SPI2_MISO
 *  PB13 --> SPI2_SCLK
 *  PB12 --> SPI2_NSS
 */

namespace
{
void initSPI2GPIOPeripherals()
{
  constexpr auto pinNumberSCLK = 13;
  constexpr auto pinNumberMOSI = 15;
  static constexpr GPIOInitData initData{ PeripheralAHB1::GPIOB,  PortMode::alternateFunction,
                                          AlternateFunction::af5, OutputType::pushPull,
                                          OutputSpeed::high,      PullupPullDownControl::noPullupPullDown };

  using gpioB = GPIO<BaseAddresses::gpioB>;
  gpioB::init<initData, pinNumberSCLK>();
  gpioB::init<initData, pinNumberMOSI>();
}
} // namespace

int main()
{
  initSPI2GPIOPeripherals();

  constexpr SPIInitData initData{ MasterSelection::master,
                                  BidirectionalDataMode::fullDuplex,
                                  BaudRateControl::fPCLKDiv2,
                                  DataFrameFormat::eightBit,
                                  ClockPhase::firstClockTransitionFirstDataCapture,
                                  ClockPolarity::clockZeroWhenIdle,
                                  SoftwareSlaveSelect::enabled };

  SPI<SPINumber::spi2>::init<initData>();
  SPI<SPINumber::spi2>::sendString("Hello World!");

  while (true)
    ;

  return 0;
}
