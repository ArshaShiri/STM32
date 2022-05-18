
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
  // constexpr auto pinNumberNSS = 12;
  constexpr auto pinNumberSCLK = 13;
  // constexpr auto pinNumberMISO = 14;
  constexpr auto pinNumberMOSI = 15;


  using gpioB = GPIO<BaseAddresses::gpioB>;
  gpioB::setClock<PeripheralAHB1::GPIOB, true>();

  auto setPinDependentProperties = []<RegisterType pinNumber>() {
    gpioB::setPortMode<PortMode::alternateFunction, pinNumber>();
    gpioB::setAlternateFunction<AlternateFunction::af5, pinNumber>();
    gpioB::setOutputType<OutputType::pushPull, pinNumber>();
    gpioB::setPullupPullDown<PullupPullDownControl::noPullupPullDown, pinNumber>();
    gpioB::setOutputSpeed<OutputSpeed::high, pinNumber>();
  };

  // setPinDependentProperties.template operator()<pinNumberNSS>();
  setPinDependentProperties.template operator()<pinNumberSCLK>();
  // setPinDependentProperties.template operator()<pinNumberMISO>();
  setPinDependentProperties.template operator()<pinNumberMOSI>();
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

  const std::array<std::uint8_t, 10> data{ { 0, 15, 54, 241, 78, 5, 6, 7, 8, 9 } };
  SPI<SPINumber::spi2>::sendData(data);

  while (true)
    ;

  return 0;
}
