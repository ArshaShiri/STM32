
#include "targetSpecific/drivers/i2c.h"
#include "targetSpecific/drivers/gpio.h"
#include "targetSpecific/registers/registersBaseAddresses.h"

/*
 *  PB6 --> I2C1_SCL
 *  PB7 --> I2C1_SDA
 */

namespace
{
void initI2CGPIOPeripherals()
{
  constexpr auto pinNumberSCL = 6;
  constexpr auto pinNumberSDA = 7;
  static constexpr GPIOInitData initData{ PeripheralAHB1::GPIOB,  PortMode::alternateFunction,
                                          AlternateFunction::af4, OutputType::openDrain,
                                          OutputSpeed::high,      PullupPullDownControl::pullup };

  using gpioB = GPIO<BaseAddresses::gpioB>;
  gpioB::init<initData, pinNumberSDA>();
  gpioB::init<initData, pinNumberSCL>();
}
} // namespace

void lcd_send_cmd(char cmd, uint8_t slaveAddress)
{
  char data_u, data_l;
  std::array<std::uint8_t, 4> data{};

  data_u = (cmd & 0xf0);
  data_l = ((cmd << 4) & 0xf0);
  data[0] = data_u | 0x0C; // en=1, rs=0
  data[1] = data_u | 0x08; // en=0, rs=0
  data[2] = data_l | 0x0C; // en=1, rs=0
  data[3] = data_l | 0x08; // en=0, rs=0

  I2C<I2CNumber::i2c1>::masterSendData(data, slaveAddress);
}

void lcd_send_data(char data, uint8_t slaveAddress)
{
  char data_u, data_l;
  std::array<std::uint8_t, 4> array{};
  data_u = (data & 0xf0);
  data_l = ((data << 4) & 0xf0);
  array[0] = data_u | 0x0D; // en=1, rs=1
  array[1] = data_u | 0x09; // en=0, rs=1
  array[2] = data_l | 0x0D; // en=1, rs=1
  array[3] = data_l | 0x09; // en=0, rs=1

  I2C<I2CNumber::i2c1>::masterSendData(array, slaveAddress);
}

int main()
{
  initI2CGPIOPeripherals();

  constexpr uint8_t ownAddress = 0x61;
  constexpr uint32_t serialClockSpeedHz = 100000;
  constexpr I2CInitData initData{ Acknowledge::enable, ownAddress, serialClockSpeedHz, FastModeDutyCycle::two };

  I2C<I2CNumber::i2c1>::init<initData>();

  constexpr uint8_t slaveAddress = 0x27;


  softwareDelay<10000>();
  lcd_send_cmd(0x30, slaveAddress);
  softwareDelay<10000>();
  lcd_send_cmd(0x30, slaveAddress);
  softwareDelay<10000>();
  lcd_send_cmd(0x30, slaveAddress);
  softwareDelay<10000>();
  lcd_send_cmd(0x20, slaveAddress);
  softwareDelay<10000>();

  // dislay initialisation
  lcd_send_cmd(0x28, slaveAddress);
  softwareDelay<10000>();
  lcd_send_cmd(0x08, slaveAddress);
  softwareDelay<10000>();
  lcd_send_cmd(0x01, slaveAddress);
  softwareDelay<10000>();
  softwareDelay<10000>();
  lcd_send_cmd(0x06, slaveAddress);
  softwareDelay<10000>();
  lcd_send_cmd(0x0C, slaveAddress);

  lcd_send_cmd(0x80 | 0x00, slaveAddress);
  lcd_send_data('A', slaveAddress);

  while (true)
    ;

  return 0;
}
