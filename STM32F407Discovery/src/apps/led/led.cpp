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
    delay();
  }

  return 0;
}
