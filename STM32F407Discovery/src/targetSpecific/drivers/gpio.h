#ifndef SRC_TARGETSPECIFIC_DRIVERS_GPIO
#define SRC_TARGETSPECIFIC_DRIVERS_GPIO

#include "targetSpecific/registers/gpioRegisters.h"
#include "targetSpecific/registers/rccRegisters.h"

template<RegisterType baseRegisterAddress>
class GPIO
{
public:
  template<PeripheralAHB1 gpio, bool set>
  static void setClock()
  {
    RCCRegistersTarget::setPeripheralOnAHB1<gpio, set>();
  }

  template<PortMode mode, PinType pinNumber>
  static void setPortMode()
  {
    GPIORegisters<RegisterType>::setPortMode<mode, pinNumber>(baseRegisterAddress);
  }

  template<OutputType type, PinType pinNumber>
  static void setOutputType()
  {
    GPIORegisters<RegisterType>::setOutputType<type, pinNumber>(baseRegisterAddress);
  }

  template<OutputSpeed speed, PinType pinNumber>
  static void setOutputSpeed()
  {
    GPIORegisters<RegisterType>::setOutputSpeed<speed, pinNumber>(baseRegisterAddress);
  }

  template<PullupPullDownControl type, PinType pinNumber>
  static void setPullupPullDown()
  {
    GPIORegisters<RegisterType>::setPullupPullDown<type, pinNumber>(baseRegisterAddress);
  }

  template<AlternateFunction function, PinType pinNumber>
  static void setAlternateFunction()
  {
    GPIORegisters<RegisterType>::setAlternateFunction<function, pinNumber>(baseRegisterAddress);
  }

  template<PeripheralAHB1 gpio>
  static void reset()
  {
    RCCRegistersTarget::resetPeripheralOnAHB1<gpio>();
  }

  template<PinType pinNumber>
  static bool readInputPin()
  {
    return GPIORegisters<RegisterType>::readInputPin<pinNumber>(baseRegisterAddress);
  }

  RegisterType readInputPort() { return GPIORegisters<RegisterType>::readInputPort(baseRegisterAddress); }

  template<PinType pinNumber, bool set>
  static void writeOutputPin()
  {
    GPIORegisters<RegisterType>::writeOutputPin<pinNumber, set>(baseRegisterAddress);
  }

  static void writeOutputPort(const RegisterType value)
  {
    GPIORegisters<RegisterType>::writeOutputPort(baseRegisterAddress, value);
  }

  template<PinType pinNumber>
  static void toggleOutputPin()
  {
    GPIORegisters<RegisterType>::toggleOutputPin<pinNumber>(baseRegisterAddress);
  }
};

#endif /* SRC_TARGETSPECIFIC_DRIVERS_GPIO */
