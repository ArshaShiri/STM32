#include "targetSpecific/drivers/gpio.h"
#include "targetSpecific/registers/registersBaseAddresses.h"
#include "utils/helpers.h"

int main()
{
  static constexpr auto pinNumber = 12;
  static constexpr GPIOInitData initData{ PeripheralAHB1::GPIOD,
                                          PortMode::generalpurposeOutput,
                                          OutputType::pushPull,
                                          OutputSpeed::high,
                                          PullupPullDownControl::noPullupPullDown };


  using gpioD = GPIO<BaseAddresses::gpioD>;

  // gpioD::setClock<PeripheralAHB1::GPIOD, true>();
  // gpioD::setPortMode<PortMode::generalpurposeOutput, pinNumber>();
  // gpioD::setOutputType<OutputType::pushPull, pinNumber>();
  // gpioD::setOutputSpeed<OutputSpeed::high, pinNumber>();
  // gpioD::setPullupPullDown<PullupPullDownControl::noPullupPullDown, pinNumber>();

  // TODO why calling this instead of the commented out lines above generates more text in the binary?
  gpioD::init<initData, pinNumber>();

  while (true)
  {
    gpioD::toggleOutputPin<pinNumber>();
    softwareDelay<500000>();
  }

  return 0;
}
