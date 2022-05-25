#include "targetSpecific/drivers/gpio.h"
#include "targetSpecific/drivers/interrupt.h"
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

  Interrupt::setEXTIRisingTriggerRegister<pinNumberButton, true>();
  Interrupt::setExternalInterruptClock<true>();
  Interrupt::setExternalInterruptConfigurationRegister<InputPort::PA, pinNumberButton>();
  Interrupt::setEXTIInterruptMaskRegister<pinNumberButton, true>();
  Interrupt::enableIRQ<IRQ::EXTI0>();

  while (true)
    ;

  return 0;
}

extern "C" {
void EXTI0_IRQHandler()
{
  softwareDelay<500000>();
  Interrupt::setEXTIPendingRegister<0, true>();
  GPIO<BaseAddresses::gpioD>::toggleOutputPin<12>();
}
}
