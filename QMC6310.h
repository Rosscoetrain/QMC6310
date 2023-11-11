#ifndef QMC6310_H
#define QMC6310_H

#include <Arduino.h>
#include <Wire.h>

#define QMC6310_ADDRESS 0x0C // Default I2C address of QMC6310

// Register addresses
#define QMC6310_X_LSB 0x01
#define QMC6310_X_MSB 0x02
#define QMC6310_Y_LSB 0x03
#define QMC6310_Y_MSB 0x04
#define QMC6310_Z_LSB 0x05
#define QMC6310_Z_MSB 0x06
#define QMC6310_STATUS 0x09
#define QMC6310_CONTROL_1 0x0A
#define QMC6310_CONTROL_2 0x0B

// Status register bits
#define QMC6310_STATUS_DRDY 0x01
#define QMC6310_STATUS_OVFL 0x02

class QMC6310 {
public:
  QMC6310() {}

  bool begin();
  bool readData(int16_t &x, int16_t &y, int16_t &z);

  void setADDR(uint8_t b);

  uint8_t getMode1();
  void setMode1(uint8_t m);

  uint8_t getMode2();
  void setMode2(uint8_t m);

  void setReset();

private:
  uint8_t _ADDR = QMC6310_ADDRESS;
  void _writeReg(byte r, byte v);
};

#endif // QMC6310_H
