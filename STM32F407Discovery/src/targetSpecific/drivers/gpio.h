#ifndef SRC_TARGETSPECIFIC_DRIVERS_GPIO
#define SRC_TARGETSPECIFIC_DRIVERS_GPIO

#include "targetSpecific/registers/gpioRegisters.h"
#include "targetSpecific/registers/rccRegisters.h"

struct GPIOInitData
{
  constexpr GPIOInitData(PeripheralAHB1 gpioPortNew,
                         PortMode portModeNew,
                         OutputType outputTypeNew,
                         OutputSpeed outputSpeedNew,
                         PullupPullDownControl pullupPullDownControlNew)
    : gpioPort{ gpioPortNew }, portMode{ portModeNew }, alternateFunction{ AlternateFunction::af0 },
      outputType{ outputTypeNew }, outputSpeed{ outputSpeedNew }, pullupPullDownControl{ pullupPullDownControlNew }
  {
  }

  constexpr GPIOInitData(PeripheralAHB1 gpioPortNew,
                         PortMode portModeNew,
                         AlternateFunction alternateFunctionNew,
                         OutputType outputTypeNew,
                         OutputSpeed outputSpeedNew,
                         PullupPullDownControl pullupPullDownControlNew)
    : gpioPort{ gpioPortNew }, portMode{ portModeNew }, alternateFunction{ alternateFunctionNew },
      outputType{ outputTypeNew }, outputSpeed{ outputSpeedNew }, pullupPullDownControl{ pullupPullDownControlNew }
  {
  }

  PeripheralAHB1 gpioPort;
  PortMode portMode;
  AlternateFunction alternateFunction;
  OutputType outputType;
  OutputSpeed outputSpeed;
  PullupPullDownControl pullupPullDownControl;
};

template<RegisterType baseRegisterAddress>
class GPIO
{
public:
  template<GPIOInitData initData, PinType pinNumber>
  static void init()
  {
    setClock<initData.gpioPort, true>();
    setPortMode<initData.portMode, pinNumber>();

    if constexpr (initData.portMode == PortMode::alternateFunction)
      setAlternateFunction<initData.alternateFunction, pinNumber>();

    setOutputType<initData.outputType, pinNumber>();
    setOutputSpeed<initData.outputSpeed, pinNumber>();
    setPullupPullDown<initData.pullupPullDownControl, pinNumber>();
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

private:
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

  template<AlternateFunction function, PinType pinNumber>
  static void setAlternateFunction()
  {
    GPIORegisters<RegisterType>::setAlternateFunction<function, pinNumber>(baseRegisterAddress);
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
};

#endif /* SRC_TARGETSPECIFIC_DRIVERS_GPIO */
