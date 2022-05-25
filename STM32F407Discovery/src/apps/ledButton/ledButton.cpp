#include "targetSpecific/drivers/gpio.h"
#include "targetSpecific/registers/registersBaseAddresses.h"
#include "utils/helpers.h"

int main()
{
  static constexpr auto pinNumberLed = 12;
  static constexpr GPIOInitData initDataLed{ PeripheralAHB1::GPIOD,
                                             PortMode::generalpurposeOutput,
                                             OutputType::pushPull,
                                             OutputSpeed::high,
                                             PullupPullDownControl::noPullupPullDown };

  constexpr auto pinNumberButton = 0;
  static constexpr GPIOInitData initDataButton{ PeripheralAHB1::GPIOA,
                                                PortMode::input,
                                                OutputType::pushPull,
                                                OutputSpeed::high,
                                                PullupPullDownControl::noPullupPullDown };


  using gpioD = GPIO<BaseAddresses::gpioD>;
  using gpioA = GPIO<BaseAddresses::gpioA>;

  gpioD::init<initDataLed, pinNumberLed>();
  gpioA::init<initDataButton, pinNumberButton>();

  while (true)
  {
    if (gpioA::readInputPin<pinNumberButton>())
    {
      softwareDelay<500000>();
      gpioD::toggleOutputPin<pinNumberLed>();
    }
  }

  return 0;
}
