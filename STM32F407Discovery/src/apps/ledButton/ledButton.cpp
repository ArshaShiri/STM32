#include "targetSpecific/drivers/gpio.h"
#include "targetSpecific/registers/registersBaseAddresses.h"

namespace
{
void delay()
{
  auto i = size_t{ 0 };
  for ([[maybe_unused]] volatile size_t counter = 0; i < 500000; counter = i, ++i)
  {
  }
}
} // namespace

int main()
{
  constexpr auto ledPinNumber = 12;
  using gpioD = GPIO<BaseAddresses::gpioD>;
  gpioD::setClock<PeripheralAHB1::GPIOD, true>();
  gpioD::setPortMode<PortMode::generalpurposeOutput, ledPinNumber>();
  gpioD::setOutputSpeed<OutputSpeed::high, ledPinNumber>();
  gpioD::setOutputType<OutputType::pushPull, ledPinNumber>();
  gpioD::setPullupPullDown<PullupPullDownControl::noPullupPullDown, ledPinNumber>();

  constexpr auto buttonPinNumber = 0;
  using gpioA = GPIO<BaseAddresses::gpioA>;
  gpioA::setClock<PeripheralAHB1::GPIOA, true>();
  gpioA::setPortMode<PortMode::input, buttonPinNumber>();
  gpioA::setOutputSpeed<OutputSpeed::high, buttonPinNumber>();
  gpioA::setPullupPullDown<PullupPullDownControl::noPullupPullDown, buttonPinNumber>();

  while (true)
  {
    if (gpioA::readInputPin<buttonPinNumber>())
    {
      delay();
      gpioD::toggleOutputPin<ledPinNumber>();
    }
  }

  return 0;
}
