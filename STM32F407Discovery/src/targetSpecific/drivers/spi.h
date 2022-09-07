#ifndef SRC_TARGETSPECIFIC_DRIVERS_SPI
#define SRC_TARGETSPECIFIC_DRIVERS_SPI

#include <array>

#include "targetSpecific/drivers/gpio.h"
#include "targetSpecific/drivers/interrupt.h"
#include "targetSpecific/registers/spiRegisters.h"
#include "utils/helpers.h"

enum class SPINumber
{
  spi1,
  spi2,
  spi3
};

struct SPIInitData
{
  MasterSelection mode;
  BidirectionalDataMode dataMode;
  BaudRateControl rate;
  DataFrameFormat format;
  ClockPhase phase;
  ClockPolarity polarity;
  SoftwareSlaveSelect slaveSelect;
};

extern "C" void SPI2_IRQHandler();
template<SPINumber spiNumber>
class SPI
{
public:
  template<SPIInitData data>
  static void init()
  {
    setSPIClock<true>();

    setDeviceMode<data.mode>();
    setBidirectionalDataMode<data.dataMode>();
    setBaudRateControl<data.rate>();

    setDataFrameFormat<data.format>();
    setClockPhase<data.phase>();
    setClockPolarity<data.polarity>();
    setSoftwareSlaveSelect<data.slaveSelect>();

    SPIRegisters<RegisterType>::setControlRegister1Bit<ControlRegister1Property::ssi, bool, true>(
      spiNumberToBaseAddress.at(spiNumber));

    setSPIEnable<true>();
  }

  template<std::size_t size>
  static void sendData(const std::array<std::uint16_t, size> &data)
  {
    const auto isDataFrameFormat8Bit = SPIRegisters<RegisterType>::
      readControlRegister1Bit<ControlRegister1Property::dff, DataFrameFormat, DataFrameFormat::eightBit>(
        spiNumberToBaseAddress.at(spiNumber));

    if (isDataFrameFormat8Bit)
      return;

    doSendData<std::uint16_t, size>(data);
  }

  template<std::size_t size>
  static void sendDataViaInterrupt(const std::array<std::uint16_t, size> &data)
  {
    const auto isDataFrameFormat8Bit = SPIRegisters<RegisterType>::
      readControlRegister1Bit<ControlRegister1Property::dff, DataFrameFormat, DataFrameFormat::eightBit>(
        spiNumberToBaseAddress.at(spiNumber));

    if (isDataFrameFormat8Bit)
      return;

    sizeOfData = size;
    idxOfData = 0;
    data16bit = data.data();

    Interrupt::enableIRQ<spiNumberToIRQ.at(spiNumber)>();
    SPIRegisters<RegisterType>::setControlRegister2Bit<ControlRegister2Property::txdmaen, true>(
      spiNumberToBaseAddress.at(spiNumber));
  }

  template<std::size_t size>
  static void sendData(const std::array<std::uint8_t, size> &data)
  {
    const auto isDataFrameFormat16Bit = SPIRegisters<RegisterType>::
      readControlRegister1Bit<ControlRegister1Property::dff, DataFrameFormat, DataFrameFormat::sixteenBit>(
        spiNumberToBaseAddress.at(spiNumber));

    if (isDataFrameFormat16Bit)
      return;

    doSendData<std::uint8_t, size>(data);
  }

  template<std::size_t size>
  static void sendDataViaInterrupt(const std::array<std::uint8_t, size> &data)
  {
    const auto isDataFrameFormat16Bit = SPIRegisters<RegisterType>::
      readControlRegister1Bit<ControlRegister1Property::dff, DataFrameFormat, DataFrameFormat::sixteenBit>(
        spiNumberToBaseAddress.at(spiNumber));

    if (isDataFrameFormat16Bit)
      return;

    sizeOfData = size;
    idxOfData = 0;
    data8bit = data.data();

    Interrupt::enableIRQ<spiNumberToIRQ.at(spiNumber)>();
    SPIRegisters<RegisterType>::setControlRegister2Bit<ControlRegister2Property::txeie, true>(
      spiNumberToBaseAddress.at(spiNumber));
  }

  static void sendString(const char *character)
  {
    while (*character)
      sendChar(*character++);
  }

  static void sendStringViaInterrupt(const char *character)
  {
    sizeOfData = 0;
    while (*character)
      sizeOfData++;

    idxOfData = 0;
    data8bit = character;

    Interrupt::enableIRQ<spiNumberToIRQ.at(spiNumber)>();
    SPIRegisters<RegisterType>::setControlRegister2Bit<ControlRegister2Property::txeie, true>(
      spiNumberToBaseAddress.at(spiNumber));
  }

private:
  template<bool set>
  static void setSPIClock()
  {
    if constexpr (spiNumber == SPINumber::spi2)
      RCCRegistersTarget::setPeripheralOnAPB1<PeripheralAPB1::SPI2, set>();
    if constexpr (spiNumber == SPINumber::spi3)
      RCCRegistersTarget::setPeripheralOnAPB1<PeripheralAPB1::SPI3, set>();
    else
      RCCRegistersTarget::setPeripheralOnAPB2<PeripheralAPB2::SPI1, set>();
  }

  template<MasterSelection mode>
  static void setDeviceMode()
  {
    SPIRegisters<RegisterType>::setControlRegister1Bit<ControlRegister1Property::mstr, MasterSelection, mode>(
      spiNumberToBaseAddress.at(spiNumber));
  }

  template<BidirectionalDataMode mode>
  static void setBidirectionalDataMode()
  {
    SPIRegisters<RegisterType>::setControlRegister1Bit<ControlRegister1Property::bidimode, BidirectionalDataMode, mode>(
      spiNumberToBaseAddress.at(spiNumber));
  }

  template<BaudRateControl rate>
  static void setBaudRateControl()
  {
    SPIRegisters<RegisterType>::setBaudRate<rate>(spiNumberToBaseAddress.at(spiNumber));
  }

  template<DataFrameFormat format>
  static void setDataFrameFormat()
  {
    SPIRegisters<RegisterType>::setControlRegister1Bit<ControlRegister1Property::dff, DataFrameFormat, format>(
      spiNumberToBaseAddress.at(spiNumber));
  }

  template<ClockPhase phase>
  static void setClockPhase()
  {
    SPIRegisters<RegisterType>::setControlRegister1Bit<ControlRegister1Property::cpha, ClockPhase, phase>(
      spiNumberToBaseAddress.at(spiNumber));
  }

  template<ClockPolarity polarity>
  static void setClockPolarity()
  {
    SPIRegisters<RegisterType>::setControlRegister1Bit<ControlRegister1Property::cpol, ClockPolarity, polarity>(
      spiNumberToBaseAddress.at(spiNumber));
  }

  template<SoftwareSlaveSelect slaveSelect>
  static void setSoftwareSlaveSelect()
  {
    SPIRegisters<RegisterType>::setControlRegister1Bit<ControlRegister1Property::ssm, SoftwareSlaveSelect, slaveSelect>(
      spiNumberToBaseAddress.at(spiNumber));
  }

  template<bool set>
  static void setSPIEnable()
  {
    SPIRegisters<RegisterType>::setControlRegister1Bit<ControlRegister1Property::spe, bool, set>(
      spiNumberToBaseAddress.at(spiNumber));
  }

  template<typename T, std::size_t size>
  static void doSendData(const std::array<T, size> &data)
  {
    for (const auto dataEl : data)
    {
      while (!SPIRegisters<RegisterType>::isTransmitBufferEmpty(spiNumberToBaseAddress.at(spiNumber)))
        ;
      SPIRegisters<RegisterType>::writeToDataRegister(spiNumberToBaseAddress.at(spiNumber), dataEl);
    }
  }

  static void sendChar(char data)
  {
    while (!SPIRegisters<RegisterType>::isTransmitBufferEmpty(spiNumberToBaseAddress.at(spiNumber)))
      ;

    SPIRegisters<RegisterType>::writeToDataRegister(spiNumberToBaseAddress.at(spiNumber), static_cast<uint16_t>(data));
  }

  static void sendNextData()
  {
    if (idxOfData == sizeOfData)
    {
      data8bit = nullptr;
      data16bit = nullptr;
      sizeOfData = 0;
      idxOfData = 0;
      SPIRegisters<RegisterType>::setControlRegister2Bit<ControlRegister2Property::txeie, false>(
        spiNumberToBaseAddress.at(spiNumber));
    }

    if (data8bit != nullptr)
    {
      SPIRegisters<RegisterType>::writeToDataRegister(spiNumberToBaseAddress.at(spiNumber), *data8bit);
      ++data8bit;
    }

    if (data16bit != nullptr)
    {
      SPIRegisters<RegisterType>::writeToDataRegister(spiNumberToBaseAddress.at(spiNumber), *data16bit);
      ++data16bit;
    }

    ++idxOfData;
  }

  static constexpr StaticMap<SPINumber, RegisterType, 3> spiNumberToBaseAddress{
    { { { SPINumber::spi1, BaseAddresses::spi1 },
        { SPINumber::spi2, BaseAddresses::spi2 },
        { SPINumber::spi3, BaseAddresses::spi3 } } }
  };

  static constexpr StaticMap<SPINumber, IRQ, 3> spiNumberToIRQ{
    { { { SPINumber::spi1, IRQ::SPI1 }, { SPINumber::spi2, IRQ::SPI2 }, { SPINumber::spi3, IRQ::SPI3 } } }
  };

  static inline size_t sizeOfData = 0;
  static inline size_t idxOfData = 0;
  static inline const uint8_t *data8bit = nullptr;
  static inline const uint16_t *data16bit = nullptr;

  friend void SPI2_IRQHandler();
};

#endif /* SRC_TARGETSPECIFIC_DRIVERS_SPI */
