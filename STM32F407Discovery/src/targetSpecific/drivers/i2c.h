#ifndef SRC_TARGETSPECIFIC_DRIVERS_I2C
#define SRC_TARGETSPECIFIC_DRIVERS_I2C


#include "targetSpecific/drivers/gpio.h"
#include "targetSpecific/registers/i2cRegisters.h"
#include "utils/helpers.h"


enum class I2CNumber
{
  i2c1,
  i2c2,
  i2c3
};

struct I2CInitData
{
  Acknowledge acknowledge;
};

template<I2CNumber i2cNumber>
class I2C
{
public:
  template<I2CInitData data>
  static void init()
  {
    // setSPIClock<true>();

    secAcknowledgement<data.acknowledge>();

    // setDeviceMode<data.mode>();
    // setBidirectionalDataMode<data.dataMode>();
    // setBaudRateControl<data.rate>();

    // setDataFrameFormat<data.format>();
    // setClockPhase<data.phase>();
    // setClockPolarity<data.polarity>();
    // setSoftwareSlaveSelect<data.slaveSelect>();

    // SPIRegisters<RegisterType>::setControlRegister1Bit<ControlRegister1Property::ssi, bool, true>(
    //   spiNumberToBaseAddress.at(spiNumber));

    // setSPIEnable<true>();
  }

private:
  template<Acknowledge acknowledge>
  static void secAcknowledgement()
  {
    I2CRegisters<RegisterType>::setControlRegister1Bit<ControlRegister1Property::ack, Acknowledge, acknowledge>(
      i2cNumberToBaseAddress.at(i2cNumber));
  }

  static constexpr StaticMap<I2CNumber, RegisterType, 3> i2cNumberToBaseAddress{
    { { { I2CNumber::i2c1, BaseAddresses::i2c1 },
        { I2CNumber::i2c2, BaseAddresses::i2c2 },
        { I2CNumber::i2c3, BaseAddresses::i2c3 } } }
  };
};

#endif /* SRC_TARGETSPECIFIC_DRIVERS_I2C */
