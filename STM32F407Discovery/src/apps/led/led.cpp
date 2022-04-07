#include "targetSpecific/drivers/gpio.h"
#include "targetSpecific/registersBaseAddresses.h"

namespace
{
void delay()
{
  for (auto i = size_t{ 0 }; i < 500000; ++i)
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
