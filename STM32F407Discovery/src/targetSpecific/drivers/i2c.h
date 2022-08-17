#ifndef SRC_TARGETSPECIFIC_DRIVERS_I2C
#define SRC_TARGETSPECIFIC_DRIVERS_I2C

#include <array>

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
  uint8_t ownAddress;
  uint32_t serialClockSpeedHz;
  FastModeDutyCycle fastModeDutyCycle;
};

template<I2CNumber i2cNumber>
class I2C
{
public:
  template<I2CInitData data>
  static void init()
  {
    secAcknowledgement<data.acknowledge>();
    const auto apb1ClockHz = RCCRegistersTarget::getAPB1ClockHZ();

    constexpr auto mhzToHZRatio = UINT32_C(1000000);
    const auto apb1ClockMhz = apb1ClockHz / mhzToHZRatio;

    I2CRegisters<RegisterType>::setPeripheralClockFrequency(i2cNumberToBaseAddress.at(i2cNumber), apb1ClockMhz);
    I2CRegisters<RegisterType>::setOwnAddress(i2cNumberToBaseAddress.at(i2cNumber), data.ownAddress);
    I2CRegisters<RegisterType>::keepBit14OfOAR1AsSet(i2cNumberToBaseAddress.at(i2cNumber));
    I2CRegisters<RegisterType>::setSerialClock(
      i2cNumberToBaseAddress.at(i2cNumber), data.serialClockSpeedHz, apb1ClockHz, data.fastModeDutyCycle);

    I2CRegisters<RegisterType>::setTRise(i2cNumberToBaseAddress.at(i2cNumber), data.serialClockSpeedHz, apb1ClockHz);
  }

  template<std::size_t size>
  static void masterSendData(const std::array<std::uint8_t, size> &data, const uint8_t slaveAddress)
  {
    // Generate the start condition.
    I2CRegisters<RegisterType>::
      setControlRegister1Bit<ControlRegister1Property::start, StartCondition, StartCondition::repeatedStartGeneration>(
        i2cNumberToBaseAddress.at(i2cNumber));

    // Confirm that start generation is completed byu checking hte SB flag in the SR1.
    // Note: until SB is cleared, SCL will be stretched (pulled to low)
    while (!I2CRegisters<RegisterType>::isStartConditionGenerated(i2cNumberToBaseAddress.at(i2cNumber)))
      ;

    // Send the address of the salve with r/nw bit set to 0 (total 8 bits)
    executeAddressPhase(slaveAddress);

    // Confirm that address phase is completed by checking the ADDR flag is SR1
    clearADDRFLag();

    // Send data.
    for (auto byte : data)
    {
      while (!I2CRegisters<RegisterType>::isDataRegisterEmpty(i2cNumberToBaseAddress.at(i2cNumber)))
        ;
      I2CRegisters<RegisterType>::writeToDataRegister(i2cNumberToBaseAddress.at(i2cNumber), byte);
    }

    // After sending data, wait for TXE=1 and BTF=1 before generating stop condition.
    // TXE=1 and BTF=1 means that bot shift register and data registers are empty and next transmission should begin
    // when BTF=1 SCL will be stretched (pulled to low)
    while (!I2CRegisters<RegisterType>::isDataRegisterEmpty(i2cNumberToBaseAddress.at(i2cNumber)))
      ;
    while (!I2CRegisters<RegisterType>::isByteTransferFinished(i2cNumberToBaseAddress.at(i2cNumber)))
      ;

    // Generate stop condition and master does not need to wait for the completion of stop condition.
    // Note: generation STOP, automatically clears BTF.
    I2CRegisters<RegisterType>::
      setControlRegister1Bit<ControlRegister1Property::stop, StopCondition, StopCondition::stopGeneration>(
        i2cNumberToBaseAddress.at(i2cNumber));
  }

private:
  template<Acknowledge acknowledge>
  static void secAcknowledgement()
  {
    I2CRegisters<RegisterType>::setControlRegister1Bit<ControlRegister1Property::ack, Acknowledge, acknowledge>(
      i2cNumberToBaseAddress.at(i2cNumber));
  }

  static void executeAddressPhase(uint8_t slaveAddress)
  {
    constexpr auto readWriteBitNumber = 1;
    slaveAddress = slaveAddress << readWriteBitNumber;
    slaveAddress = slaveAddress & ~(readWriteBitNumber);
    I2CRegisters<RegisterType>::writeToDataRegister(i2cNumberToBaseAddress.at(i2cNumber), slaveAddress);
  }

  static void clearADDRFLag()
  {
    I2CRegisters<RegisterType>::readStatusRegister1(i2cNumberToBaseAddress.at(i2cNumber));
    I2CRegisters<RegisterType>::readStatusRegister2(i2cNumberToBaseAddress.at(i2cNumber));
  }

  static constexpr StaticMap<I2CNumber, RegisterType, 3> i2cNumberToBaseAddress{
    { { { I2CNumber::i2c1, BaseAddresses::i2c1 },
        { I2CNumber::i2c2, BaseAddresses::i2c2 },
        { I2CNumber::i2c3, BaseAddresses::i2c3 } } }
  };
};

#endif /* SRC_TARGETSPECIFIC_DRIVERS_I2C */
