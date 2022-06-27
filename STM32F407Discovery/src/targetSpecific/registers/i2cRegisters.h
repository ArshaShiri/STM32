#ifndef SRC_TARGETSPECIFIC_REGISTERS_I2CREGISTERS
#define SRC_TARGETSPECIFIC_REGISTERS_I2CREGISTERS

#include "registerType.h"
#include "registersBaseAddresses.h"

#include "utils/helpers.h"
#include "utils/registerAccess.h"

enum class ControlRegister1Property
{
  pe,
  smbus,
  smbType,
  enarp,
  enpec,
  engc,
  noStretch,
  start,
  stop,
  ack,
  pos,
  pec,
  alert,
  swrst
};

enum class Peripheral
{
  enable,
  disable
};

enum class Acknowledge
{
  enable,
  disable
};

enum class FastModeDutyCycle
{
  two,
  sixteenOverNine
};

enum class StartCondition
{
  noStartGeneration,
  repeatedStartGeneration
};

template<typename RegisterAddressType>
class I2CRegisters
{
  struct Offsets
  {
    // TODO Make the type to be RegisterAddressType
    static constexpr RegisterType cr1 = UINT32_C(0x00);
    static constexpr RegisterType cr2 = UINT32_C(0x04);
    static constexpr RegisterType oar1 = UINT32_C(0x08);
    static constexpr RegisterType oar2 = UINT32_C(0x0C);
    static constexpr RegisterType dr = UINT32_C(0x10);
    static constexpr RegisterType sr1 = UINT32_C(0x14);
    static constexpr RegisterType sr2 = UINT32_C(0x18);
    static constexpr RegisterType ccr = UINT32_C(0x1C);
    static constexpr RegisterType trise = UINT32_C(0x20);
    static constexpr RegisterType fltr = UINT32_C(0x24);
  };

  static constexpr auto maxClockFrequencyValue = 0b110010;

public:
  template<ControlRegister1Property property, typename T, T value>
  static void setControlRegister1Bit(const RegisterAddressType i2cBaseAddress)
  {
    constexpr auto bitNumber = controlRegister1PropertyToShiftValue.at(property);
    constexpr auto setValue = SetValueHelper<property, T>::getSetValue(value);
    doSet<setValue>(i2cBaseAddress + Offsets::cr1, bitNumber);
  }

  static void setPeripheralClockFrequency(const RegisterAddressType i2cBaseAddress, uint8_t value)
  {
    constexpr RegisterAddressType maskValue = UINT32_C(0b111111);
    value = value & maskValue;
    auto cr2Value = RegisterAccess<RegisterAddressType, RegisterAddressType>::regGet(i2cBaseAddress + Offsets::cr2);
    cr2Value = cr2Value & ~maskValue;

    RegisterAccess<RegisterAddressType, RegisterAddressType>::regSet(i2cBaseAddress + Offsets::cr2, cr2Value | value);
  }

  static void setOwnAddress(const RegisterAddressType i2cBaseAddress, uint8_t value)
  {
    constexpr RegisterAddressType maskValue = UINT32_C(0b1111111);
    constexpr RegisterAddressType shiftValueForSevenBitAddress = 1;
    value = (value & maskValue) << shiftValueForSevenBitAddress;

    auto oar1Value = RegisterAccess<RegisterAddressType, RegisterAddressType>::regGet(i2cBaseAddress + Offsets::oar1);
    oar1Value = oar1Value & ~maskValue;

    RegisterAccess<RegisterAddressType, RegisterAddressType>::regSet(i2cBaseAddress + Offsets::oar1,
                                                                     (oar1Value | value));
  }

  static void keepBit14OfOAR1AsSet(const RegisterAddressType i2cBaseAddress)
  {
    constexpr auto bitNumberThatHasToBeSetToOne = 14;
    RegisterAccess<RegisterAddressType, RegisterAddressType>::regBitSet(i2cBaseAddress + Offsets::oar1,
                                                                        bitNumberThatHasToBeSetToOne);
  }

  static void setSerialClock(const RegisterAddressType i2cBaseAddress,
                             const uint32_t serialClockSpeed,
                             const uint32_t apb1ClockHz,
                             const FastModeDutyCycle cycle)
  {
    constexpr auto standardModeSpeedHz = UINT32_C(100000);
    constexpr auto fastModeSpeedHz = UINT32_C(400000);

    uint16_t ccrValue = UINT32_C(0);

    // Assuming t high is equal to t low.
    if (serialClockSpeed < standardModeSpeedHz)
      ccrValue = (apb1ClockHz) / (2 * serialClockSpeed);
    else
    {
      constexpr auto bitNumberForFastMode = 15;
      RegisterAccess<RegisterAddressType, RegisterAddressType>::regBitSet(i2cBaseAddress + Offsets::ccr,
                                                                          bitNumberForFastMode);

      constexpr auto bitNumberForDutyCycle = 14;
      if (cycle == FastModeDutyCycle::two)
      {
        RegisterAccess<RegisterAddressType, RegisterAddressType>::regBitClear(i2cBaseAddress + Offsets::ccr,
                                                                              bitNumberForDutyCycle);
        ccrValue = (apb1ClockHz) / (3 * serialClockSpeed);
      }
      else
      {
        RegisterAccess<RegisterAddressType, RegisterAddressType>::regBitSet(i2cBaseAddress + Offsets::ccr,
                                                                            bitNumberForDutyCycle);
        ccrValue = (apb1ClockHz) / (25 * serialClockSpeed);
      }
    }

    constexpr auto ccrMastValue = 0xFFF;
    ccrValue = ccrValue & ccrMastValue;
    RegisterAccess<RegisterAddressType, RegisterAddressType>::regSet(i2cBaseAddress + Offsets::ccr, ccrValue);
  }

  static bool isStartConditionGenerated(const RegisterAddressType i2cBaseAddress)
  {
    constexpr auto bitNumber = 0;
    return RegisterAccess<RegisterAddressType, RegisterAddressType>::regBitGet(i2cBaseAddress + Offsets::sr1,
                                                                               bitNumber);
  }

  static bool isAddressTransmissionFinished(const RegisterAddressType i2cBaseAddress)
  {
    constexpr auto bitNumber = 1;
    return RegisterAccess<RegisterAddressType, RegisterAddressType>::regBitGet(i2cBaseAddress + Offsets::sr1,
                                                                               bitNumber);
  }

  static void writeToDataRegister(const RegisterAddressType i2cBaseAddress, uint8_t data)
  {
    RegisterAccess<RegisterAddressType, uint8_t>::regSet(i2cBaseAddress + Offsets::dr, data);
  }

  static RegisterAddressType readStatusRegister1(const RegisterAddressType i2cBaseAddress)
  {
    return RegisterAccess<RegisterAddressType, RegisterAddressType>::regGet(i2cBaseAddress + Offsets::sr1);
  }

  static RegisterAddressType readStatusRegister2(const RegisterAddressType i2cBaseAddress)
  {
    return RegisterAccess<RegisterAddressType, RegisterAddressType>::regGet(i2cBaseAddress + Offsets::sr2);
  }

private:
  template<ControlRegister1Property property, typename T>
  struct SetValueHelper
  {
    static constexpr bool getSetValue(T value) { return value; }
  };

  template<typename T>
  struct SetValueHelper<ControlRegister1Property::pe, T>
  {
    static constexpr bool getSetValue(Peripheral value) { return value == Peripheral::enable ? 1 : 0; }
  };

  template<typename T>
  struct SetValueHelper<ControlRegister1Property::start, T>
  {
    static constexpr bool getSetValue(StartCondition value)
    {
      return value == StartCondition::repeatedStartGeneration ? 1 : 0;
    }
  };

  template<typename T>
  struct SetValueHelper<ControlRegister1Property::ack, T>
  {
    static constexpr bool getSetValue(Acknowledge value) { return value == Acknowledge::enable ? 1 : 0; }
  };

  template<bool set>
  static void doSet(const RegisterAddressType regAddress, const RegisterAddressType bitNumber)
  {
    if constexpr (set)
      RegisterAccess<RegisterAddressType, RegisterAddressType>::regBitSet(regAddress, bitNumber);
    else
      RegisterAccess<RegisterAddressType, RegisterAddressType>::regBitClear(regAddress, bitNumber);
  }

  static constexpr StaticMap<ControlRegister1Property, std::uint8_t, 14> controlRegister1PropertyToShiftValue{
    { { { ControlRegister1Property::pe, 0 },
        { ControlRegister1Property::smbus, 1 },
        { ControlRegister1Property::smbType, 3 },
        { ControlRegister1Property::enarp, 4 },
        { ControlRegister1Property::enpec, 5 },
        { ControlRegister1Property::engc, 6 },
        { ControlRegister1Property::noStretch, 7 },
        { ControlRegister1Property::start, 8 },
        { ControlRegister1Property::stop, 9 },
        { ControlRegister1Property::ack, 10 },
        { ControlRegister1Property::pos, 11 },
        { ControlRegister1Property::pec, 12 },
        { ControlRegister1Property::alert, 13 },
        { ControlRegister1Property::swrst, 15 } } }
  };
};


#endif /* SRC_TARGETSPECIFIC_REGISTERS_I2CREGISTERS */
