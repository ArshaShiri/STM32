#ifndef STM32F407DISCOVERY_SRC_TARGETSPECIFIC_DRIVERS_SPI
#define STM32F407DISCOVERY_SRC_TARGETSPECIFIC_DRIVERS_SPI

#include <array>

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
};

template<SPINumber spiNumber>
class SPI
{
public:
  template<SPIInitData data>
  static void init()
  {
    setDeviceMode<data.mode>();
    setBidirectionalDataMode<data.dataMode>();
    setBaudRateControl<data.rate>();

    setDataFrameFormat<data.format>();
    setClockPhase<data.phase>();
    setClockPolarity<data.polarity>();
  }

  template<std::size_t size>
  static void sendData(const std::array<std::uint16_t, size> &data)
  {
    if (SPIRegisters<RegisterType>::
          readControlRegister1Bit<ControlRegister1Property::dff, DataFrameFormat, DataFrameFormat::eightBit>)
      return;

    doSendData<std::uint16_t, size>(data);
  }

  template<std::size_t size>
  static void sendData(const std::array<std::uint8_t, size> &data)
  {
    if (SPIRegisters<RegisterType>::
          readControlRegister1Bit<ControlRegister1Property::dff, DataFrameFormat, DataFrameFormat::sixteenBit>)
      return;

    doSendData<std::uint8_t, size>(data);
  }

private:
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
    SPIRegisters<RegisterType>::setBaudRate<BaudRateControl, rate>(spiNumberToBaseAddress.at(spiNumber));
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

  template<typename T, std::size_t size>
  static void doSendData(const std::array<T, size> &data)
  {
    for (const auto dataEl : data)
    {
      while (!SPIRegisters<RegisterType>::isTransmitBufferEmpty())
        ;
      SPIRegisters<RegisterType>::writeToDataRegister(spiNumberToBaseAddress.at(spiNumber), dataEl);
    }
  }

  static constexpr StaticMap<SPINumber, RegisterType, 3> spiNumberToBaseAddress{
    { { { spi1::noPullupPullDown, BaseAddresses::spi1 },
        { spi2::pullup, BaseAddresses::spi2 },
        { spi3::pullDown, BaseAddresses::spi3 } } }
  };
};


#endif /* STM32F407DISCOVERY_SRC_TARGETSPECIFIC_DRIVERS_SPI */
