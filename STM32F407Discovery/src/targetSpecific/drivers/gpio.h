#ifndef SRC_TARGETSPECIFIC_DRIVERS_GPIO
#define SRC_TARGETSPECIFIC_DRIVERS_GPIO

#include "targetSpecific/gpioRegisters.h"
#include "targetSpecific/rccRegisters.h"

class GPIO
{
private:
  RegisterType baseRegisterAddress;

public:
  GPIO(RegisterType baseRegisterAddressOfGPIO) : baseRegisterAddress{ baseRegisterAddressOfGPIO } {}

  template<PeripheralAHB1 gpio, bool set>
  void setClock()
  {
    RCCRegistersTarget::setPeripheralOnAHB1<gpio, set>();
  }

  template<PortMode mode, PinType pinNumber>
  void setPortMode()
  {
    GPIORegisters<RegisterType>::setPortMode<mode, pinNumber>(baseRegisterAddress);
  }

  template<OutputType type, PinType pinNumber>
  void setOutputType()
  {
    GPIORegisters<RegisterType>::setOutputType<type, pinNumber>(baseRegisterAddress);
  }

  template<OutputSpeed speed, PinType pinNumber>
  void setOutputSpeed()
  {
    GPIORegisters<RegisterType>::setOutputSpeed<speed, pinNumber>(baseRegisterAddress);
  }

  template<PullupPullDownControl type, PinType pinNumber>
  void setPullupPullDown()
  {
    GPIORegisters<RegisterType>::setPullupPullDown<type, pinNumber>(baseRegisterAddress);
  }

  template<AlternateFunction function, PinType pinNumber>
  void setAlternateFunction()
  {
    GPIORegisters<RegisterType>::setAlternateFunction<function, pinNumber>(baseRegisterAddress);
  }

  template<PeripheralAHB1 gpio>
  void reset()
  {
    RCCRegistersTarget::resetPeripheralOnAHB1<gpio>();
  }

  template<PinType pinNumber>
  bool readInputPin()
  {
    return GPIORegisters<RegisterType>::readInputPin<pinNumber>(baseRegisterAddress);
  }

  RegisterType readInputPort() { return GPIORegisters<RegisterType>::readInputPort(baseRegisterAddress); }

  template<PinType pinNumber, bool set>
  void writeOutputPin()
  {
    GPIORegisters<RegisterType>::writeOutputPin<pinNumber, set>(baseRegisterAddress);
  }

  void writeOutputPort(const RegisterType value)
  {
    GPIORegisters<RegisterType>::writeOutputPort(baseRegisterAddress, value);
  }

  template<PinType pinNumber>
  void toggleOutputPin()
  {
    GPIORegisters<RegisterType>::toggleOutputPin<pinNumber>(baseRegisterAddress);
  }
};

#endif /* SRC_TARGETSPECIFIC_DRIVERS_GPIO */
