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

  auto gpio = GPIO(BaseAddresses::gpioD);
  gpio.setClock<PeripheralAHB1::GPIOD, true>();
  gpio.setPortMode<PortMode::generalpurposeOutput, pinNumber>();
  gpio.setOutputSpeed<OutputSpeed::high, pinNumber>();
  gpio.setOutputType<OutputType::pushPull, pinNumber>();
  gpio.setPullupPullDown<PullupPullDownControl::noPullupPullDown, pinNumber>();

  while (true)
  {
    gpio.toggleOutputPin<pinNumber>();
    delay();
  }

  return 0;
}
