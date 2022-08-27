// Drivers for 20X4 LCD with PCF8574T I2C device.
// For the driver of this lcd, the explanations presented at
// https://controllerstech.com/lcd-20x4-using-i2c-with-stm32/ are used.

#ifndef STM32F407DISCOVERY_SRC_EXTERNALPERIPHERALS_I2CLCD
#define STM32F407DISCOVERY_SRC_EXTERNALPERIPHERALS_I2CLCD

#include <cstdint>

#include "targetSpecific/drivers/i2c.h"
#include "utils/helpers.h"

class I2CLCD
{
private:
  static constexpr std::uint8_t numberOfRows = 4;
  static constexpr std::uint8_t numberOfColumns = 20;

public:
  static void init()
  {
    // TODO The software delays should be replaced by timers.
    // At the moment, even different waiting times is needed
    // for each command, a single value is fed to the
    // software delay command. This value was chosen
    // by experiments.

    // Initialize in 4 bit mode
    softwareDelay<10000>(); // wait for >40ms
    sendCommand(0x30);
    softwareDelay<10000>(); // wait for >4.1ms
    sendCommand(0x30);
    softwareDelay<10000>(); // wait for >100us
    sendCommand(0x30);
    softwareDelay<10000>();
    sendCommand(0x20); // 4bit mode
    softwareDelay<10000>();

    // dislay initialisation
    sendCommand(0x28); // Function set --> DL=0 (4 bit mode), N = 1 (2 line display) F = 0 (5x8 characters)
    softwareDelay<10000>();
    sendCommand(0x08); // Display on/off control --> D=0,C=0, B=0  ---> display off
    softwareDelay<10000>();
    clear();
    softwareDelay<10000>();
    sendCommand(0x06); // Entry mode set --> I/D = 1 (increment cursor) & S = 0 (no shift)
    softwareDelay<10000>();
    sendCommand(0x0C); // Display on/off control --> D = 1, C and B = 0. (Cursor and blink, last two bits)
  }

  template<std::uint8_t row, std::uint8_t col>
  requires(col < numberOfColumns) static void setCursorLocation()
  {
    static constexpr auto maskValue = 0x80;
    constexpr auto ddramValue = rowNumberToStartDDRAM.at(row) + col;
    I2CLCD::sendCommand(ddramValue | maskValue);
  }

  static void clear() { sendCommand(0x01); }

  static void shiftRight() { sendCommand(0x1C); }

  static void shiftLeft() { sendCommand(0x18); }

  static void sendString(const char *character)
  {
    while (*character)
      sendChar(*character++);
  }

  static void sendCommand(char command)
  {
    char data_u, data_l;
    std::array<std::uint8_t, 4> data{};

    data_u = (command & static_cast<char>(0xf0));
    data_l = (static_cast<char>(command << 4) & static_cast<char>(0xf0));

    data[0] = data_u | 0x0C;
    data[1] = data_u | 0x08;
    data[2] = data_l | 0x0C;
    data[3] = data_l | 0x08;

    I2C<I2CNumber::i2c1>::masterSendData(data, slaveAddress);
  }

  static void sendChar(char data)
  {
    char data_u, data_l;
    std::array<std::uint8_t, 4> dataArray{};

    data_u = (data & static_cast<char>(0xf0));
    data_l = (static_cast<char>(data << 4) & 0xf0);

    dataArray[0] = data_u | 0x0D;
    dataArray[1] = data_u | 0x09;
    dataArray[2] = data_l | 0x0D;
    dataArray[3] = data_l | 0x09;

    I2C<I2CNumber::i2c1>::masterSendData(dataArray, slaveAddress);
  }

private:
  static constexpr std::uint8_t slaveAddress = 0x27;

  static constexpr StaticMap<std::uint8_t, std::uint8_t, numberOfRows> rowNumberToStartDDRAM{
    { { { 0, 0x00 }, { 1, 0x40 }, { 2, 0x14 }, { 3, 0x54 } } }
  };
};


#endif /* STM32F407DISCOVERY_SRC_EXTERNALPERIPHERALS_I2CLCD */
