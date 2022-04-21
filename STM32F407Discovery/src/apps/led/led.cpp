#include "targetSpecific/drivers/gpio.h"
#include "targetSpecific/registers/registersBaseAddresses.h"
#include "utils/helpers.h"

int main()
{
  constexpr auto pinNumber = 12;
  using gpioD = GPIO<BaseAddresses::gpioD>;

  gpioD::setClock<PeripheralAHB1::GPIOD, true>();
  gpioD::setPortMode<PortMode::generalpurposeOutput, pinNumber>();
  gpioD::setOutputSpeed<OutputSpeed::high, pinNumber>();
  gpioD::setOutputType<OutputType::pushPull, pinNumber>();
  gpioD::setPullupPullDown<PullupPullDownControl::noPullupPullDown, pinNumber>();

  while (true)
  {
    gpioD::toggleOutputPin<pinNumber>();
    softwareDelay<500000>();
  }

  return 0;
}
